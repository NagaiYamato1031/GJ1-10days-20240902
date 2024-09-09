#include "Stage.h"

void Stage::Init() {
	// モデル読み込み
	model_.reset(Model::CreateSphere());
	// 行列初期化
	transform_.Initialize();

	transform_.translation_.z = 5.0f;
	transform_.scale_ = { 50.0f,50.0f,1.0f };
}

void Stage::Update() {




	// 行列更新
	transform_.UpdateMatrix();
}

void Stage::DrawModel(ViewProjection* view) {
	model_->Draw(transform_, *view);
}
