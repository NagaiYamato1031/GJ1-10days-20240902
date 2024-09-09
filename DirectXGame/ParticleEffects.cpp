#include "ParticleEffects.h"

#include <ImGuiManager.h>
#include <TextureManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;

ParticleEffects::~ParticleEffects() { 
	delete model_; 
}

void ParticleEffects::Init() {
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("white1x1.png");

	//3Dモデルの生成
	model_ = Model::Create();
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void ParticleEffects::Update() {
	ImGui::Begin("ParticleWindow");

	ImGui::DragFloat3("translate", &worldTransform_.translation_.x, 0.1f);

	ImGui::End();

	worldTransform_.UpdateMatrix();
}

void ParticleEffects::DrawModel(ViewProjection* view) { 	
	model_->Draw(worldTransform_, *view); 
}

void ParticleEffects::CreateParticle() {}

void ParticleEffects::UpdateParticle() {}
