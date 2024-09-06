#include "TestScene.h"

#include "TitleScene.h"

void TestScene::Init() {
}

void TestScene::Update() {


	ImGui::Begin("Scene");
	ImGui::Text("Test");
	ImGui::End();


	if (input_->TriggerKey(DIK_SPACE)) {
		nextScene_ = new TitleScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
}

void TestScene::DrawBackdrop() {
}

void TestScene::Draw3D() {
}

void TestScene::DrawOverlay() {
}
