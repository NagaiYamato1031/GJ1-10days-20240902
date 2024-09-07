#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {

	//delete sprite_; 
}

void TitleScene::Init() {

	//MoziPos = {100, 100, 0};

	//sprite_ = Sprite::Create(textureHandle_, {MoziPos.x, MoziPos.y});
}

void TitleScene::Update() {

	ImGui::Begin("Scene");
	ImGui::Text("Title");
	ImGui::End();

}

void TitleScene::DrawBackdrop() {
}

void TitleScene::Draw3D() {
}

void TitleScene::DrawOverlay() {

	//ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	//Sprite::PreDraw(commandList);

	//sprite_->Draw();

	//Sprite::PostDraw();
}
