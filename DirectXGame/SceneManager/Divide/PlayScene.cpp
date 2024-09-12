#include "PlayScene.h"

#include "EndScene.h"

using namespace ACJPN;
using namespace ACJPN::Collider;
using namespace ACJPN::Math;

void PlayScene::Init() {

	// 当たり判定の初期化
	collisionManager_ = CollisionManager::GetInstance();
	collisionManager_->Init();

	// カメラ初期化
	camera_.Init();

	// プレイヤーを初期化
	player_.Init();

	// ステージ初期化
	stage_.Init();

	// ボス
	boss_.Init();

	boss_.SetPlayer(&player_);

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

	// フラグを検知してシーンを切り替える
	// プレイヤー死亡時
	if (player_.IsDead()) {
		nextScene_ = new EndScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
	// ボス死亡時
	else if (boss_.IsDead()) {
		nextScene_ = new EndScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}
	// プレイヤー更新
	player_.Update();

	// ボス更新
	boss_.Update();

	// ステージ更新
	stage_.Update();

	// フォローカメラ更新
	camera_.Update();

	// 当たり判定
	collisionManager_->Update();
	collisionManager_->CheckCollision();
}

void PlayScene::DrawBackdrop() {
}


void PlayScene::Draw3D() {
	origin_->Draw(originTransform_, *camera_.GetView());
	east_->Draw(eastTransform_, *camera_.GetView());
	boss_.DrawModel(camera_.GetView());
	stage_.DrawModel(camera_.GetView());
	player_.DrawModel(camera_.GetView());
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
