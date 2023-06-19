#include "Enemy.h"
#include "Player.h"
#include <assert.h>
#include "./class/Matrix4.h"
#include "GameScene.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

/// 初期化
void Enemy::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {

	// NULLであればエラー
	assert(model);

	m_model = model;
	m_textureHandle = TextureManager::Load("enemySoul.jpg");
	m_worldTransform.Initialize();
	m_worldTransform.translation_ = position;
	m_vel = velocity;

	SetRadius(0.5f);

}

/// 
void Enemy::Update() {

	switch (m_phase) {

	case Enemy::Phase::Approach:
	default:

		// ・ｺｧ・ｨ・・・・・ｧｻ・・・・・・・・・・・・
		m_worldTransform.translation_.x += m_vel.x;
		m_worldTransform.translation_.y += m_vel.y;
		m_worldTransform.translation_.z += m_vel.z;

		// ・・ｻ・・・
		if (m_attackCoolTime > 0) {
			m_attackCoolTime--;
		} else if (m_attackCoolTime == 0) {
			m_attackCoolTime = 60;
			Attack();
		}

		// ・・｢・ｮ・・・ｮ・ｽ・・ｽｮ・・ｧ・・・・・ｧ・・ｼ・・ｺ・ｧｻ・｡・
		if (m_worldTransform.translation_.z < 20.0f) {

			// ・・・ｺｦ・・・・・・・ｨｭ・ｮ・
			m_vel.x = 0.02f;

			// ・・・・・ｧ・・ｼ・・ｺ・・・・､・・・ｴ
			m_phase = Enemy::Phase::Leave;

		}
			

		break;
	case Enemy::Phase::Leave:

		// ・ｺｧ・ｨ・・・・・ｧｻ・・・・・・・・・・・・
		m_worldTransform.translation_.x += m_vel.x;
		m_worldTransform.translation_.y += m_vel.y;
		m_worldTransform.translation_.z += m_vel.z;

		break;
	
	}

	//// ・・・・・・・ｵ・・・・・・ｧ・・・・・ｹ
	//if (--m_deathTimer <= 0) {
	//	m_isDead = true;
	//}

	// ・ｼｾ・・ｮ・・ｴ・・ｰ
	

	// ・・・・・ｹ・・・・・ｩ・・ｰ・・ｮ・ｫ・・・｣・・・・ｼｾ・・・・・・・・､
	

	// ・｡・・・・・・・・ｨ・・ｮ・・・ｻ・ｻ｢・・
	m_worldTransform.UpdateMatrix();
}

/// ・・・・・ｻ・・ｦ・・・
void Enemy::Draw(const ViewProjection& viewProjection) {

	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);
}


// ・・ｺ・・・・・ｦ・・・
void Enemy::Boon() {}

// ・・ｻ・・・
void Enemy::Attack() {

	assert(m_player);

	// 弾の速度を設定
	const float kBulletSpeed = 0.0005f;

	// プレイヤーのワールド座標系を取得
	Vector3 m_worldPos = m_player->GetWorldPos();
	// 敵のワールド座標系を取得
	Vector3 m_enemyWorldPos = GetWorldPos();
	// 差分を計算	
	Vector3 SubPos;
	SubPos.x = m_worldPos.x - m_enemyWorldPos.x;
	SubPos.y = m_worldPos.y - m_enemyWorldPos.y;
	SubPos.z = m_worldPos.z - m_enemyWorldPos.z;
	// 長さを調整
	float length = sqrtf((SubPos.x * SubPos.x) + (SubPos.y * SubPos.y) + (SubPos.z * SubPos.z));
	if (length > 0) {
		length = 1 / length;
	}
	SubPos.x = (SubPos.x / length);
	SubPos.y = (SubPos.y / length);
	SubPos.z = (SubPos.z / length);

	Vector3 velocity;
	velocity.x = SubPos.x * kBulletSpeed;
	velocity.y = SubPos.y * kBulletSpeed;
	velocity.z = SubPos.z * kBulletSpeed;

	// 敵の弾を生成
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(m_model, m_worldTransform.translation_, velocity);
	
	// ゲームシーンに登録
	m_gamesSene->AddEnemyBullet(newBullet);
}