#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ClrarScene.h"
#include "OverScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	TitleScene* titleScene = nullptr;
	GameScene* gameScene = nullptr;
	ClearScene* clearScene = nullptr;
	OverScene* overScene = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"LD2A_12_ワタナベ_ユウタ_AL3");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	XINPUT_STATE joyState;

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// タイトルシーンの初期化
	titleScene = new TitleScene;
	titleScene->Initialize();

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

	clearScene = new ClearScene;
	clearScene->Initialize();
	overScene = new OverScene;
	overScene->Initialize();

	// シーン切り替え変数
	int sceneNumber = 0;

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();

		switch (sceneNumber) {
		case 0:

			// タイトルシーンの処理
			titleScene->Update();
			
			if (titleScene->GetSceneChange()) {
				sceneNumber = 1;
			}

			break;
		case 1:

			// ゲームシーンの毎フレーム処理
			gameScene->Update();

			break;
		case 2:

			// ゲームシーンの毎フレーム処理
			gameScene->Update();

			break;
		case 3:

			// ゲームシーンの毎フレーム処理
			gameScene->Update();

			break;
		default:
			break;
		}

		

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		
		switch (sceneNumber) {
		case 0:

			// タイトルシーン
			titleScene->Draw();

			break;
		case 1:

			// ゲームシーン
			gameScene->Draw();

			break;

		default:
			break;
		}

		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();

		// ESCキー入力でウィンドウを閉じる
		if (input->PushKey(DIK_ESCAPE)) {
			break;
		}
	}

	// 各種解放
	SafeDelete(gameScene);
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}