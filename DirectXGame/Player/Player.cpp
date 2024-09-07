#include "Player.h"

#include <ImGuiManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;

void Player::Init() {
	// モデル読み込み
	model_ = Model::CreateFromOBJ("cube");
	// 初期化
	transform_.Initialize();
	// 北側から始まる
	transform_.translation_.y = kPaddingCenter_;
}

void Player::Update() {
	// デバッグ情報表示
	DebugWindow();

	transform_.translation_.x = std::cosf(theta_) * kPaddingCenter_;
	transform_.translation_.y = std::sinf(theta_) * kPaddingCenter_;

	// 行列更新
	transform_.UpdateMatrix();
}

void Player::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}

void Player::DebugWindow() {
	ImGui::Begin("PlayerWindow");

	ImGui::DragFloat("theta", &theta_, 0.001f);
	if (theta_ < -3.14f * 2){
		theta_ += 3.14f * 2;
	}else if (3.14f * 2 < theta_){
		theta_ -= 3.14f * 2;
	}
	ImGui::DragFloat3("rotation", &transform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("translate", &transform_.translation_.x, 0.01f);

	ImGui::Separator();

	ImGui::DragFloat("Padding", &kPaddingCenter_, 0.1f);

	ImGui::End();
}