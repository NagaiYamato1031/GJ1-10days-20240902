#include "BoundBullet.h"

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void BoundBullet::Init() {
	model_.reset(Model::CreateFromOBJ("BossEnemy"));
	transform_.Initialize();
	velocity_.y = -1.0f;
	isOutMove_ = true;
	objColor_.Initialize();
	color_ = { 0.3f,0.3f,0.3f,1.0f };
	UpdateColor();
}

void BoundBullet::Update() {
	elapsedFrame++;
	// 一定時間経った後に動き始める
	if (elapsedFrame <= 60) {
		// ボスの周りを回るように動く
		direct_ = Normalize(velocity_);
		// ボスの半径以上を入れる
		transform_.translation_.x = direct_.x * 12.0f;
		transform_.translation_.y = direct_.y * 12.0f;
		// 当たり判定移動
		colSphere_.center = transform_.translation_;
		// 行列更新
		transform_.UpdateMatrix();
		return;
	}

	// ステージにぶつかった時の処理
	if (aliveLength_ <= Length(transform_.translation_)) {
		// プレイヤーの弾に当たらなかったとして波発生
		endFunction();
		DecreaseHP(1);
		// 消えてたら
		if (!isActive) {
			return;
		}
		isOutMove_ = false;
		// 速度を反転
		velocity_ = direct_ * -0.75f;
	}
	// 半分に達していたら
	if (!isOutMove_) {
		velocity_ += direct_ * 0.01f;
	}
	transform_.translation_ += velocity_;

	// 当たり判定移動
	colSphere_.center = transform_.translation_;

	// 行列更新
	transform_.UpdateMatrix();
}

void BoundBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view, &objColor_);
}

void BoundBullet::DecreaseHP(int damage) {
	hp_ -= damage;
	if (hp_ <= 0) {
		isActive = false;
		collider_->isEnable = false;
	}
}
