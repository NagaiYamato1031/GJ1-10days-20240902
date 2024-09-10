#include "Particle_PlayerBullet.h"

#include <ImGuiManager.h>
#include <TextureManager.h>
#include <Time.h>

using namespace ACJPN;
using namespace ACJPN::Math;

Particle_PlayerBullet::~Particle_PlayerBullet() { 

}

void Particle_PlayerBullet::Init( float time,Model *model,const Vector3& position) {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("white1x1.png");

	//生存時間
	time_ = time;

	//破壊フラグ
	isBreak_ = false;

	// 3Dモデルの生成
	model_ = model; // Model::Create();
	
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

}

void Particle_PlayerBullet::Update() {
	//なんか書いてあった奴をまねて書いた奴ら
	ImGui::Begin("ParticleWindow");

	ImGui::DragFloat3("translate", &worldTransform_.translation_.x, 0.1f);
	ImGui::Checkbox(" isBreak", &isBreak_);

	ImGui::End();

	//壊れるまでの時間計算
	time_--;
	if (time_ <= 0) {
		isBreak_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void Particle_PlayerBullet::Draw(const ViewProjection* viewProjection) {
	model_->Draw(worldTransform_, *viewProjection, textureHandle_); 
}

bool Particle_PlayerBullet::IsBreak() {
	if (isBreak_) {
		return true;
	}
	else {
		return false;
	}
}
