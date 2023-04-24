#include "Player.h"
#include <assert.h>
#include"./class/Matrix4.h"

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

	// シングルインスタンスを取得する
	m_input = Input::GetInstance();

}

// 更新
void Player::Update() {

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更(左右)
	if (m_input->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (m_input->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	// 押した方向で移動ベクトルを変更(上下)
	if (m_input->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (m_input->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 座標移動 (ベクトルの加算)
	m_worldTransform.translation_.x += move.x;
	m_worldTransform.translation_.y += move.y;
	m_worldTransform.translation_.z += move.z;

	// スケーリング行列の作成
	m_worldTransform.matWorld_ = Matrix4::MakeAffineMatrix(
	    m_worldTransform.scale_, m_worldTransform.rotation_, m_worldTransform.translation_);

	//行列を定数バッファに転送
	m_worldTransform.TransferMatrix();

}

// 描画
void Player::Draw(ViewProjection viewProjection) {

	// 3Dモデルを描画
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);

}
