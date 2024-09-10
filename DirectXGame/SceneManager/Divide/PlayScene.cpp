#include "PlayScene.h"

#include "EndScene.h"

void PlayScene::Init() {
}

void PlayScene::Update() {
	// デバッグ情報
	DebugWindow();

	// スペースを押すとエンドシーンへ
	if (input_->TriggerKey(DIK_SPACE)) {
		nextScene_ = new EndScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
}

void PlayScene::DrawBackdrop() {
}

void PlayScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("Play");
	ImGui::End();
#endif // _DEBUG
}

void PlayScene::Draw3D() {
}

void PlayScene::DrawOverlay() {
}
