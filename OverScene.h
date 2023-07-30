#pragma once

// エンジンコード インクルード
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class OverScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	OverScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OverScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool GetSceneChange();

	private:

		DirectXCommon* dxCommon_ = nullptr;
	    Input* input_ = nullptr;
	    Audio* audio_ = nullptr;

		bool isChange;

};
