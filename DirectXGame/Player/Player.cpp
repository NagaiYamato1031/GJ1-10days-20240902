#include "Player.h"

#include <ImGuiManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;

void Player::Init() {
	// モデル読み込み
	model_ = Model::CreateFromOBJ("cube");
	// 初期化
	transform_.Initialize();
}

void Player::Update() {
	ImGui::Begin("PlayerWindow");

	ImGui::DragFloat3("traslate", &transform_.translation_.x, 0.1f);

	ImGui::End();

	transform_.UpdateMatrix();
}

void Player::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}
