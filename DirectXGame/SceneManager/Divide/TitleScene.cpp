#include "TitleScene.h"

#include "PlayScene.h"

using namespace ACJPN;
using namespace ACJPN::Collider;
using namespace ACJPN::Math;

TitleScene::TitleScene() {
}

TitleScene::~TitleScene() {
}

void TitleScene::Init() {
	// 当たり判定マネージャー初期化
	collisionManager_ = CollisionManager::GetInstance();
	collisionManager_->Init();

	// 画像の初期化
	textureTitle_ = TextureManager::GetInstance()->Load("title/Title.png");
	titleSprite_.reset(Sprite::Create(textureTitle_, kSpritePosition_));
	titleSprite_->SetAnchorPoint({ 0.5f,0.5f });
	Vector2 size = titleSprite_->GetSize();
	titleSprite_->SetSize(size * 0.5f);

	// オブジェクトの初期化
	skydome_.Init();
	stage_.Init();

	// プレイヤーの初期化
	player_.Init();
	// カメラの初期化
	camera_.Init();
	camera_.SetTarget(player_.GetTransform());

	// ボスのモデル
	bossModel_.reset(Model::CreateFromOBJ("BossEnemy"));
	bossTransform_.Initialize();
	bossTransform_.scale_ = { 10.0f,10.0f,1.0f };
	bossTransform_.UpdateMatrix();
	bossObjColor_.Initialize();
	bossObjColor_.SetColor({ 0.0f, 0.75f, 0.0f, 1.0f });
	bossObjColor_.TransferMatrix();

	// 当たり判定を初期化
	colSphere_.center = { 0.0f,0.0f,0.0f };
	colSphere_.radius = 20.0f;
	collider_ = std::make_shared<ShapeCollider<Sphere>>(&colSphere_);
	// 適当なマスク
	collider_->mask = MBoss();
	collider_->enterLambda = [=](int mask) {
		mask;
		// シーン遷移
		nextScene_ = new PlayScene;
		sceneFlag_.isTransition_ = true;
		sceneFlag_.allEnd_ = true;
		};
	// 登録
	collisionManager_->RegistCollider(collider_);
}

void TitleScene::Update() {
	// デバッグ表示
	DebugWindow();


	// 時間で切り替え
	timeToggle_++;
	if (100 <= timeToggle_) {
		isJump_ = !isJump_;
		timeToggle_ = 0;
	}

	// プレイヤー更新
	player_.Update();

	// ステージ更新
	stage_.Update();
	//スカイドーム更新
	skydome_.Update();

	// カメラ更新
	camera_.Update();

	// 原点をカメラ座標に直す
	Vector3 origin = { 0.0f,0.0f,0.0f };
	// 反転して取得
	Matrix4x4 matCamera = Inverse(camera_.GetView()->matView);
	origin = Transform(origin, matCamera);
	titleSprite_->SetPosition({ origin.x + kSpritePosition_.x,origin.y + kSpritePosition_.y });

	// 当たり判定更新
	collisionManager_->Update();
	collisionManager_->CheckCollision();

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

void TitleScene::DrawBackdrop() {
}

void TitleScene::Draw3D() {
	skydome_.DrawModel(camera_.GetView());
	stage_.DrawModel(camera_.GetView());
	player_.DrawModel(camera_.GetView());
	bossModel_->Draw(bossTransform_, *camera_.GetView(), &bossObjColor_);
}

void TitleScene::DrawOverlay() {
	//moveSprite_->Draw();
	spaceSprite_->Draw();
	if (isJump_) {
		jumpSprite_->Draw();
	}
	else {
		dropSprite_->Draw();
	}
	titleSprite_->Draw();
}

void TitleScene::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Scene");

	if (ImGui::TreeNode("Title")) {
		Vector2 position = titleSprite_->GetPosition();
		if (ImGui::DragFloat2("Position", &position.x)) {
			titleSprite_->SetPosition(position);
		}
		Vector2 size = titleSprite_->GetSize();
		if (ImGui::DragFloat2("Size", &size.x, 1.0f)) {
			titleSprite_->SetSize(size);
		}

		ImGui::TreePop();
	}
	ImGui::End();
#endif // _DEBUG
}
