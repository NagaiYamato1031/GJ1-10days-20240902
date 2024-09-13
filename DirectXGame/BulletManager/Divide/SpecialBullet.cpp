#include "SpecialBullet.h"

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void SpecialBullet::Init() {
	model_.reset(Model::Create());
	transform_.Initialize();
	velocity_.y = -1.0f;
	particleEffect_.Init();
}

void SpecialBullet::Update() {
	if (hp_ <= 0) {
		isActive = false;
		return;
	}
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
	//パーティクル生成
	particleEffect_.CreateParticle_BBBullet(transform_.translation_, transform_.rotation_.z);
	particleEffect_.UpdateParticle();
	// 行列更新
	transform_.UpdateMatrix();
}

void SpecialBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
	particleEffect_.DrawParticle(view);
}
