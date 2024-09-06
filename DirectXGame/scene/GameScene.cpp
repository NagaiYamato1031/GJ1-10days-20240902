#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace ACJPN;
using namespace ACJPN::Scene;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// シーンマネージャーの生成と初期化
	sceneManager_ = std::make_unique<SceneManager>();
	sceneManager_->Init();
}

void GameScene::Update() {
	sceneManager_->Update();
}

void GameScene::Draw() {
	sceneManager_->Draw();
}
