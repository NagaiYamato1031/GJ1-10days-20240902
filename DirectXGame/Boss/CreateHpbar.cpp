#include "CreateHpbar.h"

#include <ImGuiManager.h>
#include <TextureManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;

void CreateHpbar::Init(const Vector3& pos, Model *model ,const float &deg,const float &far_) {
	//破壊フラグ初期化
	isBreak = false;
	model_ = model;
	distance_ = far_;
	pos_ = pos;
	textureHandle_ = TextureManager::Load("HpBar/HpBar.png");
	
	//角度で位置を求める
	float rotate_ = ToRadian(deg);
	velocity_ = Vector3(distance_ * sinf(rotate_), distance_ * cosf(rotate_), 0);


	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(pos_.x + velocity_.x, pos_.y + velocity_.y, pos_.z + velocity_.z);
	worldTransform_.rotation_ = Vector3(0, 0, rotate_);


}

void CreateHpbar::Update() { 




	float rotate_ = worldTransform_.rotation_.z - 0.05f;
	velocity_ = Vector3(distance_ * sinf(rotate_), distance_ * cosf(rotate_), 0);

	worldTransform_.translation_ = Vector3(pos_.x + velocity_.x, pos_.y + velocity_.y, pos_.z + velocity_.z);
	worldTransform_.rotation_ = Vector3(0, 0, rotate_);

	worldTransform_.UpdateMatrix();
}

void CreateHpbar::Draw(const ViewProjection* viewProjection) { 
	model_->Draw(worldTransform_, *viewProjection, textureHandle_); }

void CreateHpbar::NeedReturn() {}

float CreateHpbar::ToRadian(float angle) { return angle * 3.14159265359f / 180.0f; }

