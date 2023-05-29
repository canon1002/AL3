#include "EnemyBullet.h"
#include <assert.h>

/// �R���X�g���N�^
EnemyBullet::EnemyBullet() {}

/// �f�X�g���N�^
EnemyBullet::~EnemyBullet() {}

/// ������
void EnemyBullet::Initialize(Model* model, const Vector3& position, Vector3& velocity) {

	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �󂯎�����f�[�^�������o�ϐ��Ɋi�[
	m_model = model;
	// �e�N�X�`���ǂݍ���
	m_textureHandle = TextureManager::Load("Bullet.png");

	// ���[���h�g�����X�t�H�[���̏�����
	m_worldTransform.Initialize();
	// �����Ŏ󂯎�����������W���Z�b�g
	m_worldTransform.translation_ = position;

	// �����Ŏ󂯎�������x�������o�ϐ��ɃZ�b�g
	m_vel = velocity;
}

/// �X�V����
void EnemyBullet::Update() {

	// ���Ԍo�߂Ńf�X
	if (--m_deathTimer <= 0) {
		m_isDead = true;
	}

	// ���W���ړ�������
	m_worldTransform.translation_.x += m_vel.x;
	m_worldTransform.translation_.y += m_vel.y;
	m_worldTransform.translation_.z += m_vel.z;

	// �s����v�Z�E�]��
	m_worldTransform.UpdateMatrix();
}

/// �`�揈��
void EnemyBullet::Draw(const ViewProjection& viewProjection) {

	// ���f���̕`��
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);
}