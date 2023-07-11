#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "madeCode/Setting/Heder/Collider.h"

/// <summary>
/// ・・ｵ・・ｭ・・｣・・ｩ・・ｮ・ｼｾ
/// </summary>
/// 
class EnemyBullet : public Collider
{

public: // ・・｡・・ｳ・・・・・｢・・ｰ
	EnemyBullet();
	~EnemyBullet();

	/// <summary>
	/// ・・・・・・・・・
	/// </summary>
	/// <param name="model">・・｢・・・・・ｫ</param>
	/// <param name="position">・・・・・・・ｺｧ・ｨ・</param>
	/// <param name="velocity">・・・ｺｦ</param>
	void Initialize(Model* model, const Vector3& position, Vector3& velocity);

	/// <summary>
	/// ・・ｴ・・ｰ・・ｦ・・・
	/// </summary>
	void Update();

	/// <summary>
	/// ・・・・・ｻ・・ｦ・・・
	/// </summary>
	/// <param name="viewProjection">・・・・・･・・ｼ・・・・・ｭ・・ｸ・・ｧ・・ｯ・・ｷ・・ｧ・・ｳ</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// ・ｼｾ・・・・ｯｿ・・ｽ・・・・ｿ・・・・・・・・・・・・ｩ・・・・・・・・・・ｾ・・・・・・・
	/// </summary>
	bool IsDead() const { return m_isDead; }

	// ・・ｯ・・ｼ・・ｫ・・・・ｺｧ・ｨ・・・・・・・・ｾ・
	Vector3 GetWorldPos() override {
		Vector3 result = {};
		result.x = m_worldTransform.matWorld_.m[3][0];
		result.y = m_worldTransform.matWorld_.m[3][1];
		result.z = m_worldTransform.matWorld_.m[3][2];
		return result;
	}

	void OnCollision() override { m_isDead = true; }
	void OnCollision(Collider* collider) override { m_isDead = true; }

	// ・｡・・ｪ・・ｱ・・ｧ(・・ｪ・・・)・・・・・・・ｾ・
	virtual uint32_t GetCollisionAttribute() override { return m_collisionAttribute; }
	// ・｡・・ｪ・・ｱ・・ｧ(・・ｪ・・・)・・・・ｨｭ・ｮ・
	virtual void SetCollisionAttribute(uint32_t collisionAttribute) override {
		m_collisionAttribute = collisionAttribute;
	}
	// ・｡・・ｪ・・・・・・ｹ・・ｯ(・・ｸ・・・)・・・・・・・ｾ・
	virtual uint32_t GetCollisionMask() override { return m_collisionMask; }
	// ・｡・・ｪ・・・・・・ｹ・・ｯ(・・ｸ・・・)・・・・ｨｭ・ｮ・
	virtual void SetCollisionMask(uint32_t collisionMask) override {
		m_collisionMask = collisionMask;
	}


private: // ・・｡・・ｳ・・・・､・・・ｰ
	// ・・ｯ・・ｼ・・ｫ・・・・､・・・・・・・・・ｼ・・ｿ
	WorldTransform m_worldTransform;
	// ・・｢・・・・・ｫ
	Model* m_model = nullptr;
	// ・・・・・ｯ・・ｹ・・・・・｣・・・・・ｳ・・・・・ｫ
	uint32_t m_textureHandle = 0u;
	// ・・・ｺｦ
	Vector3 m_vel;
	// ・ｯｿ・・ｽ<frm>
	static const int32_t kLifeTime = 60 * 5;
	// ・・・・・ｹ・・ｿ・・､・・・・・ｼ
	int32_t m_deathTimer = kLifeTime;
	// ・・・・・ｹ・・・・・ｩ・・ｰ
	bool m_isDead = false;
	// ・｡・・ｪ・・ｱ・・ｧ(・・ｪ・・・)
	uint32_t m_collisionAttribute = kCollisionAttributeEnemyBullet;
	// ・｡・・ｪ・・・・・・ｹ・・ｯ(・・ｸ・・・)
	uint32_t m_collisionMask = kCollisionAttributePlayer + kCollisionAttributePlayerBullet;

};
