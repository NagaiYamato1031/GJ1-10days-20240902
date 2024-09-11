#include "SimpleBullet.h"

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void SimpleBullet::Init() {
	model_.reset(Model::Create());
	transform_.Initialize();
	velocity_.y = -1.0f;
}

void SimpleBullet::Update() {
	elapsedFrame++;
	if (aliveFrame_ <= elapsedFrame) {
		isActive = false;
		// 緊急の措置として関数を呼ぶ
		collider_->exitLambda(MStage());
		return;
	}
	transform_.translation_ += velocity_;

	// 当たり判定移動
	colSphere_.center = transform_.translation_;

	// 行列更新
	transform_.UpdateMatrix();
}

void SimpleBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}
