#include "Particle_Background.h"

#include <ImGuiManager.h>
#include <TextureManager.h>
#include <time.h>
#include <random>

using namespace ACJPN;
using namespace ACJPN::Math;

void Particle_Background::Init(Model* model, const Vector3& position, const float& scalar, const float &breakPos,const Vector3&scale) {
	// 加速度代入
	velocity_.y = scalar;

	// 3Dモデルの生成
	model_ = model;

	// 破壊フラグ初期化
	isBreak_ = false;
	
	Vector3 pos = Vector3(((float)((rand()) % 100)-50), position.y, position.z);

	//壊れる座標受け取り
	breakPos_ = breakPos;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.scale_ = scale;
	worldTransform_.translation_ = pos;
}

void Particle_Background::Update() {
	if (worldTransform_.translation_.y > breakPos_) {
		isBreak_ = true;
	}
	// 加速度加算
	worldTransform_.translation_ += velocity_;
	worldTransform_.rotation_.x += 0.01f;
	worldTransform_.rotation_.y += 0.2f;
	worldTransform_.rotation_.z += 0.01f;

	// ワールドマトリックス更新
	worldTransform_.UpdateMatrix();
}

void Particle_Background::DrawModel(const ViewProjection* viewProjection) { model_->Draw(worldTransform_, *viewProjection); }

bool Particle_Background::IsBreak() {
	if (isBreak_) {
		return true;
	} else {
		return false;
	}
}