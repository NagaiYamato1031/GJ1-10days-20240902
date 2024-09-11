#include "Boss.h"
#include <BulletManager/Divide/BulletList.h>
#include <Player/Player.h>
#include <ImGuiManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;
using namespace ACJPN::Collider;

void Boss::Init() {
	model_.reset(Model::CreateSphere());
	transform_.Initialize();
	transform_.scale_ = { 10.0f,10.0f,1.0f };

	// 弾管理クラス初期化
	bulletManager_.Init();

	//ＨＰ・フラグ・フェーズ初期化
	HP_ = 40;
	isDead_ = false;
	phase_ = p1;
	// 当たり判定を初期化
	InitCollision();
}

void Boss::Update() {

	// デバッグ表示
	DebugWindow();

	switch (phase_) {
	case Boss::p1:
		Phase_01();
		break;
	case Boss::p2:
		Phase_02();
		break;
	case Boss::p3:
		Phase_03();
		break;
	case Boss::p4:
		Phase_04();
		break;
	}

	// 弾管理クラス更新
	bulletManager_.Update();

	// 当たり判定も更新
	colSphere_.center = transform_.translation_;

	// 行列の更新
	transform_.UpdateMatrix();
}

void Boss::DrawModel(ViewProjection* view) {

	//弾管理クラス描画
	bulletManager_.DrawModel(view);

	model_->Draw(transform_, *view);
}

void Boss::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("BossWindow");

	ImGui::Text("HP : %d", HP_);
	ImGui::Text("IsDead : %s", isDead_ ? "TRUE" : "FALSE");

	ImGui::End();
#endif // _DEBUG
}

void Boss::InitCollision() {
	//　球の当たり判定
	colSphere_.center = { 0.0f,0.0f,0.0f };
	colSphere_.radius = 5.0f;
	collider_ = std::make_shared<ShapeCollider<Sphere>>(&colSphere_);
	// マスク設定
	collider_->mask = MBoss();

	// 当たった時の処理
	collider_->enterLambda = [=](int mask) {
		// プレイヤーの弾の時
		if (mask == MPlayerBullet()) {
			DecreasHP(1);
		}
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(collider_);
}

void Boss::CreateBulletSimple() {
	// 弾を生成する
	SimpleBullet* data = new SimpleBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	// 座標
	Vector3 pos = player_->GetTransform()->translation_;
	Vector3 norm = Normalize(pos);
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = norm.x * 1.0f;
	data->velocity_.y = norm.y * 1.0f;
	data->aliveFrame_ = 50;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 1.0f;
	data->collider_ = std::make_shared<ShapeCollider<Sphere>>(&data->colSphere_);
	// マスク
	data->collider_->mask = MBossBullet();

	// ヒット時処理
	data->collider_->enterLambda = [=](int mask) {
		mask;
		// プレイヤーに当たった時
		if (mask == MPlayer()) {
			data->isActive = false;
			data->collider_->isActive = false;
		}
		};
	// 応急措置として呼び出す
	data->collider_->exitLambda = [=](int mask) {
		// ステージに当たったら
		if (mask == MStage()) {
			data->isActive = false;
			data->collider_->isActive = false;
			Vector3 norm = Normalize(data->transform_.translation_);
			// 波を発生させる
			CreateBulletWave(std::atan2(norm.y,norm.x), 3.0f);
		}
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(data->collider_);
	// 登録
	bulletManager_.Regist(data);
}

void Boss::CreateBulletWave(float theta, float power) {
	// 座標
	Vector3 pos = { std::cosf(theta),std::sinf(theta),0.0f };
	// ステージに合わせる
	pos *= 50.0f;
	// 一つ目
	// 弾を生成する
	WaveBullet* data = new WaveBullet;
	data->Init();
	data->transform_.translation_ = pos;
	// 進む方向を設定
	data->theta_ = theta;
	data->power_ = power;
	data->omega_ = power * 0.001f;
	
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 1.0f;
	data->collider_ = std::make_shared<ShapeCollider<Sphere>>(&data->colSphere_);
	// マスク
	data->collider_->mask = MWave();

	// ヒット時処理
	data->collider_->enterLambda = [=](int mask) {
		mask;
		// プレイヤーに当たった時
		if (mask == MPlayer()) {
			data->isActive = false;
			data->collider_->isActive = false;
		}
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(data->collider_);
	// 登録
	bulletManager_.Regist(data);

	// 二つ目
	// 弾を生成する
	data = new WaveBullet;
	data->Init();
	data->transform_.translation_ = pos;
	// 進む方向を逆方向へ
	data->theta_ = theta;
	data->power_ = power;
	data->omega_ = power * 0.001f * -1;

	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 1.0f;
	data->collider_ = std::make_shared<ShapeCollider<Sphere>>(&data->colSphere_);
	// マスク
	data->collider_->mask = MWave();

	// ヒット時処理
	data->collider_->enterLambda = [=](int mask) {
		mask;
		// プレイヤーに当たった時
		if (mask == MPlayer()) {
			data->isActive = false;
			data->collider_->isActive = false;
		}
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(data->collider_);
	// 登録
	bulletManager_.Regist(data);
}

void Boss::DecreasHP(int damage) {
	HP_ -= damage;
	if (HP_ <= 0) {
		isDead_ = true;
	}
}

// エネミー攻撃処理
void Boss::EnemyAttack_1() {
	// プレイヤーを狙って飛んでくる弾
	CreateBulletSimple();
}

void Boss::EnemyAttack_2() {

	// プレイヤーの周りを狙って飛んでくる弾
	SimpleBullet* data = new SimpleBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	// 弾をプレイヤーの方向に向ける
	data->velocity_.x;
	data->velocity_.y;
	// 登録
	bulletManager_.Regist(data);
}

void Boss::EnemyAttack_3() {

	// 円に向かって飛び、波を発生させる弾
	SimpleBullet* data = new SimpleBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	// 弾をプレイヤーの方向に向ける
	data->velocity_.x;
	data->velocity_.y;
	// 登録
	bulletManager_.Regist(data);
}


//エネミーフェーズ処理
void Boss::Phase_01() {

	AttackFrame01--;

	//攻撃処理呼び出し
	if (AttackFrame01 <= 0) {

		EnemyAttack_1();

		//フレーム初期化
		AttackFrame01 = 180;
	}

	// フェーズ２へ移行
	if (HP_ >= 29 && HP_ <= 30) {
		phase_ = p2;
	}
}

void Boss::Phase_02() {

	AttackFrame01--;
	AttackFrame02--;

	// 攻撃処理呼び出し
	if (AttackFrame01 <= 0) {

		EnemyAttack_1();
		AttackFrame01 = 180;
	}
	// 攻撃処理呼び出し
	else if (AttackFrame02 <= 0) {

		EnemyAttack_2();
		AttackFrame02 = 180;
	}

	//フェーズ３へ移行
	if (HP_ >= 19 && HP_ <= 28) {
		phase_ = p3;
	}
}

void Boss::Phase_03() {

	// 攻撃処理呼び出し
	if (false) {

		EnemyAttack_1();
	}
	// 攻撃処理呼び出し
	else if (false) {

		EnemyAttack_3();
	}

	// フェーズ４へ移行
	if (HP_ >= 9 && HP_ <= 18) {
		phase_ = p4;
	}
}

void Boss::Phase_04() {

	// 攻撃処理呼び出し
	if (false) {

		EnemyAttack_1();
	}
	// 攻撃処理呼び出し
	else if (false) {

		EnemyAttack_2();
	}
	// 攻撃処理呼び出し
	else if (false) {

		EnemyAttack_3();
	}
}