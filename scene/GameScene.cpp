#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>
#include "./class/Matrix4.h"
#include "./collider/Collider.h"
#include "ImGuiManager.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

	// 3Dモデルデータの開放
	delete m_model;
	// 自キャラの開放
	delete m_player;
	// デバッグカメラの開放
	delete m_debugCamera;
	// 敵クラスの開放
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

	CheckAllCollisions();

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

void GameScene::CheckAllCollisions() {

	// 判定対象の座標
	Vector3 posA, posB, posC, posD;
	float radA, radB, radC, radD;
	// 弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = m_player->GetBullets();
	for (Enemy* enemy : m_enemys) {
		const std::list<EnemyBullet*>& enemyBullets = enemy->GetBullets();
	}
	// 座標をセット
	posA = m_player->GetWorldPos();
	radA = m_player->GetRadius();

		// コライダー
	std::list<Collider*> m_colliders;

	// コライダーをリストに登録
	m_colliders.push_back(m_player);
	for (Enemy* enemy : m_enemys) {
		m_colliders.push_back(enemy);
	}

	// 自弾・敵弾すべて
	for (PlayerBullet* playerBullet : playerBullets) {
		m_colliders.push_back(playerBullet);
	}
	for (Enemy* enemy : m_enemys) {
		const std::list<EnemyBullet*>& enemyBullets = enemy->GetBullets();
		for (EnemyBullet* enemyBullet : enemyBullets) {
			m_colliders.push_back(enemyBullet);
		}
	}
	for (Enemy* enemy : m_enemys) {
		const std::list<EnemyBullet*>& enemyBullets = enemy->GetBullets();

		// プレイヤーと敵の当たり判定
		CheckCollisionPair(m_player, enemy);

		for (PlayerBullet* playerBullet : playerBullets) {
			// 敵とプレイヤーの弾の当たり判定
			CheckCollisionPair(playerBullet, enemy);

			// 敵の弾とプレイヤーの弾の当たり判定
			for (EnemyBullet* enemyBullet : enemyBullets) {
				CheckCollisionPair(playerBullet, enemyBullet);
			}
		}

		// 敵の弾とプレイヤーの当たり判定
		for (EnemyBullet* enemyBullet : enemyBullets) {
			CheckCollisionPair(m_player, enemyBullet);
		}
	}

	/*
	// 自弾・敵弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player->GetBullets();
	for (Enemy* enemy : m_enemys) {
		const std::list<EnemyBullet*>& enemyBullets = enemy->GetBullets();
	}

	// コライダー
	std::list<Collider*> m_colliders;

	// コライダーをリストに登録
	m_colliders.push_back(player);
	for (Enemy* enemy : m_enemys) {
		m_colliders.push_back(enemy);
	}

	// 自弾・敵弾すべて
	for (PlayerBullet* playerBullet : playerBullets) {
		m_colliders.push_back(playerBullet);
	}

	for (EnemyBullet* enemyBullet : enemyBullets) {
		m_colliders.push_back(enemyBullet);
	}
	*/

	/* リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = m_colliders.begin();
	for (; itrA != m_colliders.end(); ++itrA) {

		// イテレーターからコライダーを取得
		Collider* colliderA = (*itrA);

		// このイテレーターは前のイテレーターの次の要素から回す
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != m_colliders.end(); ++itrB) {

			// イテレーターからコライダーを取得
			Collider* colliderB = (*itrB);

			// 当たり判定
			//CheckCollisionPair(colliderA, colliderB);

			// イテレーターBはイテレーターAの次の要素から回す
			std::list<Collider*>::iterator itrC = itrB;
			itrC++;

			for (; itrC != m_colliders.end(); ++itrC) {

				// イテレーターからコライダーを取得
				Collider* colliderC = (*itrC);

				// 当たり判定
				CheckCollisionPair(colliderB, colliderC);

				// イテレーターBはイテレーターAの次の要素から回す
				std::list<Collider*>::iterator itrD = itrC;
				itrD++;

				for (; itrD != m_colliders.end(); ++itrD) {

					// イテレーターからコライダーを取得
					Collider* colliderD = (*itrD);

					// 当たり判定
					CheckCollisionPair(colliderC, colliderD);
				}
			}
		}
	}
	*/
}

void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {

	// 衝突フィルタリング
	if ((colliderA->GetCollisionAttribute() & colliderB->GetCollisionMask()) == 0 ||
	    (colliderB->GetCollisionAttribute() & colliderA->GetCollisionMask()) == 0)
	{
		return;
	}

	// コライダーのワールド座標を取得
	Vector3 posA = colliderA->GetWorldPos();
	float radA = colliderA->GetRadius();
	Vector3 posB = colliderB->GetWorldPos();
	float radB = colliderB->GetRadius();

	// 距離の判定
	if ((posA.x + radA) > (posB.x - radB) && (posA.x - radA) < (posB.x + radB) &&
	    (posA.y + radA) > (posB.y - radB) && (posA.y - radA) < (posB.y + radB) &&
	    (posA.z + radA) > (posB.z - radB) && (posA.z - radA) < (posB.z + radB)) 
	{		
		
		colliderA->OnCollision(colliderB);
		colliderB->OnCollision(colliderA);

		// エフェクトを生成し、初期化
		// Effect* newEffect = new Effect();
		// newEffect->Initialize(EFFECT_TYPE::DISCRETE, { quadA.rightTop.x - (quadA.rightTop.x -
		// quadA.leftTop.x),quadA.leftTop.y });

		// エフェクトを登録
		// m_effects.push_back(newEffect);
	}
}
