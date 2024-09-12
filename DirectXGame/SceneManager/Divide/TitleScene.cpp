#include "TitleScene.h"

#include "PlayScene.h"

void TitleScene::Init() {

	//MoziPos = {100, 100, 0};

	//sprite_ = Sprite::Create(textureHandle_, {MoziPos.x, MoziPos.y});
}

void TitleScene::Update() {
	// �f�o�b�O���
	DebugWindow();

	// �X�y�[�X������ƃv���C�V�[����
	if (input_->TriggerKey(DIK_RETURN)) {
		nextScene_ = new PlayScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
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

void TitleScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("Title");
	ImGui::End();
#endif // _DEBUG
}
