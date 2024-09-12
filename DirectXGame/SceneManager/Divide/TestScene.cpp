#include "TestScene.h"

#include "TitleScene.h"

using namespace ACJPN;
using namespace ACJPN::Collider;
using namespace ACJPN::Math;

TestScene::TestScene() {}

TestScene::~TestScene() {}

void TestScene::Init() {

	collisionManager_ = CollisionManager::GetInstance();
	collisionManager_->Init();

	time = kTransitionFrame_;

	// カメラ初期化
	camera_.Init();

	// プレイヤーを初期化
	player_.Init();

	// ステージ初期化
	stage_.Init();

	// ボス初期化
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
	//　球の当たり判定
	sphere_.center = { 0.0f,0.0f,0.0f };
	sphere_.radius = 1.0f;
	colSphere = std::make_shared<ShapeCollider<Sphere>>(&sphere_);

	//画像処理
	textureHandle_ = TextureManager::Load("white1x1.png");
	transitionSprite_.reset(Sprite::Create(textureHandle_, { 1280,0 }));
	transitionSprite_->SetSize({ 1280,720 });
}

void TestScene::Update() {
	// デバッグ情報
	DebugWindow();


	// 遷移中はほかのことをしない
	if (sceneFlag_.isTransition_) {
		TransitionUpdate();
		return;
	}
	// スペースを押すとタイトルへ
	if (input_->TriggerKey(DIK_RETURN)) {
		nextScene_ = new TitleScene;
		sceneFlag_.isTransition_ = true;
	}

	// プレイヤー更新
	player_.Update();

	// ボス初期化
	boss_.Update();

	// ステージ更新
	stage_.Update();

	// フォローカメラ更新
	camera_.Update();

	collisionManager_->Update();
	collisionManager_->CheckCollision();
}

void TestScene::DrawBackdrop() {
}

void TestScene::Draw3D() {
	origin_->Draw(originTransform_, *camera_.GetView());
	east_->Draw(eastTransform_, *camera_.GetView());

	stage_.DrawModel(camera_.GetView());
	player_.DrawModel(camera_.GetView());
	boss_.DrawModel(camera_.GetView());
}

void TestScene::DrawOverlay() {
	if (IsTransition()) {
		transitionSprite_->Draw();
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
