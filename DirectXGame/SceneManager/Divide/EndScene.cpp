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

	SelectFrag_T = false;
	SelectFrag_P = false;

	TMoziPos = {640, 500, 0};
	PMoziPos = {640, 600, 0};

	spriteT_ = Sprite::Create(textureHandle_T, {TMoziPos.x, TMoziPos.y});
	spriteP_ = Sprite::Create(textureHandle_P, {PMoziPos.x, PMoziPos.y});

}

void EndScene::Update() {
	// デバッグ情報
	DebugWindow();

	if (input_->TriggerKey(DIK_A)) {

		SelectFrag_T = true;
	} 
	else if (input_->TriggerKey(DIK_D)) {

		SelectFrag_P = true;
	} 

	if (SelectFrag_T == true) {
		// スペースを押すとタイトルシーンへ
		if (input_->TriggerKey(DIK_SPACE)) {
			nextScene_ = new TitleScene;
			sceneFlag_.isTransition_ = true;
			sceneFlag_.allEnd_ = true;

			SelectFrag_T = false;
		}
	}

	else if (SelectFrag_P == true) {
		// スペースを押すとプレイシーンへ
		if (input_->TriggerKey(DIK_SPACE)) {
			nextScene_ = new PlayScene;
			sceneFlag_.isTransition_ = true;
			sceneFlag_.allEnd_ = true;

			SelectFrag_P = false;
		}
	}
}

void EndScene::DrawBackdrop() {
}


void EndScene::Draw3D() {
}

void EndScene::DrawOverlay() {

	if (SelectFrag_T == true) {

		spriteT_->Draw();
	}

	if (SelectFrag_P == true) {

		spriteP_->Draw();
	}
}

void EndScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("End");
	ImGui::End();
#endif // _DEBUG
}