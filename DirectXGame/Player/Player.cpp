#include "Player.h"

#include <ImGuiManager.h>
#include <BulletManager/Divide/BulletList.h>

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void Player::Init() {
	// 入力取得
	input_ = Input::GetInstance();

	// モデル読み込み
	model_.reset(Model::CreateFromOBJ("cube"));
	// 初期化
	transform_.Initialize();
	// 北側から始まる
	transform_.translation_.y = kPaddingCenter_;
	// 北側に固定
	theta_ = 3.14f * 0.5f;

	// 値を初期化
	distance_ = 0.0f;
	latestDistance_ = kPaddingCenter_;

	// メンバ関数ポインタ配列を初期化
	InitFunctionArray();

	// 弾管理クラスの初期化
	bulletManager_.Init();
	//　球の当たり判定
	colSphere_.center = { 0.0f,0.0f,0.0f };
	colSphere_.radius = 1.0f;
	collider_ = std::make_shared<ShapeCollider<Sphere>>(&colSphere_);
	collider_->mask = MPlayer();
	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(collider_);
}

void Player::Update() {
	// デバッグ情報表示
	DebugWindow();

	// 行動の更新があった時
	if (reqBehavior_) {
		behavior_ = reqBehavior_.value();
		(this->*initFunc[behavior_])();
		reqBehavior_ = std::nullopt;
	}
	// 行動の更新
	(this->*updateFunc[behavior_])();

	// 弾管理クラス更新
	bulletManager_.Update();

	// 距離を計算
	latestDistance_ = kPaddingCenter_ + distance_;

	// 角度に応じて移動させる
	transform_.translation_.x = std::cosf(theta_) * latestDistance_;
	transform_.translation_.y = std::sinf(theta_) * latestDistance_;

	// 回転を合わせて中心に経っているようにする
	transform_.rotation_.z = theta_;

	// 当たり判定を移動
	colSphere_.center = transform_.translation_;

	// 行列更新
	transform_.UpdateMatrix();
}

void Player::DrawModel(ViewProjection* view) {
	bulletManager_.DrawModel(view);
	model_->Draw(transform_, *view);
}

void Player::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("PlayerWindow");

	ImGui::Text("Behavior : ");	ImGui::SameLine();
	switch (behavior_) {
	case Player::None:
		ImGui::Text("None");
		break;
	case Player::Jump:
		ImGui::Text("Jump");
		break;
	case Player::Fall:
		ImGui::Text("Fall");
		break;
	case Player::Drop:
		ImGui::Text("Drop");
		break;
	default:
		break;
	}

	ImGui::Text("Bullet : %d", bulletManager_.GetList().size());

	ImGui::DragFloat("theta", &theta_, 0.001f);
	if (theta_ < -3.14f * 2) {
		theta_ += 3.14f * 2;
	}
	else if (3.14f * 2 < theta_) {
		theta_ -= 3.14f * 2;
	}
	if (ImGui::TreeNode("Transform")) {
		ImGui::DragFloat3("rotation", &transform_.rotation_.x, 0.01f);
		ImGui::DragFloat3("translate", &transform_.translation_.x, 0.01f);

		ImGui::TreePop();
	}
	ImGui::Separator();

	if (ImGui::TreeNode("ConstVariables")) {
		ImGui::DragFloat("Padding", &kPaddingCenter_, 0.1f);
		ImGui::DragFloat("kSpeed", &kSpeed_, 0.0001f);

		ImGui::TreePop();
	}
	ImGui::Separator();

	ImGui::End();
#endif // _DEBUG
}

void Player::InitFunctionArray() {
	// 配列の最大値を決める
	initFunc.resize(Behavior::_Count);
	updateFunc.resize(Behavior::_Count);

	// 初期化関数
	initFunc[Behavior::None] = &Player::InitNone;
	initFunc[Behavior::Jump] = &Player::InitJump;
	initFunc[Behavior::Fall] = &Player::InitFall;
	initFunc[Behavior::Drop] = &Player::InitDrop;
	// 更新関数
	updateFunc[Behavior::None] = &Player::UpdateNone;
	updateFunc[Behavior::Jump] = &Player::UpdateJump;
	updateFunc[Behavior::Fall] = &Player::UpdateFall;
	updateFunc[Behavior::Drop] = &Player::UpdateDrop;
}

//** 初期化 **//

void Player::InitNone() {
}

void Player::InitJump() {
	elapsedFrame_ = 0;
	fineAir_ = 0.5f;
}

void Player::InitFall() {
	//fineAir_ = 0.0f;
}

void Player::InitDrop() {
	fineAir_ = -1.0f;
}

//** 更新 **//

void Player::UpdateNone() {
	// 入力で移動する
	if (input_->PushKey(DIK_A)) {
		theta_ += kSpeed_;
	}
	if (input_->PushKey(DIK_D)) {
		theta_ -= kSpeed_;
	}
	if (flag_.isGround_ && input_->TriggerKey(DIK_SPACE)) {
		flag_.isJumping_ = true;
		flag_.isGround_ = false;
		reqBehavior_ = Behavior::Jump;
	}
}

void Player::UpdateJump() {
	// 入力で移動する
	if (input_->PushKey(DIK_A)) {
		theta_ += kSpeed_;
	}
	if (input_->PushKey(DIK_D)) {
		theta_ -= kSpeed_;
	}
	// 追加入力で急降下
	if (input_->TriggerKey(DIK_SPACE)) {
		reqBehavior_ = Behavior::Drop;
	}
	fineAir_ -= 0.01f;
	distance_ += fineAir_;
	elapsedFrame_++;
	if (50 <= elapsedFrame_) {
		flag_.isJumping_ = false;
		reqBehavior_ = Behavior::Fall;
	}
}

void Player::UpdateFall() {
	// 入力で移動する
	if (input_->PushKey(DIK_A)) {
		theta_ += kSpeed_;
	}
	if (input_->PushKey(DIK_D)) {
		theta_ -= kSpeed_;
	}
	// 追加入力で急降下
	if (input_->TriggerKey(DIK_SPACE)) {
		reqBehavior_ = Behavior::Drop;
	}
	fineAir_ -= 0.01f;
	distance_ += fineAir_;
	if (distance_ <= 0.0f) {
		distance_ = 0.0f;
		flag_.isGround_ = true;
		reqBehavior_ = Behavior::None;
	}
}

void Player::UpdateDrop() {
	fineAir_ -= 0.01f;
	distance_ += fineAir_;
	if (distance_ <= 0.0f) {
		CreateBullet();
		distance_ = 0.0f;
		flag_.isGround_ = true;
		reqBehavior_ = Behavior::None;
	}
}

void Player::CreateBullet() {
	// 弾を生成する
	SimpleBullet* data = new SimpleBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	// 速度を向いている方向に向ける
	data->velocity_.x = std::cosf(theta_) * -1.5f;
	data->velocity_.y = std::sinf(theta_) * -1.5f;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 1.0f;
	data->collider_ = std::make_shared<ShapeCollider<Sphere>>(&data->colSphere_);
	// マスク
	data->collider_->mask = MPlayerBullet();

	// ヒット時処理
	data->collider_->enterLambda = [=](int mask) {
		mask;
		data->isActive = false;
		data->collider_->isActive = false;
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(data->collider_);
	// 登録
	bulletManager_.Regist(data);
}
