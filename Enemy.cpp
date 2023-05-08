#include "Enemy.h"
#include <assert.h>
#include "./class/Matrix4.h"

/// コンストラクタ
Enemy::Enemy() {}

/// デストラクタ
Enemy::~Enemy() {}

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


	// 時間経過でデス
	if (--m_deathTimer <= 0) {
		m_isDead = true;
	}

	// 座標を移動させる
	m_worldTransform.translation_.x += m_vel.x;
	m_worldTransform.translation_.y += m_vel.y;
	m_worldTransform.translation_.z += m_vel.z;

	// 行列を計算・転送
	m_worldTransform.UpdateMatrix();
}

/// 描画処理
void Enemy::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);
}

void Enemy::Boon() {

	
}