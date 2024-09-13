#include "EndScene.h"

#include "TitleScene.h"

#include "PlayScene.h"

#include "TextureManager.h"

EndScene::EndScene() {}

EndScene::~EndScene() {}

void EndScene::Init() {

	// カメラ初期化
	camera_.Initialize();
	camera_.translation_.z = -1.0f;
	camera_.UpdateMatrix();
	// スカイドーム初期化
	skydome_.Init();

	textHandleTitle_ = TextureManager::GetInstance()->Load("title/Title.png");

	spriteTitlePosition_ = { 1280 * 0.5f, 720 * 0.5f };
	spriteTitle_.reset(Sprite::Create(textHandleTitle_, spriteTitlePosition_));
	spriteTitle_->SetAnchorPoint({ 0.5f,0.5f });
	spriteTitle_->SetPosition(spriteTitlePosition_);
}

void EndScene::Update() {
	// デバッグ情報
	DebugWindow();

	//// 左はタイトル
	//// 上下に変えるかも
	//if (input_->TriggerKey(DIK_A)) {
	//	selectTitle_ = true;
	//}
	//else if (input_->TriggerKey(DIK_D)) {
	//	selectTitle_ = false;
	//}

	// スペースを押す
	if (input_->TriggerKey(DIK_SPACE)) {
		// タイトルへ
		nextScene_ = new TitleScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
	// カメラ更新
	camera_.UpdateMatrix();
}

void EndScene::DrawBackdrop() {
}


void EndScene::Draw3D() {
	skydome_.DrawModel(&camera_);
}

void EndScene::DrawOverlay() {
	// タイトルへ向かう画像
	spriteTitle_->Draw();
}

void EndScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("End");
	ImGui::DragFloat3("cameraPos", &camera_.translation_.x, 1.0f);
	ImGui::End();
#endif // _DEBUG
}