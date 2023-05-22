#pragma once
#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// �G�L�����̒e
/// </summary>
/// 
class EnemyBullet 
{

public: // �����o�֐�
	EnemyBullet();
	~EnemyBullet();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="position">�������W</param>
	/// <param name="velocity">���x</param>
	void Initialize(Model* model, const Vector3& position, Vector3& velocity);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V����</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// �e���������}�������ǂ����擾����
	/// </summary>
	bool IsDead() const { return m_isDead; }

private: // �����o�ϐ�
	// ���[���h�ϊ��f�[�^
	WorldTransform m_worldTransform;
	// ���f��
	Model* m_model = nullptr;
	// �e�N�X�`���n���h��
	uint32_t m_textureHandle = 0u;
	// ���x
	Vector3 m_vel;
	// ����<frm>
	static const int32_t kLifeTime = 60 * 5;
	// �f�X�^�C�}�[
	int32_t m_deathTimer = kLifeTime;
	// �f�X�t���O
	bool m_isDead = false;
	//�N�[���^�C��
	
};
