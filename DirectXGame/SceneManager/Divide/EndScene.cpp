#include "EndScene.h"

#include "TitleScene.h"

#include "PlayScene.h"

#include "TextureManager.h"

EndScene::EndScene() {}

EndScene::~EndScene() {

	delete spriteT_;
	delete spriteP_;
}

void EndScene::Init() {

	selectTitle_ = true;

	toTitlePosition_ = { 640, 500, 0 };
	toPlayPosition_ = { 640, 600, 0 };

	//textHandleTitle_ = TextureManager::GetInstance()->Load("");
	//textHandlePlay_ = TextureManager::GetInstance()->Load("");

	spriteT_ = Sprite::Create(textHandleTitle_, { toTitlePosition_.x, toTitlePosition_.y });
	spriteP_ = Sprite::Create(textHandlePlay_, { toPlayPosition_.x, toPlayPosition_.y });

}

void EndScene::Update() {
	// デバッグ情報
	DebugWindow();

	// 左はタイトル
	// 上下に変えるかも
	if (input_->TriggerKey(DIK_A)) {
		selectTitle_ = true;
	}
	else if (input_->TriggerKey(DIK_D)) {
		selectTitle_ = false;
	}

	// スペースを押す
	if (input_->TriggerKey(DIK_SPACE)) {
		// タイトルへ
		if (selectTitle_ == true) {
			nextScene_ = new TitleScene;
			sceneFlag_.isTransition_ = true;
			sceneFlag_.allEnd_ = true;
		}
		// プレイシーンへ
		else {
			nextScene_ = new PlayScene;
			sceneFlag_.isTransition_ = true;
			sceneFlag_.allEnd_ = true;
		}
	}
}

void EndScene::DrawBackdrop() {
}


void EndScene::Draw3D() {
}

void EndScene::DrawOverlay() {
	// タイトルへ向かう画像
	spriteT_->Draw();
	// プレイシーンへ向かう画像
	spriteP_->Draw();
}

void EndScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("End");
	ImGui::End();
#endif // _DEBUG
}