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

	//Hpばー初期化
	displayHp_.Init();

	// ターゲットに設定
	camera_.SetTarget(player_.GetTransform());

	//画像処理
	textureHandle_ = TextureManager::Load("white1x1.png");
	transitionSprite_.reset(Sprite::Create(textureHandle_, { 1280,0 }));
	transitionSprite_->SetSize({ 1280,720 });

	// 移動画像初期化
	moveHandle_ = TextureManager::Load("ui/move.png");
	moveSpritePosition_ = { 50.0f,43.0f };
	moveSprite_.reset(Sprite::Create(moveHandle_, moveSpritePosition_));
	moveSprite_->SetSize({ 215.0f,50.0f });
	// スペース画像初期化
	spaceHandle_ = TextureManager::Load("ui/SPACE.png");
	spaceSpritePosition_ = { 70.0f,110.0f };
	spaceSprite_.reset(Sprite::Create(spaceHandle_, spaceSpritePosition_));
	spaceSprite_->SetSize({ 170.0f,65.0f });
	// ジャンプ画像初期化
	jumpHandle_ = TextureManager::Load("ui/jump.png");
	jumpdropSpritePosition_ = { 150.0f,200.0f };
	jumpSprite_.reset(Sprite::Create(jumpHandle_, jumpdropSpritePosition_));
	jumpSprite_->SetAnchorPoint({ 0.5f,0.5f });
	jumpSprite_->SetSize({ 100.0f,50.0f });
	// ドロップ画像初期化
	dropHandle_ = TextureManager::Load("ui/drop.png");
	dropSprite_.reset(Sprite::Create(dropHandle_, jumpdropSpritePosition_));
	dropSprite_->SetAnchorPoint({ 0.5f,0.5f });
	dropSprite_->SetSize({ 100.0f,50.0f });
}

void TestScene::Update() {
	// デバッグ情報
	DebugWindow();

	// 時間で切り替え
	timeToggle_++;
	if (100 <= timeToggle_) {
		isJump_ = !isJump_;
		timeToggle_ = 0;
	}

	// Skydome の演出
	if (boss_.GetPhase() == 3) {
		skydome_.DirectionRed();
	}
	else if (boss_.IsDead()) {
		skydome_.DirectionTurnOff();
	}


	// 遷移中はほかのことをしない
	// 演出が出来なくなるので処理するようにする
	if (sceneFlag_.isTransition_) {
		TransitionUpdate();
		//return;
	}

	// フラグを検知してシーンを切り替える
	// プレイヤー死亡時
	if (!IsTransition() && player_.IsDead()) {
		nextScene_ = new TestScene;
		sceneFlag_.isTransition_ = true;
		//sceneFlag_.allEnd_ = true;
	}
	// ボス死亡時
	else if (!IsTransition() && boss_.IsDead()) {
		nextScene_ = new TestScene;
		sceneFlag_.isTransition_ = true;
		//sceneFlag_.allEnd_ = true;
	}

	// M を押すとタイトルへ
	if (input_->TriggerKey(DIK_M)) {
		nextScene_ = new TitleScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
	}

	//テストで体力表示
	if (input_->TriggerKey(DIK_W)) {
		displayHp_.Create(Vector3(0, 0, 0), 3);
	}
	if (input_->TriggerKey(DIK_S)) {
		displayHp_.DamageBreak();
	}
	displayHp_.Update();

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

	displayHp_.DrawModel(camera_.GetView());
}

void TestScene::DrawOverlay() {
	moveSprite_->Draw();
	spaceSprite_->Draw();
	if (isJump_) {
		jumpSprite_->Draw();
	}
	else {
		dropSprite_->Draw();
	}

	if (IsTransition()) {
		transitionSprite_->Draw();
	}

}

void TestScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("Test");
	if (ImGui::TreeNode("Move")) {
		Vector2 size = moveSprite_->GetSize();
		if (ImGui::DragFloat3("pos", &moveSpritePosition_.x, 0.01f)) {
			moveSprite_->SetPosition(moveSpritePosition_);
		}
		if (ImGui::DragFloat3("size", &size.x, 0.01f)) {
			moveSprite_->SetSize(size);
		}
		ImGui::TreePop();
		ImGui::Separator();
	}
	if (ImGui::TreeNode("Space")) {
		Vector2 size = spaceSprite_->GetSize();
		if (ImGui::DragFloat3("pos", &spaceSpritePosition_.x, 0.01f)) {
			spaceSprite_->SetPosition(spaceSpritePosition_);
		}
		if (ImGui::DragFloat3("size", &size.x, 0.01f)) {
			spaceSprite_->SetSize(size);
		}
		ImGui::TreePop();
		ImGui::Separator();
	}
	if (ImGui::TreeNode("jump")) {
		Vector2 size = jumpSprite_->GetSize();
		if (ImGui::DragFloat3("pos", &jumpdropSpritePosition_.x, 0.01f)) {
			jumpSprite_->SetPosition(jumpdropSpritePosition_);
		}
		if (ImGui::DragFloat3("size", &size.x, 0.01f)) {
			jumpSprite_->SetSize(size);
		}
		ImGui::TreePop();
		ImGui::Separator();
	}
	if (ImGui::TreeNode("drop")) {
		Vector2 size = dropSprite_->GetSize();
		if (ImGui::DragFloat3("pos", &jumpdropSpritePosition_.x, 0.01f)) {
			dropSprite_->SetPosition(jumpdropSpritePosition_);
		}
		if (ImGui::DragFloat3("size", &size.x, 0.01f)) {
			dropSprite_->SetSize(size);
		}
		ImGui::TreePop();
		ImGui::Separator();
	}
	ImGui::End();
#endif // _DEBUG
}

void TestScene::TransitionUpdate() {

	// プレイヤーかボスの演出後に更新するようにする
	if (player_.IsActive() && boss_.IsActive()) {
		return;
	}

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
