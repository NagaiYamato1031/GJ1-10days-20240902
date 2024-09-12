#include "Skydome.h"

#include <ImGuiManager.h>

void Skydome::Init() {
	//モデル読み込み
	model_.reset(Model::CreateFromOBJ("skydome"));
	//行列初期化
	transform_.Initialize();

	transform_.translation_ = {};
	transform_.scale_ = { 100.0f,100.0f,100.0f };
	// 色
	objColor_.Initialize();
}

void Skydome::Update() {
	// デバッグ表示
	DebugWindow();

	//行列更新
	transform_.UpdateMatrix();
}

void Skydome::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view, &objColor_);
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

void Skydome::DirectionTwinkle() {
	if (isToggle_) {
		t += 5;
		if (kColorRange1_ <= t) {
			t = kColorRange1_;
			isToggle_ = !isToggle_;
		}
		Vector3 rgb = { 1.0f,1.0f,1.0f };
		rgb.x = 0.7f - rgb.x * t / 255;
		rgb.y = 0.7f - rgb.y * t / 255;
		rgb.z = 0.7f - rgb.z * t / 255;
		Vector4 color = { rgb.x,rgb.y,rgb.z,1.0f };
		objColor_.SetColor(color);
		objColor_.TransferMatrix();
	}
	else {
		t -= 2;
		if (t <= 0) {
			t = 0;
			isToggle_ = !isToggle_;
		}
		Vector3 rgb = { 1.0f,1.0f,1.0f };
		rgb.x = 0.7f - rgb.x * t / 255;
		rgb.y = 0.7f - rgb.y * t / 255;
		rgb.z = 0.7f - rgb.z * t / 255;
		Vector4 color = { rgb.x,rgb.y,rgb.z,1.0f };
		objColor_.SetColor(color);
		objColor_.TransferMatrix();
	}
}

void Skydome::DirectionRed() {
	if (isToggle_) {
		t += 5;
		if (kColorRange2_ <= t) {
			t = kColorRange2_;
			isToggle_ = !isToggle_;
		}
		Vector3 rgb = { 1.0f,0.3f,0.3f };
		rgb.x = 1.0f - rgb.x * t / 255;
		Vector4 color = { rgb.x,rgb.y,rgb.z,1.0f };
		objColor_.SetColor(color);
		objColor_.TransferMatrix();
	}
	else {
		t -= 2;
		if (t <= 0) {
			t = 0;
			isToggle_ = !isToggle_;
		}
		Vector3 rgb = { 1.0f,0.3f,0.3f };
		rgb.x = 1.0f - rgb.x * t / 255;
		Vector4 color = { rgb.x,rgb.y,rgb.z,1.0f };
		objColor_.SetColor(color);
		objColor_.TransferMatrix();
	}
}

void Skydome::DirectionTurnOff() {
	if (isToggle_) {
		return;
	}
	t += 5;
	if (kColorRange3_ <= t) {
		t = kColorRange3_;
		isToggle_ = !isToggle_;
	}
	Vector3 rgb = { 1.0f,1.0f,1.0f };
	rgb.x = 0.85f - rgb.x * t / 255;
	rgb.y = 0.85f - rgb.y * t / 255;
	rgb.z = 0.85f - rgb.z * t / 255;
	Vector4 color = { rgb.x,rgb.y,rgb.z,1.0f };
	objColor_.SetColor(color);
	objColor_.TransferMatrix();
}
