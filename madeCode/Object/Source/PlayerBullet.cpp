#include "madeCode/Object/Heder/PlayerBullet.h"
#include <assert.h>

/// コンストラクタ
PlayerBullet::PlayerBullet() {}

/// デストラクタ
PlayerBullet::~PlayerBullet() {}


/// 初期化
void PlayerBullet::Initialize(Model* model, const Vector3& position, Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	// 受け取ったデータをメンバ変数に格納
	m_model = model;
	// テクスチャ読み込み
	m_textureHandle = TextureManager::Load("./Resources/bullet/bullet.png");

	// ワールドトランスフォームの初期化
	m_worldTransform.Initialize();
	// 引数で受け取った初期座標をセット
	m_worldTransform.translation_ = position;   

	// 引数で受け取った速度をメンバ変数にセット
	m_vel = velocity;

	// 半径を設定
	SetRadius(0.5f);

}


/// 更新処理
void PlayerBullet::Update() {

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
void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);

}