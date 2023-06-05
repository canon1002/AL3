#pragma once
#include <Model.h>
#include <WorldTransform.h>

/// <summary>
/// 天球
/// </summary>
class Skydome 
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Skydome();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection viewProjection);

private:

	// ワールド変換データ
	WorldTransform m_worldTransform;
	// モデル
	Model* m_model = nullptr;
	// テクスチャ
	uint32_t m_textureHandle = 0u;

};
