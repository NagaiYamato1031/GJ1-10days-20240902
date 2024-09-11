#include "EffectiveBullet.h"

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void EffectiveBullet::Init() {
	model_.reset(Model::Create());
	transform_.Initialize();
	velocity_.y = -1.0f;
}

void EffectiveBullet::Update() {
	elapsedFrame++;
	if (aliveLength_ <= Length(transform_.translation_)) {
		// プレイヤーの弾に当たらなかったとき波発生
		endFunction();
		isActive = false;
		return;
	}
	transform_.translation_ += velocity_;

	// 当たり判定移動
	colSphere_.center = transform_.translation_;

	// 行列更新
	transform_.UpdateMatrix();
}

void EffectiveBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}
