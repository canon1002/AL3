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
#include "DebugCamera.h"
#include <sstream>

// 自作コード インクルード
#include "madeCode/Object/Heder/Player.h"
#include "madeCode/Object/Heder/Enemy.h"
#include "madeCode/Object/Heder/Skydome.h"
#include "madeCode/Object/Heder/RailCamera.h"
#include "madeCode/Setting/Heder/CollisionManager.h"
#include "madeCode/Math/Heder/MatrixCamera.h"

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

	/// <summary>
	/// 敵の弾の登録
	/// </summary>
	/// <param name="enemyBullet"></param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopDate();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	WorldTransform GetWorldTransfome() { return m_worldTransform; }
	MatrixCamera* GetMatrixCamera() { return m_matrixCamera; }

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

	// カメラ行列
	MatrixCamera* m_matrixCamera = new MatrixCamera({1280, 720}); 


	/// <summary>
	/// オブジェクト
	/// <summary>

	// 天球
	Skydome* m_skydome = nullptr;

	// 自キャラ
	Player* m_player = nullptr;
	// 敵
	std::list<Enemy*> m_enemys;
	// 敵の弾
	std::list<EnemyBullet*> m_enemyBullets;
	// 敵の初期座標
	Vector3 enemyStartPos;
	// 敵発生コマンド
	std::stringstream enemyPopCommands;
	// 待機中フラグ
	bool m_isWait;
	//  待機中タイマー
	int32_t m_waitTime;

	// ImGuiで値を入力する変数
	float m_inputPos3A[3] = {0, 0, 0};
	float m_inputPos3B[3] = {0, 0, 0};
	float m_inputPos3C[3] = {0, 0, 0};
	float m_inputPos3D[3] = {0, 0, 0};

};
