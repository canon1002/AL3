#include "madeCode/Object/Heder/Skydome.h"
#include <assert.h>

Skydome::Skydome() { }

void Skydome::Initialize() {

	// 受け取ったデータをメンバ変数に格納
	m_model = Model::CreateFromOBJ("skydome", true);
	
	// ワールド変換の初期化
	m_worldTransform.Initialize();
	m_worldTransform.matWorld_.m[3][0] = 0.0f;
	m_worldTransform.matWorld_.m[3][1] = 0.0f;
	m_worldTransform.matWorld_.m[3][2] = 0.0f;
}


void Skydome::Update() {

	// 行列を計算・転送
	m_worldTransform.UpdateMatrix();

}


void Skydome::Draw(ViewProjection viewProjection) {

	// 3Dモデルを描画
	m_model->Draw(m_worldTransform, viewProjection);
}