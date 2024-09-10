#include "PlayScene.h"

#include "EndScene.h"

void PlayScene::Init() {
	// カメラ初期化
	camera_.Init();

	// プレイヤーを初期化
	player_.Init();

	// ステージ初期化
	stage_.Init();

	// ターゲットに設定
	camera_.SetTarget(player_.GetTransform());

	// 原点のオブジェクト
	origin_.reset(Model::CreateSphere());
	originTransform_.Initialize();
	// 東側のオブジェクト
	east_.reset(Model::Create());
	eastTransform_.Initialize();
	eastTransform_.translation_.x = 10.0f;
	eastTransform_.UpdateMatrix();
}

void PlayScene::Update() {
	// デバッグ情報
	DebugWindow();

	// スペースを押すとエンドシーンへ
	if (input_->TriggerKey(DIK_RETURN)) {
		nextScene_ = new EndScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
	// プレイヤー更新
	player_.Update();

	// ステージ更新
	stage_.Update();

	// フォローカメラ更新
	camera_.Update();
}

void PlayScene::DrawBackdrop() {
}


void PlayScene::Draw3D() {
	stage_.DrawModel(camera_.GetView());
	player_.DrawModel(camera_.GetView());
	origin_->Draw(originTransform_, *camera_.GetView());
	east_->Draw(eastTransform_, *camera_.GetView());
}

void PlayScene::DrawOverlay() {
}

void PlayScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("Play");
	ImGui::End();
#endif // _DEBUG
}
