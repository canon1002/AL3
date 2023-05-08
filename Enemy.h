#pragma once
#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// 自キャラの弾
/// </summary>
class Enemy {

public: // メンバ関数
	Enemy();
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	/// <param name="velocity">速度</param>
	void Initialize(Model* model, const Vector3& position, Vector3& velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 敵が寿命を迎えたかどうか取得する
	/// </summary>
	bool IsDead() const { return m_isDead; }

	/// <summary>
	/// 敵の発生処理
	/// </summary>
	void Boon();

private: // メンバ変数
	// ワールド変換データ
	WorldTransform m_worldTransform;
	// モデル
	Model* m_model = nullptr;
	// テクスチャハンドル
	uint32_t m_textureHandle = 0u;
	// 速度
	Vector3 m_vel;
	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t m_deathTimer = kLifeTime;
	// デスフラグ
	bool m_isDead = false;
};
