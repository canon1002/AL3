#include "madeCode/Object/Heder/RailCamera.h"
#include "madeCode/Math/Heder/Matrix4x4Funk.h"
#include "imguiManager.h"

void RailCamera::Initialize(Vector3 worldPosition, Vector3 radian) {

	m_worldTransform.Initialize();
	m_worldTransform.translation_ = worldPosition;
	m_worldTransform.rotation_ = radian;

	m_viewProjection.farZ = 2000.0f;
	m_viewProjection.Initialize();

}

void RailCamera::Update() {

	// ワールド行列の更新
	m_worldTransform.UpdateMatrix();

	// カメラオブジェクトのワールド座標からビュー行列を計算する
	m_viewProjection.matView = Matrix4x4Funk::Inverse(m_worldTransform.matWorld_);

	// カメラ座標を画面表示する
	ImGui::Begin("Camera");
	m_fTranslation[0] = m_worldTransform.translation_.x;
	m_fTranslation[1] = m_worldTransform.translation_.y;
	m_fTranslation[2] = m_worldTransform.translation_.z;
	m_fRotation[0] = m_worldTransform.rotation_.x;
	m_fRotation[1] = m_worldTransform.rotation_.y;
	m_fRotation[2] = m_worldTransform.rotation_.z;
	ImGui::SliderFloat3("Position", m_fTranslation, 0.0f, 1.0f);
	ImGui::SliderFloat3("Rotation", m_fRotation, 0.0f, 1.0f);
	ImGui::End();

}