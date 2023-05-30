#include "Enemy.h"
#include "Player.h"
#include <assert.h>
#include "./class/Matrix4.h"

/// ・・ｳ・・ｳ・・ｹ・・・・・ｩ・・ｯ・・ｿ
Enemy::Enemy() {}

/// ・・・・・ｹ・・・・・ｩ・・ｯ・・ｿ
Enemy::~Enemy() {

	// ・ｼｾ・・ｯ・・ｩ・・ｹ・・ｮ・・・・・ｾ
	for (EnemyBullet* bullet : m_bullets) {
		delete bullet;
	}

}

/// ・・・・・・・・・
void Enemy::Initialize(Model* model, const Vector3& position, Vector3& velocity) {

	// NULL・・・・・､・・ｳ・・ｿ・・・・・ｧ・・・・・ｯ
	assert(model);

	// ・・・・・・・・・・・｣・・・・・・・・ｼ・・ｿ・・・・・｡・・ｳ・・・・､・・・ｰ・・ｫ・ｼ・ｴ・
	m_model = model;
	// ・・・・・ｯ・・ｹ・・・・・｣・ｪｭ・・ｿ・ｾｼ・・ｿ
	m_textureHandle = TextureManager::Load("enemySoul.jpg");

	// ・・ｯ・・ｼ・・ｫ・・・・・・・・ｩ・・ｳ・・ｹ・・・・・ｩ・・ｼ・・・・ｮ・・・・・・・・・
	m_worldTransform.Initialize();
	// ・ｼ・・・ｰ・・ｧ・・・・・・・・・・・｣・・・・・・・・・・ｺｧ・ｨ・・・・・・ｻ・・・・・・
	m_worldTransform.translation_ = position;

	// ・ｼ・・・ｰ・・ｧ・・・・・・・・・・・｣・・・・・・ｺｦ・・・・・｡・・ｳ・・・・､・・・ｰ・・ｫ・・ｻ・・・・・・
	m_vel = velocity;

	// ・・・・ｾ・・・・・ｨｭ・ｮ・
	SetRadius(0.5f);

}

/// ・・ｴ・・ｰ・・ｦ・・・
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
		if (m_worldTransform.translation_.z < 0.0f) {

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
	for (EnemyBullet* bullet : m_bullets) {
		bullet->Update();
	}

	// ・・・・・ｹ・・・・・ｩ・・ｰ・・ｮ・ｫ・・・｣・・・・ｼｾ・・・・・・・・､
	m_bullets.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// ・｡・・・・・・・・ｨ・・ｮ・・・ｻ・ｻ｢・・
	m_worldTransform.UpdateMatrix();
}

/// ・・・・・ｻ・・ｦ・・・
void Enemy::Draw(const ViewProjection& viewProjection) {

	// ・ｼｾ・・ｮ・・・・・ｻ
	for (EnemyBullet* bullet : m_bullets) {
		bullet->Draw(viewProjection);
	}

	// ・・｢・・・・・ｫ・・ｮ・・・・・ｻ
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);
}


// ・・ｺ・・・・・ｦ・・・
void Enemy::Boon() {}

// ・・ｻ・・・
void Enemy::Attack() {

	assert(m_player);

	// ・ｼｾ・・ｮ・・・ｺｦ・・・・ｨｭ・ｮ・
	const float kBulletSpeed = 0.0005f;

	// ・・・・・ｬ・・､・・､・・ｼ・・ｮ・ｺｧ・ｨ・・・・・・・・ｾ・
	Vector3 m_worldPos = m_player->GetWorldPos();
	// ・・ｵ・・ｮ・ｺｧ・ｨ・・・・・・・・ｾ・
	Vector3 m_enemyWorldPos = GetWorldPos();
	// ・ｷｮ・・・・・・・・・・ｾ・
	Vector3 SubPos;
	SubPos.x = m_worldPos.x - m_enemyWorldPos.x;
	SubPos.y = m_worldPos.y - m_enemyWorldPos.y;
	SubPos.z = m_worldPos.z - m_enemyWorldPos.z;
	// ・・・・・ｯ・・・・・ｫ・・ｮ・ｭ｣・ｦ・・・・
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

	// ・ｼｾ・・・・・・・・・・・・・・・・・・・・・・・
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(m_model, m_worldTransform.translation_, velocity);

	// ・ｼｾ・・・・・ｻ・・ｲ
	m_bullets.push_back(newBullet);
}