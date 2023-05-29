﻿#include "Player.h"
#include <assert.h>
#include "./class/Matrix4.h"
#include "ImGuiManager.h"

// コンストラクタ
Player::Player() {}

// デストラクタ
Player::~Player() {

	// 弾クラスの開放
	for (PlayerBullet* bullet : m_bullets) {
		delete bullet;
	}

}

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

	// キーボードによる移動処理

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 旋回処理
	Rotate();

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

	// 移動限界座標
	const float kMoveLimitX = 30;
	const float kMoveLimitY = 10;
	// 範囲を超えない処理
	m_worldTransform.translation_.x = max(m_worldTransform.translation_.x, -kMoveLimitX);
	m_worldTransform.translation_.x = min(m_worldTransform.translation_.x, +kMoveLimitX);
	m_worldTransform.translation_.y = max(m_worldTransform.translation_.y, -kMoveLimitY);
	m_worldTransform.translation_.y = min(m_worldTransform.translation_.y, +kMoveLimitY);

	// キャラクターの攻撃処理
	Attack();

	// 弾の更新
	for (PlayerBullet* bullet : m_bullets) {
		bullet->Update();
	}

	// デスフラグの立った弾を削除
	m_bullets.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});


	// 行列への変換

	// 座標移動 (ベクトルの加算)
	m_worldTransform.translation_.x += move.x;
	m_worldTransform.translation_.y += move.y;
	m_worldTransform.translation_.z += move.z;
	
	// 行列を計算・転送
	m_worldTransform.UpdateMatrix();


	// 座標を表示(デバッグ)

	// キャラクターの座標を画面表示する処理
	ImGui::Begin("Player");
	// 座標を代入
	m_inputPos3[0] = m_worldTransform.translation_.x;
	m_inputPos3[1] = m_worldTransform.translation_.y;
	m_inputPos3[2] = m_worldTransform.translation_.z;
	ImGui::SliderFloat3("Position", m_inputPos3, 0.0f, 1.0f);
	ImGui::End();

}

// 描画
void Player::Draw(ViewProjection viewProjection) {

	// 弾の描画
	for (PlayerBullet* bullet : m_bullets) {
		bullet->Draw(viewProjection);
	}

	// 3Dモデルを描画
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);

}

// 旋回(回転)
void Player::Rotate() { 
	//回転速度[ラジアン/flame]
	const float kRotSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更
	if (m_input->PushKey(DIK_A)) {
		m_worldTransform.rotation_.y -= kRotSpeed;
	} else if (m_input->PushKey(DIK_D)) {
		m_worldTransform.rotation_.y += kRotSpeed;
	}
}

// 攻撃
void Player::Attack() {

	// 発射キーをトリガーしたら
	if (m_input->TriggerKey(DIK_SPACE)) {

		// 弾の速度を設定
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = Matrix4::Transform(velocity, m_worldTransform.matWorld_);

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(m_model, m_worldTransform.translation_, velocity);

		// 弾を登録
		m_bullets.push_back(newBullet);
	}

}

Vector3 Player::GetWorldPos() {

	Vector3 worldPos;
	worldPos.x = m_worldTransform.translation_.x;
	worldPos.y = m_worldTransform.translation_.y;
	worldPos.z = m_worldTransform.translation_.z;

	return worldPos;
}