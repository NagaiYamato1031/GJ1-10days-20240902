#include "DisplayHp.h"


#include <ImGuiManager.h>
#include <TextureManager.h>
#include <Time.h>
#include <random>

using namespace ACJPN;
using namespace ACJPN::Math;


void DisplayHp::Init() { 

	distance_ = 4.0f;

	model_ = Model::Create();
}

void DisplayHp::Create(const Vector3 &position,const int  &hp) { 
	for (int i = 0; i < hp; i++) {
		CreateHpbar* newHp = new CreateHpbar();
		float deg = 360 / hp * i;
		newHp->Init(position, model_,deg,distance_);
		hpBars_.push_back(newHp);
	}
}

void DisplayHp::Update() {
	for (auto it = hpBars_.begin(); it != hpBars_.end();) {
		CreateHpbar* createHpBar = *it;
		createHpBar->Update();

		//if (particle_PlayerBullet->IsBreak()) {
		//	delete particle_PlayerBullet;
		//	it = particle_PlayerBullets_.erase(it);

		//} else {
		//	++it;
		//}
	}
}

void DisplayHp::DrawModel() {
	
}
