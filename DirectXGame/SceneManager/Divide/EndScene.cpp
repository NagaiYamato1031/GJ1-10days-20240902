#include "EndScene.h"

#include "TitleScene.h"

#include "PlayScene.h"

void EndScene::Init() {
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

void EndScene::DebugWindow() {
	ImGui::Begin("Scene");
	ImGui::Text("End");
	ImGui::End();
}

void EndScene::Draw3D() {
}

void EndScene::DrawOverlay() {
}
