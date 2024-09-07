#include "TitleScene.h"

#include "PlayScene.h"

void TitleScene::Init() {
}

void TitleScene::Update() {

	ImGui::Begin("Scene");
	ImGui::Text("Title");
	ImGui::End();

	// スペースを押すとプレイシーンへ
	if (input_->TriggerKey(DIK_SPACE)) {
		nextScene_ = new PlayScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
}

void TitleScene::DrawBackdrop() {
}

void TitleScene::Draw3D() {
}

void TitleScene::DrawOverlay() {
}
