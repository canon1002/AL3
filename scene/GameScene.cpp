#include "GameScene.h"
#include "./class/Matrix4x4Funk.h"
#include "./collider/Collider.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>
#include<fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {

	// 3Dモデルデータの解放
	delete m_model;
	// 自キャラの解放
	delete m_player;
	// デバッグカメラの解放
	delete m_debugCamera;
	// レールカメラの解放
	delete m_railCamera;
	// 衝突マネージャーの解放
	delete m_collisionManager;
	// 天球の解放
	delete m_skydome;
	// 敵クラスの解放
	for (Enemy* enemy : m_enemys) {
		delete enemy;
	}
	// 敵の弾クラスの解放
	for (EnemyBullet* bullet : m_enemyBullets) {
		delete bullet;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャ読み込み
	m_textureHandle = TextureManager::Load("player.png");
	// 3Dモデルデータの作成
	m_model = Model::Create();
	// ワールド座標変換データの初期化
	m_worldTransform.Initialize();
	// ビュープロジェクションの初期化
	m_viewProjection.Initialize();
	// レールカメラの初期化
	m_railCamera->Initialize({0, 5, -60}, {0, 0, 0});
	// 天球の作成
	m_skydome = new Skydome();
	// 天球の初期化
	m_skydome->Initialize();
	// 自キャラの生成
	m_player = new Player();
	// 自キャラの初期化
	m_player->Initialize(m_model, m_textureHandle, {0, 0, 40});
	// 自キャラとレールカメラの親子関係を結ぶ
	m_player->SetParent(&m_railCamera->GetWorldTransform());
	// デバッグカメラの生成
	m_debugCamera = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&m_viewProjection);

	/// 敵関連の処理

	// 敵の速度を設定
	const float kEnemySpeed = -0.02f;
	Vector3 velocity(0, 0, kEnemySpeed);

	// 敵の初期座標を設定
	enemyStartPos = {0.0f, 8.0f, 80.0f};

	// 敵発生データの読み込みを行う
	LoadEnemyPopDate();

}

void GameScene::Update() {

	//
	// ↓キー入力 ここから
	//

	// マウスホイールを取得
	m_player->GetInput()->GetWheel();

	if (m_player->GetInput()->GetWheel() > 0) {
		WorldTransform result;
		result = m_railCamera->GetWorldTransform();
		result.translation_.z += 2.0f;
		m_railCamera->SetWorldTransform(result);
	} else if (m_player->GetInput()->GetWheel() < 0) {
		WorldTransform result;
		result = m_railCamera->GetWorldTransform();
		result.translation_.z -= 2.0f;
		m_railCamera->SetWorldTransform(result);
	}

	// 中ボタン＋トラックでカメラを移動
	if (m_player->GetInput()->IsPressMouse(2) == true) {
		if (m_player->GetInput()->GetMouseMove().lX != 0) {
			WorldTransform result;
			result = m_railCamera->GetWorldTransform();
			result.translation_.x -= (m_player->GetInput()->GetMouseMove().lX / 10);
			m_railCamera->SetWorldTransform(result);
		}
		if (m_player->GetInput()->GetMouseMove().lY != 0) {
			WorldTransform result;
			result = m_railCamera->GetWorldTransform();
			result.translation_.y += (m_player->GetInput()->GetMouseMove().lY / 10);
			m_railCamera->SetWorldTransform(result);
		}
	}

	// 右ボタン＋トラックでカメラを回転
	if (m_player->GetInput()->IsPressMouse(1) == true) {

		if (m_player->GetInput()->GetMouseMove().lX > 0) {
			WorldTransform result;
			result = m_railCamera->GetWorldTransform();
			result.rotation_.y -= 0.05f;
			m_railCamera->SetWorldTransform(result);
		}

		if (m_player->GetInput()->GetMouseMove().lX < 0) {
			WorldTransform result;
			result = m_railCamera->GetWorldTransform();
			result.rotation_.y += 0.05f;
			m_railCamera->SetWorldTransform(result);
		}

		if (m_player->GetInput()->GetMouseMove().lY > 0) {
			WorldTransform result;
			result = m_railCamera->GetWorldTransform();
			result.rotation_.x -= 0.05f;
			m_railCamera->SetWorldTransform(result);
		}

		if (m_player->GetInput()->GetMouseMove().lY < 0) {
			WorldTransform result;
			result = m_railCamera->GetWorldTransform();
			result.rotation_.x += 0.05f;
			m_railCamera->SetWorldTransform(result);
		}
	}

	//
	// ↑キー入力 ここまで
	//

	// 天球の更新
	m_skydome->Update();

	// 自キャラの更新
	m_player->Update(m_viewProjection);


	// 敵発生コマンドの更新を行う
	UpdateEnemyPopCommands();

	// 敵キャラの更新
	for (Enemy* enemy : m_enemys) {
		enemy->Update();
	}

	// デスフラグの立った敵を削除
	m_enemys.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});

	// 敵の弾の更新
	for (EnemyBullet* bullet : m_enemyBullets) {
		bullet->Update();
	}
	// 敵の弾の死亡処理
	m_enemyBullets.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	///
	/// ↓当たり判定処理　ここから
	///

	// 衝突マネージャーのリストをクリア
	m_collisionManager->ClearColliders();

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = m_player->GetBullets();

	// コライダーを衝突マネージャーのリストに登録
	m_collisionManager->SetCollider(m_player);
	for (Enemy* m_enemy : m_enemys) {
		m_collisionManager->SetCollider(m_enemy);
	}
	for (PlayerBullet* playerBullet : playerBullets) {
		m_collisionManager->SetCollider(playerBullet);
	}
	for (EnemyBullet* enemyBullet : m_enemyBullets) {
		m_collisionManager->SetCollider(enemyBullet);
	}

	// 衝突マネージャーの当たり判定処理を呼び出す
	m_collisionManager->Update();

	///
	/// ↑当たり判定処理　ここまで
	///

	// 行列の更新
	m_worldTransform.UpdateMatrix();

// デバッグカメラの有効化
#ifdef _DEBUG

	// 数字の0キーを押すとデバックカメラを起動する
	if (input_->TriggerKey(DIK_0)) {
		m_isDebugCameraAction = true;
	}

#endif

	// カメラの処理
	if (m_isDebugCameraAction) {
		// デバッグカメラの更新
		m_debugCamera->Update();
		m_viewProjection.matView = m_debugCamera->GetViewProjection().matView;
		m_viewProjection.matProjection = m_debugCamera->GetViewProjection().matProjection;
		// ビュープロジェクションの転送
		m_viewProjection.TransferMatrix();
	} else {
		// レールカメラの更新
		// m_railCamera->SetViewProjection(m_viewProjection);
		m_railCamera->Update();
		m_viewProjection.matView = m_railCamera->GetViewProjection().matView;
		m_viewProjection.matProjection = m_railCamera->GetViewProjection().matProjection;
		// ビュープロジェクションの転送
		m_viewProjection.TransferMatrix();
	}

	// レールカメラ更新処理


	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 天球の描画処理
	m_skydome->Draw(m_viewProjection);

	// 自キャラの描画処理
	m_player->Draw(m_viewProjection);

	// 敵キャラの更新
	for (Enemy* enemy : m_enemys) {
		enemy->Draw(m_viewProjection);
	}

	// 敵の弾を描画
	for (EnemyBullet* bullet : m_enemyBullets) {
		bullet->Draw(m_viewProjection);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	m_player->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

/// 敵の弾の登録
void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet)
{
	// リストに登録する
	m_enemyBullets.push_back(enemyBullet);
}


/// 敵発生データの読み込み
void GameScene::LoadEnemyPopDate() 
{
	// ファイルを開く
	std::ifstream file;
	file.open("./Resources/csv/enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容をストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();

}


void GameScene::UpdateEnemyPopCommands() 
{
	// 待機処理
	if (m_isWait) 
	{
		m_waitTime--;
		if (m_waitTime <= 0) 
		{
			m_isWait = false;
		}
		return;
	}

	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands,line))
	{
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) 
		{
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0)
		{
			//ｘ座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			Enemy* newEnemy = new Enemy();
			newEnemy->Initialize(m_model, Vector3(x, y, z), Vector3(0, 0, -0.0f));
			// 敵キャラにゲームシーンとプレイヤーを渡す
			newEnemy->SetGameScene(this);
			newEnemy->SetPlayer(m_player);
			// 敵キャラをリストに登録する
			m_enemys.push_back(newEnemy);

		}

		// WAITコマンド
		else if (word.find("WAIT") == 0) 
		{
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			m_isWait = true;
			m_waitTime = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}