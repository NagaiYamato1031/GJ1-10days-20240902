#include "DisplayHp.h"


#include <ImGuiManager.h>
#include <TextureManager.h>
#include <Time.h>
#include <random>

using namespace ACJPN;
using namespace ACJPN::Math;


void DisplayHp::Init() { 

	distance_ = 12.0f;

	model_ = Model::Create();
}

void DisplayHp::Create(const Vector3 &position,const int  &hp) { 
	for (int i = 0; i < hp; i++) {
		CreateHpbar* newHp = new CreateHpbar();
		float deg = (float)(360 / hp * i);
		newHp->Init(position, model_,deg,distance_);
		hpBars_.push_back(newHp);
	}
}

void DisplayHp::Update() {


	hpBars_.remove_if([](CreateHpbar* HpBar) { 
		if (!HpBar->isActive) {
			delete HpBar;
			return true;
		}
		return false;
	});
	for (CreateHpbar*createHpBar:hpBars_) {
		createHpBar->Update();
		//}
	}
}

void DisplayHp::DrawModel(const ViewProjection*viewProjection) {
	for (CreateHpbar* createHpBar : hpBars_) {
		    createHpBar->Draw(viewProjection);
	}
}

void DisplayHp::DamageBreak() { 
	int life = 0;
	for (CreateHpbar* createhpBar:hpBars_) {
		    life++;
		    createhpBar->NeedReturn();
	}
	if (life > 0) {
		    hpBars_.pop_back();
	}
	
}


