#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include <list>
#include "./collider/Collider.h"

// ゲームシーンクラスを前方宣言
class GameScene;

// プレイヤークラスを前方宣言
class Player;

/// <summary>
/// エネミークラス
/// </summary>
class Enemy : public Collider {
public: // 列挙体
	// 行動
	enum class Phase {
		Approach, // 行動
		Leave,    // 離脱
	};

	// 敵の初期行動
	Phase m_phase = Enemy::Phase::Approach;

public: // メンバ関数
	Enemy();
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	/// <param name="velocity">移動量</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

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
	/// 死亡しているか
	/// </summary>
	bool IsDead() const { return m_isDead; }

	/// <summary>
	/// 出現処理
	/// </summary>
	void Boon();

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack();

	// プレイヤーの情報を設定する
	void SetPlayer(Player* player) { m_player = player; }

	// ワールド座標を取得
	Vector3 GetWorldPos() override {
		Vector3 result = {};
		result.x = m_worldTransform.matWorld_.m[3][0];
		result.y = m_worldTransform.matWorld_.m[3][1];
		result.z = m_worldTransform.matWorld_.m[3][2];
		return result;
	}

	void OnCollision() override {}
	void OnCollision(Collider* collider) override { m_isDead = true; }

	//
	virtual uint32_t GetCollisionAttribute() override { return m_collisionAttribute; }
	//
	virtual void SetCollisionAttribute(uint32_t collisionAttribute) override {
		m_collisionAttribute = collisionAttribute;
	}
	//
	virtual uint32_t GetCollisionMask() override { return m_collisionMask; }
	//
	virtual void SetCollisionMask(uint32_t collisionMask) override {
		m_collisionMask = collisionMask;
	}

	void SetGameScene(GameScene* gameScene) { m_gamesSene = gameScene; }

private: // メンバ変数
	// ゲームシーン
	GameScene* m_gamesSene = nullptr;
	// ワールド座標
	WorldTransform m_worldTransform;
	// モデル
	Model* m_model = nullptr;
	// テクスチャ
	uint32_t m_textureHandle = 0u;
	// 移動量
	Vector3 m_vel;

	// 生存時間<frm>
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t m_deathTimer = kLifeTime;
	// 死亡しているか
	bool m_isDead = false;

	// 自分の属性
	uint32_t m_collisionAttribute = kCollisionAttributeEnemy;
	// 自分のマスク
	uint32_t m_collisionMask = kCollisionAttributePlayer + kCollisionAttributePlayerBullet;
	// 敵の弾クラス
	// std::list<EnemyBullet*> m_bullets;
	// クールタイム(攻撃)
	int32_t m_attackCoolTime;
	// プレイヤークラス
	Player* m_player = nullptr;

};
