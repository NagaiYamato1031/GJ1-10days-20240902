#include "CreateHpbar.h"

#include <ImGuiManager.h>
#include <TextureManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;

void CreateHpbar::Init(const Vector3& pos, Model *model ) {
	//破壊フラグ初期化
	isBreak = false;
	model_ = model;
	textureHandle_ = TextureManager::Load("HpBar/HpBar");
	

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void CreateHpbar::Update() {  }

void CreateHpbar::Draw(const ViewProjection* viewProjection) { 
	model_->Draw(worldTransform_, *viewProjection, textureHandle_);
}
