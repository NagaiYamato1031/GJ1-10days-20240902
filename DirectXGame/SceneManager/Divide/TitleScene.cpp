#include "TitleScene.h"

#include "PlayScene.h"
#include "TextureManager.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {

	delete sprite_; 
	delete spriteMozi_;
}

void TitleScene::Init() {

	//タイトル背景画像初期化
	textureHandle_ = TextureManager::Load("BackGrund.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});

	//タイトル文字画像
}

void TitleScene::Update() {
	// デバッグ情報
	DebugWindow();

	// スペースを押すとプレイシーンへ
	if (input_->TriggerKey(DIK_RETURN)) {
		nextScene_ = new PlayScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
}

void TitleScene::DrawBackdrop() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	sprite_->Draw();

	Sprite::PostDraw();
}

void TitleScene::Draw3D() {
}

void TitleScene::DrawOverlay() {
	
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	spriteMozi_->Draw();

	Sprite::PostDraw();
}

void TitleScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("Title");
	ImGui::End();
#endif // _DEBUG
}
