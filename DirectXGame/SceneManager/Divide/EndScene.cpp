#include "EndScene.h"

#include "TitleScene.h"

void EndScene::Init() {
}

void EndScene::Update() {
	// デバッグ情報
	DebugWindow();

	// スペースを押すとタイトルシーンへ
	if (input_->TriggerKey(DIK_SPACE)) {
		nextScene_ = new TitleScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
}

void EndScene::DrawBackdrop() {
}

void EndScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("End");
	ImGui::End();
#endif // _DEBUG
}

void EndScene::Draw3D() {
}

void EndScene::DrawOverlay() {
}
