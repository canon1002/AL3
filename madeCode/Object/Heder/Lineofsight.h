#include "madeCode/Setting/Heder/Collider.h"
#include "Model.h"
#include "Sprite.h"
#include "WorldTransform.h"
#include <list>


class Lineofsight : public Collider 
{
public: // メソッド

	void Initialize(Vector3 worldPos);
	void Update(const ViewProjection& viewProjection, const WorldTransform& worldTransformPlayer);
	void Draw(const ViewProjection& viewProjection) const;

	// ワールド座標を取得
	Vector3 GetWorldPos() override {
		Vector3 result = {};
		result.x = m_worldTransform.matWorld_.m[3][0];
		result.y = m_worldTransform.matWorld_.m[3][1];
		result.z = m_worldTransform.matWorld_.m[3][2];
		return result;
	}

	void OnCollision() override {}
	void OnCollision(Collider* collider) override {}

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

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

protected:

	// ワールド変換データ
	WorldTransform m_worldTransform;
	// モデル
	Model* m_model = nullptr;
	// テクスチャハンドル
	uint32_t m_textureHandle = 0u;

	// 衝突属性(自分)
	uint32_t m_collisionAttribute = kCollisionAttributePlayer;
	// 衝突マスク(相手)
	uint32_t m_collisionMask = kCollisionAttributeEnemy + kCollisionAttributeEnemyBullet;

};