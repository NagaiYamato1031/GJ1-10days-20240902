#include "ParticleEffects.h"

#include <ImGuiManager.h>
#include <TextureManager.h>


using namespace ACJPN;
using namespace ACJPN::Math;

ParticleEffects::~ParticleEffects() { 
	particle_PlayerBullets_.clear();
	
}

void ParticleEffects::Init() { 
	model_ = Model::Create();
}


void ParticleEffects::CreateParticle_PlayerBullet(const Vector3& position) { 

	Particle_PlayerBullet* newParticle = new Particle_PlayerBullet();
	newParticle->Init(model_,position);

	particle_PlayerBullets_.push_back(newParticle);

}

void ParticleEffects::UpdateParticle() {
	for (Particle_PlayerBullet* particle_PlayerBullet : particle_PlayerBullets_) {
		particle_PlayerBullet->Update();
	}
}

void ParticleEffects::DrawParticle(const ViewProjection* viewProjection) { 
	for (Particle_PlayerBullet* particle_PlayerBullet : particle_PlayerBullets_) {
		particle_PlayerBullet->Draw(viewProjection);
	}
}

void ParticleEffects::TestDelete() {
	particle_PlayerBullets_.clear();
}
