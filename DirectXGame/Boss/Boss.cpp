#include "Boss.h"

using namespace ACJPN;
using namespace ACJPN::Math;

void Boss::Init() {
	model_.reset(Model::Create());
	transform_.Initialize();
	transform_.scale_ = { 10.0f,10.0f,1.0f };
}

void Boss::Update() {

	transform_.UpdateMatrix();
}

void Boss::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}
