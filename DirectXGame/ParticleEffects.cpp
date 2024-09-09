#include "ParticleEffects.h"

#include <ImGuiManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;

void ParticleEffects::Init() {
	//モデル読み込み
	model_ = Model::CreateFromOBJ("cube");
	//初期化
	transform_.Initialize();
}

void ParticleEffects::Update() {
	ImGui::Begin("ParticleWindow");

	ImGui::DragFloat3("translate", &transform_.translation_.x, 0.1f);

	ImGui::End();

	transform_.UpdateMatrix();
}

void ParticleEffects::DrawModel(ViewProjection* view) { 	
	model_->Draw(transform_, *view); 
}
