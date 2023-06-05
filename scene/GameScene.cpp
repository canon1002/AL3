#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>
#include "./class/Matrix4.h"
#include "./collider/Collider.h"
#include "ImGuiManager.h"


GameScene::GameScene() {}

GameScene::~GameScene() {

	// 3Dモデルデータの解放
	delete m_model;
	// 自キャラの解放
	delete m_player;
	// デバッグカメラの解放
	delete m_debugCamera;
	// 衝突マネージャーの解放
	delete m_collisionManager;
	// 天球の解放
	delete m_skydome;
	// 敵クラスの解放
	for (Enemy* enemy : m_enemys) {
		delete enemy;
	}

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャ読み込み
	m_textureHandle = TextureManager::Load("white1x1.png");
	// 3Dモデルデータの作成
	m_model = Model::Create();
	// ビュープロジェクションの初期化
	m_viewProjection.Initialize();
	// 天球の作成
	m_skydome = new Skydome();
	// 天球の初期化
	m_skydome->Initialize();
	// 自キャラの生成
	m_player = new Player();
	// 自キャラの初期化
	m_player->Initialize(m_model, m_textureHandle);
	// デバッグカメラの生成
	m_debugCamera = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&m_viewProjection);

	///敵関連の処理

	// 敵の速度を設定
	const float kEnemySpeed = -0.02f;
	Vector3 velocity(0, 0, kEnemySpeed);

	// 敵の初期座標を設定
	enemyStartPos = {4.0f, 0.0f, 40.0f};

	// 敵を生成し、初期化
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(m_model, enemyStartPos, velocity);

	// 敵を登録
	m_enemys.push_back(newEnemy);
	// プレイヤーを貸し出す
	for (Enemy* enemy : m_enemys) {
		enemy->SetPlayer(m_player);
	}


}

void GameScene::Update() {

	// 天球の更新
	m_skydome->Update();

	// 自キャラの更新
	m_player->Update();
	
	// 敵キャラの更新
	for (Enemy* enemy : m_enemys) {
		enemy->SetPlayer(m_player);
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

	///
	/// ↓当たり判定処理　ここから
	///

	// 衝突マネージャーのリストをクリア
	m_collisionManager->ClearColliders();
	
	// 自弾・敵弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = m_player->GetBullets();
	for (Enemy* m_enemy : m_enemys) {const std::list<EnemyBullet*>& enemyBullets = m_enemy->GetBullets();}
	
	// コライダーを衝突マネージャーのリストに登録
	m_collisionManager->SetCollider(m_player);
	for (Enemy* m_enemy : m_enemys) {m_collisionManager->SetCollider(m_enemy);}
	for (PlayerBullet* playerBullet : playerBullets) {m_collisionManager->SetCollider(playerBullet);}
	for (Enemy* m_enemy : m_enemys) {
		const std::list<EnemyBullet*>& enemyBullets = m_enemy->GetBullets();
		for (EnemyBullet* enemyBullet : enemyBullets) {m_collisionManager->SetCollider(enemyBullet);}
	}

	// 衝突マネージャーの当たり判定処理を呼び出す
	m_collisionManager->Update();

	///
	/// ↑当たり判定処理　ここまで
	/// 


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
		// ビュープロジェクション行列の更新と転送
		m_viewProjection.UpdateMatrix();
	}

	// 座標を表示(デバッグ)

	// キャラクターの座標を画面表示する処理
	ImGui::Begin("Position");
	// 座標を代入
	m_inputPos3A[0] = m_player->GetWorldPos().x;
	m_inputPos3A[1] = m_player->GetWorldPos().y;
	m_inputPos3A[2] = m_player->GetWorldPos().z;
	ImGui::SliderFloat3("Player", m_inputPos3A, 0.0f, 1.0f);
	
	// 座標を代入
	for (Enemy* enemy : m_enemys) {
		m_inputPos3B[0] = enemy->GetWorldPos().x;
		m_inputPos3B[1] = enemy->GetWorldPos().y;
		m_inputPos3B[2] = enemy->GetWorldPos().z;
		ImGui::SliderFloat3("Enemy", m_inputPos3B, 0.0f, 1.0f);
	}

	// 座標を代入
	for (Enemy* enemy : m_enemys) {
		for (EnemyBullet* enemyBullet : enemy->GetBullets()) {
			m_inputPos3C[0] = enemyBullet->GetWorldPos().x;
			m_inputPos3C[1] = enemyBullet->GetWorldPos().y;
			m_inputPos3C[2] = enemyBullet->GetWorldPos().z;
			ImGui::SliderFloat3("Enemy", m_inputPos3B, 0.0f, 1.0f);
		}
	}

	ImGui::End();


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

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}