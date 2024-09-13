#include "HomingBullet.h"

#include <Player/Player.h>

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void HomingBullet::Init() {
	model_.reset(Model::CreateFromOBJ("BossEnemy"));
	transform_.Initialize();
	velocity_.y = -1.0f;
	particleEffect_.Init();
}

void HomingBullet::Update() {
	elapsedFrame++;
	// 一定時間経った後に動き始める
	if (elapsedFrame <= 60) {
		Vector3 norm = Normalize(player_->GetTransform()->translation_ - transform_.translation_);
		//velocity_ = velocity_ * speed_;
		// ボスの周りを回るように動く
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
	// 一定フレームごとに参照
	if (Length(transform_.translation_) <= aliveLength_ * 0.8f) {
		velocity_ = Normalize(player_->GetTransform()->translation_ - transform_.translation_);
		velocity_ = velocity_ * speed_;
	}
	transform_.translation_ += velocity_;

	// 当たり判定移動
	colSphere_.center = transform_.translation_;
	//パーティクル生成
	particleEffect_.CreateParticle_ChaserBullet(transform_.translation_, transform_.rotation_.z);
	particleEffect_.UpdateParticle();
	// 行列更新
	transform_.UpdateMatrix();
}

void HomingBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
	particleEffect_.DrawParticle(view);
}
