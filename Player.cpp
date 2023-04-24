#include "Player.h"
#include <assert.h>

// コンストラクタ
Player::Player() {}

// デストラクタ
Player::~Player() {}

// 初期化
void Player::Initialize(Model* model,uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);

	// 受け取ったデータをメンバ変数に格納
	m_model = model;
	m_textureHandle = textureHandle;

	// ワールド変換の初期化
	m_worldTransform.Initialize();
}

// 更新
void Player::Update() {

	//行列を定数バッファに転送
	m_worldTransform.TransferMatrix();

}

// 描画
void Player::Draw(ViewProjection viewProjection) {

	// 3Dモデルを描画
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);

}
