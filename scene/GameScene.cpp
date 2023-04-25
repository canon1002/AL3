#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {

	// 3Dモデルデータの開放
	delete m_model;
	// 自キャラの開放
	delete m_player;
	// デバッグカメラの開放
	delete m_debugCamera;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャ読み込み
	m_textureHandle = TextureManager::Load("white1x1.png");
	// 3Dモデルデータの作成
	m_model = Model::Create();
	// ビュープロジェクションの初期化
	m_viewProjection.Initialize();
	// 自キャラの生成
	m_player = new Player();
	// 自キャラの初期化
	m_player->Initialize(m_model, m_textureHandle);
	// デバッグカメラの生成
	m_debugCamera = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&m_viewProjection);

}

void GameScene::Update() {

	// 自キャラの更新
	m_player->Update();
	
	// デバッグカメラの有効化
	#ifdef _DEBUG

	// 数字の0キーを押すとデバックカメラを起動する
	if (input_->TriggerKey(DIK_0)) {
		m_isDebugCameraAction = true;
	}

#endif

	// カメラの処理
	if (m_isDebugCameraAction) {
		// デバッグカメラの更新
		m_debugCamera->Update();
		m_viewProjection.matView = m_debugCamera->GetViewProjection().matView;
		m_viewProjection.matProjection = m_debugCamera->GetViewProjection().matProjection;
		// ビュープロジェクションの転送
		m_viewProjection.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		m_viewProjection.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 自キャラの描画処理
	m_player->Draw(m_viewProjection);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
