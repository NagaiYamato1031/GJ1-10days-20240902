#include "TestScene.h"

#include "TitleScene.h"

using namespace ACJPN;
using namespace ACJPN::Collider;
using namespace ACJPN::Math;

TestScene::TestScene() {}

TestScene::~TestScene() {

	delete fadeSpriteGC_;
	delete fadeSpriteGO_;
}

void TestScene::Init() {

	collisionManager_ = CollisionManager::GetInstance();
	collisionManager_->Init();

	time = 60;

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
	textureHandleFadeGC_ = TextureManager::Load("Fade_GC.png");
	fadeSpriteGC_ = Sprite::Create(textureHandleFadeGC_, {0, 0});

	textureHandleFadeGO_ = TextureManager::Load("Fade_GO.png");
	fadeSpriteGO_ = Sprite::Create(textureHandleFadeGO_, {0, 0});
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
	if (FadeGC == true) {
		
		fadeSpriteGC_->Draw();
	}

	if (FadeGO == true) {

		fadeSpriteGO_->Draw();
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
	
	//ゲームクリア
	if (boss_.IsDead() == true) {

		FadeGC = true;
		if (FadeGC == true) {
			FadeColorGC_.w += 0.005f;
			fadeSpriteGC_->SetColor(FadeColorGC_);

			if (FadeColorGC_.w >= 1.0f) {
				FadeGC = false;
			}
		}
	}
	//ゲームオーバー
	if (player_.IsDead() == true) {

		FadeGO = true;
		if (FadeGO == true) {
			FadeColorGO_.w += 0.005f;
			fadeSpriteGO_->SetColor(FadeColorGO_);

			if (FadeColorGO_.w >= 1.0f) {
				FadeGO = false;
			}
		}
	}
}
