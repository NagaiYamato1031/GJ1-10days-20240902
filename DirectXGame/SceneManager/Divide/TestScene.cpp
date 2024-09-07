#include "TestScene.h"

#include "TitleScene.h"

void TestScene::Init() {
	time = 60;

	// カメラ初期化
	camera_ = std::make_unique<ViewProjection>();
	camera_->Initialize();

	player_ = std::make_unique<Player>();
	player_->Init();
}

void TestScene::Update() {

	ImGui::Begin("Scene");
	ImGui::Text("Test");
	ImGui::DragFloat3("rotation", &camera_->rotation_.x, 0.1f);
	ImGui::DragFloat3("translate", &camera_->translation_.x, 0.01f);
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

	player_->Update();

	camera_->UpdateMatrix();
}

void TestScene::DrawBackdrop() {
}

void TestScene::Draw3D() {
	player_->DrawModel(camera_.get());
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
