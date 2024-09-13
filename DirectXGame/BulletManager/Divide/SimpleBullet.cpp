#include "SimpleBullet.h"

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void SimpleBullet::Init() {
	model_.reset(Model::CreateSphere());
	transform_.Initialize();
	velocity_.y = -1.0f;
	objColor_.Initialize();
	color_ = { 0.99f,0.6f,0.84f,1.0f };
	UpdateColor();
}

void SimpleBullet::Update() {
	elapsedFrame++;
	if (aliveFrame_ <= elapsedFrame) {
		isActive = false;
		return;
	}
	transform_.translation_ += velocity_;

	// 当たり判定移動
	colSphere_.center = transform_.translation_;

	// 行列更新
	transform_.UpdateMatrix();
}

void SimpleBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view, &objColor_);
}
