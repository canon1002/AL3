#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>

/// <summary>
/// レールカメラ
/// </summary>
class RailCamera 
{
public:

	void Initialize(Vector3 worldPosition,Vector3 radian);
	void Update();

	void SetViewProjection(ViewProjection viewProjection) { m_viewProjection = viewProjection; }
	ViewProjection GetViewProjection() { return m_viewProjection; }

	void SetWorldTransform(WorldTransform worldTransform) { m_worldTransform = worldTransform; }
	const WorldTransform& GetWorldTransform() { return m_worldTransform; }
	

private:

	// ワールド変換データ
	WorldTransform m_worldTransform;
	// ビュープロジェクション
	ViewProjection m_viewProjection;
	// ImGui用の変数
	float m_fTranslation[3] = {0, 0, 0};
	float m_fRotation[3] = {0, 0, 0};

};