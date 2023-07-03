#include "Player.h"
#include "./class/Matrix4x4Funk.h"
#include "GameScene.h"
#include "class/MathTool.h"
#include <assert.h>
#include <ImGui.h>

// コンストラクタ
Player::Player() {}

// デストラクタ
Player::~Player() {

	// 弾クラスの開放
	for (PlayerBullet* bullet : m_bullets) {
		delete bullet;
	}

	delete m_sprite2DReticle;
}

// 初期化
void Player::Initialize(Model* model, uint32_t textureHandle, Vector3 worldPos) {

	// NULLポインタチェック
	assert(model);

	// 受け取ったデータをメンバ変数に格納
	m_model = model;
	m_textureHandle = textureHandle;

	// ワールド変換の初期化
	m_worldTransform.Initialize();
	m_worldTransform.translation_ = worldPos;

	// シングルインスタンスを取得する
	m_input = Input::GetInstance();

	// 半径を設定
	SetRadius(0.5f);

#pragma region レティクル

	// 3Dレティクル用ワールド変換データの初期化
	m_worldTransform3DReticle.Initialize();

	// レティクル用テクスチャ取得
	uint32_t textureRatecle = TextureManager::Load("white1x1.png");
	// スプライト生成
	m_sprite2DReticle =
	    Sprite::Create(textureRatecle, {0, 0}, {1.0f, 0.0f, 0.0f, 0.4f}, {0.5f, 0.5f});
	m_sprite2DReticle->SetSize({64.0f, 64.0f});

#pragma endregion
}

// 更新
void Player::Update(const ViewProjection& viewProjection) {

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

	// 座標移動 (ベクトルの加算)
	m_worldTransform.translation_.x += move.x;
	m_worldTransform.translation_.y += move.y;
	m_worldTransform.translation_.z += move.z;

	// 移動限界座標
	const float kMoveLimitX = 30;
	const float kMoveLimitY = 10;
	// 範囲を超えない処理
	m_worldTransform.translation_.x = max(m_worldTransform.translation_.x, -kMoveLimitX);
	m_worldTransform.translation_.x = min(m_worldTransform.translation_.x, +kMoveLimitX);
	m_worldTransform.translation_.y = max(m_worldTransform.translation_.y, -kMoveLimitY);
	m_worldTransform.translation_.y = min(m_worldTransform.translation_.y, +kMoveLimitY);

	// 行列を計算・転送
	m_worldTransform.UpdateMatrix();

#pragma region 自機からのワールド座標から3Dレティクルのワールド座標を計算

	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 25.0f;
	// 自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = {0, 0, 1.0f};
	// 自機のワールド座標の回転を反映
	offset = Matrix4x4Funk::Multiply(offset, m_worldTransform.matWorld_);
	// ベクトルの長さを整える
	offset = Nomalize(offset);
	offset.x *= kDistancePlayerTo3DReticle;
	offset.y *= kDistancePlayerTo3DReticle;
	offset.z *= kDistancePlayerTo3DReticle;
	// 3Dレティクルの座標を設定
	m_worldTransform3DReticle.translation_ = Add(this->GetWorldPos(), offset);

#pragma endregion

#pragma region 3dレティクルから2Dレティクルに変換
	const static Matrix4x4 viewport = Matrix4x4Funk::MakeViewportMatrix(
	    0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);

	Matrix4x4 view = Matrix4x4Funk::MakeIdentity();

	Matrix4x4 vp = Matrix4x4Funk::Multiply(
	    Matrix4x4Funk::Multiply(viewProjection.matView, viewProjection.matProjection),
	    viewport);

	//Matrix4x4 vp = Matrix4x4Funk::Multiply(
	//    Matrix4x4Funk::Multiply(view, viewProjection.matProjection), viewport);
	
	Vector3 screenReticlePosition =
	    Matrix4x4Funk::Transform(m_worldTransform3DReticle.translation_, vp);

	m_sprite2DReticle->SetPosition({screenReticlePosition.x, screenReticlePosition.y});

	ImGui::Begin("2DReticle");
	ImGui::Text("%f\n%f", screenReticlePosition.x, screenReticlePosition.y);
	ImGui::End();

#pragma endregion

	// 3Dレティクルの座標を更新転送
	m_worldTransform3DReticle.UpdateMatrix();

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
}

// 描画
void Player::Draw(const ViewProjection& viewProjection) const {

	// 弾の描画
	for (PlayerBullet* bullet : m_bullets) {
		bullet->Draw(viewProjection);
	}

	// 3Dモデルを描画
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);

	// 3Dレティクルを描画
	//m_model->Draw(m_worldTransform3DReticle, viewProjection, m_textureHandle);
}

// 旋回(回転)
void Player::Rotate() {
	// 回転速度[ラジアン/flame]
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
		const float kBulletSpeed = 0.5f;

		// 差分を計算
		Vector3 SubPos{0, 0, 0};
		SubPos = Subtract(GetWorldPos3DReticle(), GetWorldPos());
		// 長さを調整
		SubPos = Nomalize(SubPos);

		Vector3 velocity{0, 0, 0};
		velocity.x = SubPos.x * kBulletSpeed;
		velocity.y = SubPos.y * kBulletSpeed;
		velocity.z = SubPos.z * kBulletSpeed;

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(m_model, this->GetWorldPos(), velocity);

		// 弾を登録
		m_bullets.push_back(newBullet);
	}
}

// 親子関係を結ぶ
void Player::SetParent(const WorldTransform* parent) { m_worldTransform.parent_ = parent; }

void Player::DrawUI() const 
{ 
	m_sprite2DReticle->Draw();
}
