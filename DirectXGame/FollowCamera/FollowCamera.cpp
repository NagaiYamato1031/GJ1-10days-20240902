#include "FollowCamera.h"

#include <ImGuiManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;

void FollowCamera::Init() {
	// カメラ初期化
	camera_ = std::make_unique<ViewProjection>();
	camera_->Initialize();
}

void FollowCamera::Update() {
	// デバッグ情報表示
	DebguWindow();

	// ターゲットに追従
	camera_->translation_ = target_->translation_ + offset;


	// カメラ更新
	camera_->UpdateMatrix();
}

void FollowCamera::DebguWindow() {
	ImGui::Begin("FollowCamera");

	ImGui::DragFloat3("offset", &offset.x, 0.1f);

	ImGui::Separator();

	ImGui::DragFloat3("rotation", &camera_->rotation_.x, 0.01f);
	ImGui::DragFloat3("translate", &camera_->translation_.x, 0.01f);

	ImGui::End();
}
