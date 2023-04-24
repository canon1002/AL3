#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"

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

	// キーボード入力
	Input* m_input = nullptr;
	// ImGuiで値を入力する変数
	float m_inputPos3[3] = {0, 0, 0};

};