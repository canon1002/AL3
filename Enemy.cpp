#include "Enemy.h"
#include <assert.h>
#include "./class/Matrix4.h"

/// コンストラクタ
Enemy::Enemy() {}

/// デストラクタ
Enemy::~Enemy() {

	// 弾クラスの開放
	for (EnemyBullet* bullet : m_bullets) {
		delete bullet;
	}

}

/// 初期化
void Enemy::Initialize(Model* model, const Vector3& position, Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	// 受け取ったデータをメンバ変数に格納
	m_model = model;
	// テクスチャ読み込み
	m_textureHandle = TextureManager::Load("enemySoul.jpg");

	// ワールドトランスフォームの初期化
	m_worldTransform.Initialize();
	// 引数で受け取った初期座標をセット
	m_worldTransform.translation_ = position;
	m_worldTransform.translation_.y += 1.0f;

	// 引数で受け取った速度をメンバ変数にセット
	m_vel = velocity;
}

/// 更新処理
void Enemy::Update() {

	switch (m_phase) {

	case Enemy::Phase::Approach:
	default:

		// 座標を移動させる
		m_worldTransform.translation_.x += m_vel.x;
		m_worldTransform.translation_.y += m_vel.y;
		m_worldTransform.translation_.z += m_vel.z;

		//攻撃
		if (m_attackCoolTime>0) {
			m_attackCoolTime--;
		} else if (m_attackCoolTime == 0) {
			m_attackCoolTime = 30;
			Attack();
		}

		// 既定の位置でフェーズ移行
		if (m_worldTransform.translation_.z < 0.0f) {

			// 速度を再設定
			m_vel.x = 0.2f;

			// フェーズを変更
			m_phase = Enemy::Phase::Leave;

		}
			

		break;
	case Enemy::Phase::Leave:

		// 座標を移動させる
		m_worldTransform.translation_.x += m_vel.x;
		m_worldTransform.translation_.y += m_vel.y;
		m_worldTransform.translation_.z += m_vel.z;

		break;
	
	}

	//// 時間経過でデス
	//if (--m_deathTimer <= 0) {
	//	m_isDead = true;
	//}

	// 弾の更新
	for (EnemyBullet* bullet : m_bullets) {
		bullet->Update();
	}

	// デスフラグの立った弾を削除
	m_bullets.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// 行列を計算・転送
	m_worldTransform.UpdateMatrix();
}

/// 描画処理
void Enemy::Draw(const ViewProjection& viewProjection) {

	// 弾の描画
	for (EnemyBullet* bullet : m_bullets) {
		bullet->Draw(viewProjection);
	}

	// モデルの描画
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);
}


// 発生処理
void Enemy::Boon() {}

// 攻撃
void Enemy::Attack() {

	// 弾の速度を設定
	const float kBulletSpeed = 5.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = Matrix4::Transform(velocity, m_worldTransform.matWorld_);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(m_model, m_worldTransform.translation_, velocity);

	// 弾を登録
	m_bullets.push_back(newBullet);
}