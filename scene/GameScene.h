#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "Skydome.h"
#include "CollisionManager.h"
#include "RailCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	// テクスチャハンドル
	uint32_t m_textureHandle = 0;
	// 3Dモデルデータ
	Model* m_model = nullptr;
	// ワールド座標変換データ
	WorldTransform m_worldTransform;
	// ビュープロジェクション
	ViewProjection m_viewProjection;
	
	//デバッグカメラ
	DebugCamera* m_debugCamera = nullptr;
	// デバッグカメラ有効
	bool m_isDebugCameraAction = false;
	
	// レールカメラ
	RailCamera* m_railCamera = new RailCamera;

	// 衝突マネージャー
	CollisionManager* m_collisionManager = new CollisionManager;

	/// <summary>
	/// オブジェクト
	/// <summary>

	// 天球
	Skydome* m_skydome = nullptr;

	// 自キャラ
	Player* m_player = nullptr;
	// 敵
	std::list<Enemy*> m_enemys;
	// 敵の初期座標
	Vector3 enemyStartPos;

	// ImGuiで値を入力する変数
	float m_inputPos3A[3] = {0, 0, 0};
	float m_inputPos3B[3] = {0, 0, 0};
	float m_inputPos3C[3] = {0, 0, 0};
	float m_inputPos3D[3] = {0, 0, 0};

};
