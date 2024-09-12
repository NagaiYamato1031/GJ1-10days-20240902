#include "HomingBullet.h"

#include <Player/Player.h>

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void HomingBullet::Init() {
	model_.reset(Model::Create());
	transform_.Initialize();
	velocity_.y = -1.0f;
}

void HomingBullet::Update() {
	elapsedFrame++;
	if (aliveLength_ <= Length(transform_.translation_)) {
		// プレイヤーの弾に当たらなかったとき波発生
		endFunction();
		isActive = false;
		return;
	}
	// 一定フレームごとに参照
	if (Length(transform_.translation_) <= aliveLength_ * 0.75f) {
		Vector3 preVel = velocity_;
		velocity_ = Normalize(preVel + Normalize(player_->GetTransform()->translation_ - transform_.translation_));
		velocity_ = velocity_ * 0.5f;
	}
	transform_.translation_ += velocity_;

	// 当たり判定移動
	colSphere_.center = transform_.translation_;

	// 行列更新
	transform_.UpdateMatrix();
}

void HomingBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}
