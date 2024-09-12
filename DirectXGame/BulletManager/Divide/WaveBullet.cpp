#include "WaveBullet.h"

#include<algorithm>

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void WaveBullet::Init() {
	model_.reset(Model::CreateSphere());
	transform_.Initialize();
}

void WaveBullet::Update() {
	// 強さを決めて弱まっていく感じでもいい
	//elapsedFrame++;
	//if (power_ * 30 + 30 <= elapsedFrame) {
	// パワーが無くなったら
	if (power_ <= 0.5f) {
		isActive = false;
		return;
	}
	// 角度をプラス
	theta_ += omega_;
	if (theta_ < -3.14f * 2) {
		theta_ += 3.14f * 2;
	}

	// パワーを弱めていく
	power_ *= 0.98f;

	// パワーによって波の大きさを変える
	// 制限を入れておく
	float size = std::clamp(power_, kMinSize, kMaxSize);
	transform_.scale_.x = size;
	transform_.scale_.y = size;
	// 当たり判定も変える
	colSphere_.radius = size;

	// 角度に応じて移動させる
	// ステージ幅に合わせたい
	transform_.translation_.x = std::cosf(theta_) * 50.0f;
	transform_.translation_.y = std::sinf(theta_) * 50.0f;

	// 当たり判定移動
	colSphere_.center = transform_.translation_;

	// 行列更新
	transform_.UpdateMatrix();
}

void WaveBullet::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}
