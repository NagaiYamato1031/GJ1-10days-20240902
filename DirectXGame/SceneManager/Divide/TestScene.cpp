#include "TestScene.h"

#include "TitleScene.h"

using namespace ACJPN;
using namespace ACJPN::Collider;
using namespace ACJPN::Math;

TestScene::TestScene() {}

TestScene::~TestScene() {}

void TestScene::Init() {

	// 当たり判定初期化
	collisionManager_ = CollisionManager::GetInstance();
	collisionManager_->Init();

	// 時間を設定
	time = kTransitionFrame_;

	// カメラ初期化
	camera_.Init();

	// プレイヤーを初期化
	player_.Init();

	// ステージ初期化
	stage_.Init();
	//スカイドーム初期化
	skydome_.Init();

	// ボス初期化
	boss_.Init();
	boss_.SetPlayer(&player_);

	score_.Init(Vector2(0, 0));

	// ターゲットに設定
	camera_.SetTarget(player_.GetTransform());

	//画像処理
	textureHandle_ = TextureManager::Load("white1x1.png");
	transitionSprite_.reset(Sprite::Create(textureHandle_, { 1280,0 }));
	transitionSprite_->SetSize({ 1280,720 });
}

void TestScene::Update() {
	// デバッグ情報
	DebugWindow();

	if (boss_.GetPhase() == 3) {
		skydome_.DirectionRed();
	}
	else if (boss_.IsDead()) {
		skydome_.DirectionTurnOff();
	}

	// 遷移中はほかのことをしない
	if (sceneFlag_.isTransition_) {
		TransitionUpdate();
		return;
	}
	if (input_->TriggerKey(DIK_L)) {
		score_.EnterTScore(2222);
	}
	// M を押すとタイトルへ
	if (input_->TriggerKey(DIK_M)) {
		nextScene_ = new TitleScene;
		sceneFlag_.isTransition_ = true;
	}

	// プレイヤー更新
	player_.Update();

	// ボス初期化
	boss_.Update();

	// ステージ更新
	stage_.Update();
	//スカイドーム更新
	skydome_.Update();

	// フォローカメラ更新
	camera_.Update();

	score_.Update();

	collisionManager_->Update();
	collisionManager_->CheckCollision();
}

void TestScene::DrawBackdrop() {
}

void TestScene::Draw3D() {
	skydome_.DrawModel(camera_.GetView());
	stage_.DrawModel(camera_.GetView());
	player_.DrawModel(camera_.GetView());
	boss_.DrawModel(camera_.GetView());
}

void TestScene::DrawOverlay() {
	if (IsTransition()) {
		transitionSprite_->Draw();
	}
	if (score_.IsActive()) {
		score_.Draw();
	}
}

void TestScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("Test");
	ImGui::End();
#endif // _DEBUG
}

void TestScene::TransitionUpdate() {
	// 時間で終了時間を決めることもできる
	time--;
	// フラグで管理していれば終了がわかる
	if (time <= 0) {
		sceneFlag_.allEnd_ = true;
		// これ以上処理しない
		return;
	}
	// 遷移中の処理
	transitionPosition_.x = 1500.0f * ((time - 10) / (float)kTransitionFrame_);
	transitionPosition_.x = transitionPosition_.x <= 0 ? 0 : transitionPosition_.x;

	// 値を入れる
	transitionSprite_->SetPosition(transitionPosition_);
}
