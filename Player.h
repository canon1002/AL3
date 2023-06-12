#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>
#include "./collider/Collider.h"

class Player : public Collider 
{
public: // メソッド
	Player();
	~Player();

	void Initialize(Model* model, uint32_t textureHandle, Vector3 worldPos);
	void Update();
	void Draw(ViewProjection viewProjection);
	
	// 旋回(回転)
	void Rotate();
	// 攻撃
	void Attack();
	// 弾リストの取得
	const std::list<PlayerBullet*>& GetBullets() { return m_bullets; }
	// ワールド座標を取得
	Vector3 GetWorldPos()override{
		Vector3 result = {};
		result.x = m_worldTransform.matWorld_.m[3][0];
		result.y = m_worldTransform.matWorld_.m[3][1];
		result.z = m_worldTransform.matWorld_.m[3][2];
		return result;
	}

	void OnCollision()override {}
	void OnCollision(Collider* collider) override { }

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

	// 入力処理を取得
	Input* GetInput() { return m_input; }

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

private: // フィールド

	// ワールド変換データ
	WorldTransform m_worldTransform;
	// モデル
	Model* m_model = nullptr;
	// テクスチャハンドル
	uint32_t m_textureHandle = 0u;
	// デスフラグ
	bool m_isDead = false;

	// 衝突属性(自分)
	uint32_t m_collisionAttribute = kCollisionAttributePlayer;
	// 衝突マスク(相手)
	uint32_t m_collisionMask = kCollisionAttributeEnemy + kCollisionAttributeEnemyBullet;
	// 弾
	std::list<PlayerBullet*> m_bullets;

	// キーボード入力
	Input* m_input = nullptr;


	

};