#include "Stage.h"

#include <ImGuiManager.h>

void Stage::Init() {
	// モデル読み込み
	model_.reset(Model::CreateFromOBJ("stage"));
	// 行列初期化
	transform_.Initialize();

	//transform_.translation_.z = 2.5f;
	transform_.translation_.y = 0.0f;
	transform_.scale_ = { 16.0f,16.0f,5.0f };
}

void Stage::Update() {

	DebugWindow();


	// 行列更新
	transform_.UpdateMatrix();
}

void Stage::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view); }

void Stage::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("StageWindow");

	if (ImGui::TreeNode("Transform")) {
		ImGui::DragFloat3("scale", &transform_.scale_.x, 0.01f);
		ImGui::DragFloat3("rotation", &transform_.rotation_.x, 0.01f);
		ImGui::DragFloat3("translate", &transform_.translation_.x, 0.01f);

		ImGui::TreePop();
	}

	ImGui::End();
#endif // _DEBUG
}
