#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "./collider/Collider.h"

/// <summary>
/// 自キャラの弾
/// </summary>
class PlayerBullet : public Collider
{
public: // メンバ関数

	PlayerBullet();
	~PlayerBullet();

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
	/// 弾が寿命を迎えたかどうか取得する
	/// </summary>
	bool IsDead() const { return m_isDead; }

	// ワールド座標を取得
	Vector3 GetWorldPos() override {
		Vector3 result = {};
		result.x = m_worldTransform.translation_.x;
		result.y = m_worldTransform.translation_.y;
		result.z = m_worldTransform.translation_.z;
		return result;
	}

	void OnCollision() override { m_isDead = true; }
	void OnCollision(Collider* collider) override { m_isDead = true; }

	// 衝突属性(自分)を取得
	virtual uint32_t GetCollisionAttribute() override { return m_collisionAttribute; }
	// 衝突属性(自分)を設定
	virtual void SetCollisionAttribute(uint32_t collisionAttribute) override {
		m_collisionAttribute = collisionAttribute;
	}
	// 衝突マスク(相手)を取得
	virtual uint32_t GetCollisionMask() override { return m_collisionMask; }
	// 衝突マスク(相手)を設定
	virtual void SetCollisionMask(uint32_t collisionMask) override {
		m_collisionMask = collisionMask;
	}


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
	// 衝突属性(自分)
	uint32_t m_collisionAttribute = kCollisionAttributePlayerBullet;
	// 衝突マスク(相手)
	uint32_t m_collisionMask = kCollisionAttributeEnemy + kCollisionAttributeEnemyBullet;
	

};

