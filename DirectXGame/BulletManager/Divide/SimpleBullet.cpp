#include "SimpleBullet.h"

using namespace ACJPN;
using namespace ACJPN::Math;

void SimpleBullet::Init() {
	model_.reset(Model::Create());
	transform_.Initialize();
	velocity_.y = -1.0f;
}

void SimpleBullet::Update() {
	elapsedFrame++;
	if (60 <= elapsedFrame) {
		isActive = false;
		return;
	}
	transform_.translation_ += velocity_;
	transform_.UpdateMatrix();
}

void SimpleBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}
