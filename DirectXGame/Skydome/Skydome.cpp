#include "Skydome.h"

#include <ImGuiManager.h>

void Skydome::Init() { 
	//モデル読み込み
	model_.reset(Model::CreateFromOBJ("skydome"));
	//行列初期化
	transform_.Initialize();

	transform_.translation_ = {};
	transform_.scale_ = {100.0f,100.0f,100.0f};
}

void Skydome::Update() {
	DebugWindow();
	//行列更新
	transform_.UpdateMatrix();
}

void Skydome::DrawModel(ViewProjection* view) { 
	model_->Draw(transform_, *view);
}

void Skydome::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("SkydomeWindow");

	if (ImGui::TreeNode("Transform")) {
		ImGui::DragFloat3("scale", &transform_.scale_.x, 0.01f);
		ImGui::DragFloat3("rotation", &transform_.rotation_.x, 0.01f);
		ImGui::DragFloat3("translate", &transform_.translation_.x, 0.01f);

		ImGui::TreePop();
	}

	ImGui::End();
#endif // _DEBUG

}
