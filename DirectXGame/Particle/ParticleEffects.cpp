#include "ParticleEffects.h"

#include <ImGuiManager.h>
#include <TextureManager.h>


using namespace ACJPN;
using namespace ACJPN::Math;

ParticleEffects::~ParticleEffects() { 
	
}

void ParticleEffects::Init() { 
	lifeTime_PlayerBullet_ = 10;//生存時間
	scalar_PlayerBullet_ = 1.0f;//速さ
	scale_PlayerBullet_ = Vector3(0.5f, 0.5f, 0.5f);//サイズ
	rotate_PlayerBullet_ = 0.0f;//回転角
	interval_PlayerBullet_ = 3.0f;//生成間隔
	intervalBuff_PlayerBullet_ = 0;

	model_ = Model::Create();
}


void ParticleEffects::CreateParticle_PlayerBullet(const Vector3& position) { 

	if (intervalBuff_PlayerBullet_ <= 0) {
		intervalBuff_PlayerBullet_ = interval_PlayerBullet_;

		Particle_PlayerBullet* newParticle = new Particle_PlayerBullet();
		newParticle->Init(lifeTime_PlayerBullet_, model_, position, scalar_PlayerBullet_, scale_PlayerBullet_, rotate_PlayerBullet_);

		particle_PlayerBullets_.push_back(newParticle);
	}
	intervalBuff_PlayerBullet_--;
}

void ParticleEffects::UpdateParticle() {

	ImGui::Begin("ParticleWindow");
	ImGui::DragFloat("Scalar", &scalar_PlayerBullet_, 0.1f);
	ImGui::DragFloat("Rotate", &rotate_PlayerBullet_,0.1f);
	ImGui::DragFloat3("Scale", &scale_PlayerBullet_.x, 0.1f);
	ImGui::DragFloat("Intervall", &interval_PlayerBullet_, 0.1f);
	ImGui::DragFloat("LifeTime", &lifeTime_PlayerBullet_, 0.1f);
	ImGui::End();

	for (auto it = particle_PlayerBullets_.begin(); it != particle_PlayerBullets_.end();) {
		Particle_PlayerBullet* particle_PlayerBullet = *it;
		particle_PlayerBullet->Update();

		if (particle_PlayerBullet->IsBreak()) {
			delete particle_PlayerBullet;
			it = particle_PlayerBullets_.erase(it);

		} else {
			++it;
		}
	}
}

void ParticleEffects::DrawParticle(const ViewProjection* viewProjection) { 
	for (Particle_PlayerBullet* particle_PlayerBullet : particle_PlayerBullets_) {
		particle_PlayerBullet->Draw(viewProjection);
	}
}

void ParticleEffects::TestDelete() {
	for (Particle_PlayerBullet* particle_PlayerBullet : particle_PlayerBullets_) {
		delete particle_PlayerBullet;
	}
	particle_PlayerBullets_.clear();
}
