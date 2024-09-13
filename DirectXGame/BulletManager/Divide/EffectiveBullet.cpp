#include "EffectiveBullet.h"

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void EffectiveBullet::Init() {
	model_.reset(Model::CreateFromOBJ("BossEnemy"));
	transform_.Initialize();
	velocity_.y = -1.0f;
	objColor_.Initialize();
	color_ = { 1.0f,0.75f,0.0f,1.0f };
	UpdateColor();
	particleEffects_.Init();
}

void EffectiveBullet::Update() {
	elapsedFrame++;
	// 一定時間経った後に動き始める
	if (elapsedFrame <= 60) {
		// ボスの周りを回るように動く
		Vector3 norm = Normalize(velocity_);
		// ボスの半径以上を入れる
		transform_.translation_.x = norm.x * 12.0f;
		transform_.translation_.y = norm.y * 12.0f;
		// 当たり判定移動
		colSphere_.center = transform_.translation_;
		// 行列更新
		transform_.UpdateMatrix();
		return;
	}
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
	particleEffects_.CreateParticle_FootpaceBullet(transform_.translation_, transform_.rotation_.z);
	particleEffects_.UpdateParticle();

	// 行列更新
	transform_.UpdateMatrix();
}

void EffectiveBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view, &objColor_);
	particleEffects_.DrawParticle(view);
}
