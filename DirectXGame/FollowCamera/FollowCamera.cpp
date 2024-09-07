#include "FollowCamera.h"

#include<cmath>

#include <ImGuiManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;

void FollowCamera::Init() {
	// カメラ初期化
	camera_ = std::make_unique<ViewProjection>();
	camera_->Initialize();
	camera_->translation_.z = -100.0f;
}

void FollowCamera::Update() {
	// デバッグ情報表示
	DebguWindow();

	// ターゲットの位置から最適なカメラ位置を求める
	Vector3 position = target_->translation_;
	position.z += kOffset.z;
	// 原点に近くなるように角度を取得する
	Vector2 normal = Normalize(Vector2(position.x, position.y));
	// 角度を計算
	float theta = std::atan2(normal.y, normal.x);
	Vector2 angle = { std::cosf(theta),std::sinf(theta) };
	// 少し戻す
	offset = { angle.x * kOffset.y, angle.y * kOffset.y };

	// 結果を反映
	position += offset;

	// ターゲットに追従
	camera_->translation_ = position;

	// カメラ更新
	camera_->UpdateMatrix();
}

void FollowCamera::DebguWindow() {
	ImGui::Begin("FollowCamera");

	ImGui::DragFloat3("InitPosition", &kOffset.x, 0.1f);
	ImGui::DragFloat3("offset", &offset.x, 0.1f);

	ImGui::Separator();

	ImGui::DragFloat3("rotation", &camera_->rotation_.x, 0.01f);
	ImGui::DragFloat3("translate", &camera_->translation_.x, 0.01f);

	ImGui::End();
}
