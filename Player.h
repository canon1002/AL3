#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Player {

public: // メソッド

	Player();
	~Player();

	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);

private: // フィールド

	// ワールド変換データ
	WorldTransform m_worldTransform;
	// モデル
	Model* m_model = nullptr;
	// テクスチャハンドル
	uint32_t m_textureHandle = 0u;

};