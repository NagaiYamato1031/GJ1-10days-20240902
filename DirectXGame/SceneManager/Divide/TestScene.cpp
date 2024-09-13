#include "TestScene.h"

#include "TitleScene.h"


using namespace ACJPN;
using namespace ACJPN::Collider;
using namespace ACJPN::Math;

TestScene::TestScene() {}

TestScene::~TestScene() {}

void TestScene::Init() {

	soundHandle_ = audio_->LoadWave("mokugyo.wav");

}

void TestScene::Update() {
	// デバッグ情報
	DebugWindow();
}

void TestScene::DrawBackdrop() {
}

void TestScene::Draw3D() {
}

void TestScene::DrawOverlay() {
}

void TestScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("Test");

	if (ImGui::Button("Play")) {
		audio_->PlayWave(soundHandle_);
	}
	ImGui::End();
#endif // _DEBUG
}