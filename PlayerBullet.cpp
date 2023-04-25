#include "PlayerBullet.h"
#include <assert.h>

/// コンストラクタ
PlayerBullet::PlayerBullet() {}

/// デストラクタ
PlayerBullet::~PlayerBullet() {}


/// 初期化
void PlayerBullet::Initialize(Model* model, const Vector3& position) {

	// NULLポインタチェック
	assert(model);

	// 受け取ったデータをメンバ変数に格納
	m_model = model;
	// テクスチャ読み込み
	m_textureHandle = TextureManager::Load("white1x1.png");

	// ワールドトランスフォームの初期化
	m_worldTransform.Initialize();
	// 引数で受け取った初期座標をセット
	m_worldTransform.translation_ = position;   

}


/// 更新処理
void PlayerBullet::Update() {

	// 行列を計算・転送
	m_worldTransform.UpdateMatrix();

}


/// 描画処理
void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);

}