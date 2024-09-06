#include "TestScene.h"

#include "TitleScene.h"

void TestScene::Init() {
	time = 60;
}

void TestScene::Update() {


	ImGui::Begin("Scene");
	ImGui::Text("Test");
	ImGui::End();
	// 遷移中はほかのことをしない
	if (sceneFlag_.isTransition_) {
		TransitionUpdate();
		return;
	}
	// スペースを押すとタイトルへ
	if (input_->TriggerKey(DIK_SPACE)) {
		nextScene_ = new TitleScene;
		sceneFlag_.isTransition_ = true;
	}
}

void TestScene::DrawBackdrop() {
}

void TestScene::Draw3D() {
}

void TestScene::DrawOverlay() {
}

void TestScene::TransitionUpdate() {
	// 時間で終了時間を決めることもできる
	time--;
	// フラグで管理していれば終了がわかる
	if (time <= 0) {
		sceneFlag_.allEnd_ = true;
		// これ以上処理しない
		return;
	}
	// 遷移中の処理


}
