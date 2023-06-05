#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include <list>
#include "./collider/Collider.h"

// ・・ｪ・ｩ・・・ｯ・・ｩ・・ｹ・・ｮ・・・・・ｹ・ｮ｣・ｨ
class Player;

/// <summary>
/// ・・ｪ・・ｭ・・｣・・ｩ・・ｮ・ｼｾ
/// </summary>
class Enemy : public Collider 
{
public:	// ・・・・・・・ｽ・
	
	// ・｡・・・・・・・・・ｧ・・ｼ・・ｺ
	enum class Phase {
		Approach,	// ・・･・ｿ・
		Leave,		// ・・｢・・ｱ
	};

	// ・・・・・ｧ・・ｼ・・ｺ
	Phase m_phase = Enemy::Phase::Approach;

public: // ・・｡・・ｳ・・・・・｢・・ｰ
	Enemy();
	~Enemy();

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
	/// ・・ｵ・・・・ｯｿ・・ｽ・・・・ｿ・・・・・・・・・・・・ｩ・・・・・・・・・・ｾ・・・・・・・
	/// </summary>
	bool IsDead() const { return m_isDead; }

	/// <summary>
	/// ・・ｵ・・ｮ・・ｺ・・・・・ｦ・・・
	/// </summary>
	void Boon();

	/// <summary>
	/// ・・ｵ・・ｮ・・ｻ・・・・・ｦ・・・
	/// </summary>
	void Attack();

	// ・ｼｾ・・ｪ・・ｹ・・・・・ｮ・・・・ｾ・
	const std::list<EnemyBullet*>& GetBullets() { return m_bullets; }

	// ・・・・・ｬ・・､・・､・・ｼ・・・・・・・ｾ・
	void SetPlayer(Player* player) { m_player = player; }

	// ・・ｯ・・ｼ・・ｫ・・・・ｺｧ・ｨ・・・・・・・・ｾ・
	Vector3 GetWorldPos() override {
		Vector3 result = {};
		result.x = m_worldTransform.matWorld_.m[3][0];
		result.y = m_worldTransform.matWorld_.m[3][1];
		result.z = m_worldTransform.matWorld_.m[3][2];
		return result;
	}

	void OnCollision() override { }
	void OnCollision(Collider* collider) override {}

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
	uint32_t m_collisionAttribute = kCollisionAttributeEnemy;
	// ・｡・・ｪ・・・・・・ｹ・・ｯ(・・ｸ・・・)
	uint32_t m_collisionMask = kCollisionAttributePlayer + kCollisionAttributePlayerBullet;
	// ・ｼｾ
	std::list<EnemyBullet*> m_bullets;
	// ・・ｻ・・・・・ｮ・・ｯ・・ｼ・・ｫ・・ｿ・・､・・
	int32_t m_attackCoolTime;

	// ・・ｪ・・ｭ・・｣・・ｩ
	Player* m_player = nullptr;

};
