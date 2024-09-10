#include "TitleScene.h"

#include "PlayScene.h"

void TitleScene::Init() {
}

void TitleScene::Update() {
	// デバッグ情報
	DebugWindow();

	// スペースを押すとプレイシーンへ
	if (input_->TriggerKey(DIK_RETURN)) {
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

void TitleScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("Title");
	ImGui::End();
#endif // _DEBUG
}
