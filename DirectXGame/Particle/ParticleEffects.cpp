#include "ParticleEffects.h"

#include <ImGuiManager.h>
#include <TextureManager.h>


using namespace ACJPN;
using namespace ACJPN::Math;

ParticleEffects::~ParticleEffects() { 
	
}

void ParticleEffects::Init() { 
	time_ = 60;
	scalar_PlayerBullet_ = 1.0f;
	scale_PlayerBullet_ = Vector3(0.5f, 0.5f, 0.5f);
	rotate_PlayerBullet_ = 90.0f;
	model_ = Model::Create();
}


void ParticleEffects::CreateParticle_PlayerBullet(const Vector3& position) { 

	Particle_PlayerBullet* newParticle = new Particle_PlayerBullet();
	newParticle->Init(time_,model_,position,scalar_PlayerBullet_,scale_PlayerBullet_,rotate_PlayerBullet_);

	particle_PlayerBullets_.push_back(newParticle);

}

void ParticleEffects::UpdateParticle() {
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
