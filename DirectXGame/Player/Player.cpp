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
	// デバッグ情報表示
	DebugWindow();

	// 行列更新
	transform_.UpdateMatrix();
}

void Player::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}

void Player::DebugWindow() {
	ImGui::Begin("PlayerWindow");

	ImGui::DragFloat3("rotation", &transform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("translate", &transform_.translation_.x, 0.01f);

	ImGui::End();
}