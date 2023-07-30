#include "madeCode/Setting/Heder/Collider.h"
#include "madeCode/Math/Heder/Matrix4x4Funk.h"
#include "GameScene.h"
#include "madeCode/Math/Heder/MathTool.h"
#include <ImGui.h>
#include <assert.h>

// 初期化
void Lineofsight::Initialize(Vector3 worldPos) {

	// 受け取ったデータをメンバ変数に格納
	m_model = Model::CreateFromOBJ("line", true);

	// 3Dレティクル用ワールド変換データの初期化
	m_worldTransform.Initialize();

	// レティクル用テクスチャ取得
	m_textureHandle = TextureManager::Load("./Resources/line/line.png");

	// NULLポインタチェック
	assert(m_model);

	// ワールド変換の初期化
	m_worldTransform.Initialize();
	m_worldTransform.translation_ = worldPos;

	// 半径を設定
	SetRadius(0.5f);

}

// 更新
void Lineofsight::Update(const ViewProjection& viewProjection, const WorldTransform& worldTransformPlayer){

	
#pragma region 3D->2D

#pragma region 自機からのワールド座標から3Dレティクルのワールド座標を計算

	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 36.0f;
	// 自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = {0, 0, 1.0f};
	// 自機のワールド座標の回転を反映
	offset = Matrix4x4Funk::Multiply(offset, worldTransformPlayer.matWorld_);
	// ベクトルの長さを整える
	offset = Nomalize(offset);
	offset.x *= kDistancePlayerTo3DReticle;
	offset.y *= kDistancePlayerTo3DReticle;
	offset.z *= kDistancePlayerTo3DReticle;

	// 3Dレティクルの座標を設定
	m_worldTransform.translation_ = Add(this->GetWorldPos(), offset);

#pragma endregion

#pragma region 3dレティクルから2Dレティクルに変換

	// ビューポート行列を作成
	const static Matrix4x4 viewport = Matrix4x4Funk::MakeViewportMatrix(
	    0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);

	Matrix4x4 vp = Matrix4x4Funk::Multiply(
	    Matrix4x4Funk::Multiply(viewProjection.matView, viewProjection.matProjection), viewport);

	Vector3 screenReticlePosition = Matrix4x4Funk::Transform(m_worldTransform.translation_, vp);

	//m_sprite2DReticle->SetPosition({screenReticlePosition.x, screenReticlePosition.y});

	ImGui::Begin("2DReticle");
	ImGui::Text("%f\n%f", screenReticlePosition.x, screenReticlePosition.y);
	ImGui::End();

#pragma endregion

#pragma endregion

#pragma region 2D->3D

	//// マウス座標をレティクルの座標に代入
	// m_sprite2DReticle->SetPosition({(float)mousePosition.x, (float)mousePosition.y});

	// const static Matrix4x4 viewport = Matrix4x4Funk::MakeViewportMatrix(
	//     0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);

	//// 先に行列を合成する(逆行列化→合成はNG)
	// Matrix4x4 VPV = Matrix4x4Funk::Multiply(
	//     Matrix4x4Funk::Multiply(viewProjection.matView, viewProjection.matProjection), viewport);
	//// 逆行列化
	// Matrix4x4 inVPV = Matrix4x4Funk::Inverse(VPV);

	// Vector3 posNear = {
	//     m_sprite2DReticle->GetPosition().x, m_sprite2DReticle->GetPosition().y, 0.0f};
	// Vector3 posFar = {m_sprite2DReticle->GetPosition().x,
	// m_sprite2DReticle->GetPosition().y, 1.0f}; posNear = Matrix4x4Funk::Transform(posNear,
	// inVPV); posFar = Matrix4x4Funk::Transform(posFar, inVPV);

	// Vector3 mouseDirction = Subtract(posFar, posNear);

	//// 自機から3Dレティクルへの距離
	// const float kDistanceTestObject = 120.0f;

	//// ベクトルの長さを整える
	// mouseDirction = Nomalize(mouseDirction);
	// mouseDirction.x *= kDistanceTestObject;
	// mouseDirction.y *= kDistanceTestObject;
	// mouseDirction.z *= kDistanceTestObject;
	//// 3Dレティクルの座標を設定
	// m_worldTransform3DReticle.translation_ = Add(posNear, mouseDirction);

	// static Vector3 ndcStart =
	// Matrix4x4Funk::Transform(m_worldTransform.translation_,Matrix4x4Funk::Multiply(viewProjection.matProjection,
	// viewProjection.matView)); static Vector3 screenStart = Matrix4x4Funk::Transform(ndcStart,
	// viewport);

	// static Vector3 ndcEnd =
	// Matrix4x4Funk::Transform(m_worldTransform3DReticle.translation_,Matrix4x4Funk::Multiply(viewProjection.matProjection,
	// viewProjection.matView)); static Vector3 screenEnd = Matrix4x4Funk::Transform(ndcEnd,
	// viewport);
	//

	// ImGui::Begin("Player");
	// ImGui::Text(
	//     "2DReticle:(%f,%f)", m_sprite2DReticle->GetPosition().x,
	//     m_sprite2DReticle->GetPosition().y);
	// ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	// ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	// ImGui::Text(
	//     "3DReticle:(%+.2f,%+.2f,%+.2f)", m_worldTransform3DReticle.translation_.x,
	//     m_worldTransform3DReticle.translation_.y, m_worldTransform3DReticle.translation_.z);
	// ImGui::Text("ShotCoolTime:(%d)", m_shotCoolTime);
	// ImGui::End();

#pragma endregion


	// 3Dレティクルの座標を更新転送
	m_worldTransform.UpdateMatrix();

}

// 描画
void Lineofsight::Draw(const ViewProjection& viewProjection) const {

	// 3Dモデルを描画
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);

}
