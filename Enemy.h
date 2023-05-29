#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include <list>

// 自機クラスの前方宣言
class Player;

/// <summary>
/// 自キャラの弾
/// </summary>
class Enemy {

public:	// 列挙体
	
	// 行動フェーズ
	enum class Phase {
		Approach,	// 接近
		Leave,		// 離脱
	};

	// フェーズ
	Phase m_phase = Enemy::Phase::Approach;

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

	/// <summary>
	/// 敵の攻撃処理
	/// </summary>
	void Attack();

	// プレイヤーを取得
	void SetPlayer(Player* player) { m_player = player; }

	// ワールド座標を取得
	Vector3 GetWorldPos();

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
	// 弾
	std::list<EnemyBullet*> m_bullets;
	// 攻撃のクールタイム
	int32_t m_attackCoolTime;

	// 自キャラ
	Player* m_player = nullptr;

};
