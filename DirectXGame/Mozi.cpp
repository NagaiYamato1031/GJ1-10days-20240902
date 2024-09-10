#include "Mozi.h"
#include "TextureManager.h"

Mozi::Mozi() {}

Mozi::~Mozi() {

	delete spriteS_;
	delete spriteJ_;
	delete spriteH_;
}

void Mozi::Init() {

	//フラグ初期化
	SousaMozi = false;
	JumMozi = false;
	HipMozi = false;

	//座標系初期化
	SMoziPos = {100, 100, 0};
	JMoziPos = {100, 200, 0};
	HMoziPos = {100, 300, 0};

	spriteS_ = Sprite::Create(textureHandleS_, {SMoziPos.x, SMoziPos.y});
	spriteJ_ = Sprite::Create(textureHandleJ_, {JMoziPos.x, JMoziPos.y});
	spriteH_ = Sprite::Create(textureHandleH_, {HMoziPos.x, HMoziPos.y});

}

void Mozi::Update() {

	//SousaMozi
	if (SousaMozi == true) {

		MoziColorS.w += 0.005f;
		spriteS_->SetColor(MoziColorS);
	}
	if (MoziColorS.w >= 1.0f) {

		SousaMozi = false;
		MoziColorS.w = 0.0f;
	}

	//JumpMozi
	if (JumMozi == true) {

		MoziColorJ.w += 0.005f;
		spriteS_->SetColor(MoziColorJ);
	}
	if (MoziColorJ.w >= 1.0f) {

		JumMozi = false;
		MoziColorJ.w = 0.0f;
	}

	//HipMozi
	if (HipMozi == true) {

		MoziColorH.w += 0.005f;
		spriteS_->SetColor(MoziColorH);
	}
	if (MoziColorH.w >= 1.0f) {

		HipMozi = false;
		MoziColorH.w = 0.0f;
	}


}

void Mozi::DrawM() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	
	Sprite::PreDraw(commandList);

	if (SousaMozi == true) 
	{
		spriteS_->Draw();
	}

	if (JumMozi == true) 
	{
		spriteJ_->Draw();
	}

	if (HipMozi == true) 
	{
		spriteH_->Draw();
	}

	Sprite::PostDraw();

}

