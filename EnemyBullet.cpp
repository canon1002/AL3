#include "EnemyBullet.h"
#include <assert.h>

/// ・R・・・X・g・・・N・^
EnemyBullet::EnemyBullet() {}

/// ・f・X・g・・・N・^
EnemyBullet::~EnemyBullet() {}

/// ・・・・・ｻ
void EnemyBullet::Initialize(Model* model, const Vector3& position, Vector3& velocity) {

	// NULL・|・C・・・^・`・F・b・N
	assert(model);

	// ・・・ｯ・・・ﾁ・ｽ・f・[・^・・・・・・・o・ﾏ・・・ﾉ・i・[
	m_model = model;
	// ・e・N・X・`・・・ﾇ・ﾝ・・・ﾝ
	m_textureHandle = TextureManager::Load("Bullet.png");

	// ・・・[・・・h・g・・・・・X・t・H・[・・ﾌ・・・・・ｻ
	m_worldTransform.Initialize();
	// ・・・・・ﾅ・・・ｯ・・・ﾁ・ｽ・・・・・ﾀ・W・・・Z・b・g
	m_worldTransform.translation_ = position;

	// ・・・・・ﾅ・・・ｯ・・・ﾁ・ｽ・ｬ・x・・・・・・・o・ﾏ・・・ﾉ・Z・b・g
	m_vel = velocity;

	// ・ｼ・a・・・ﾝ・・
	SetRadius(0.5f);
}

/// ・X・V・・・・
void EnemyBullet::Update() {

	// ・・・ﾔ・o・ﾟ・ﾅ・f・X
	if (--m_deathTimer <= 0) {
		m_isDead = true;
	}

	// ・ﾀ・W・・・ﾚ・ｮ・ｳ・ｹ・・
	m_worldTransform.translation_.x += m_vel.x;
	m_worldTransform.translation_.y += m_vel.y;
	m_worldTransform.translation_.z += m_vel.z;

	// ・s・・・・・v・Z・E・]・・
	m_worldTransform.UpdateMatrix();
}

/// ・`・・・・・・
void EnemyBullet::Draw(const ViewProjection& viewProjection) {

	// ・・・f・・・ﾌ・`・・
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);
}