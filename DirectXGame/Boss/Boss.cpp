#include "Boss.h"
#include <BulletManager/Divide/BulletList.h>
#include <Player/Player.h>
#include <ImGuiManager.h>
#include <random>
#include <time.h>

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
	hp_ = 1;
	isDead_ = false;
	phase_ = p0;
	nextPhase_ = p1;

	// 当たり判定を初期化
	InitCollision();

	// ランダムを初期化
	srand((unsigned)time(nullptr));
}

void Boss::Update() {

	// デバッグ表示
	DebugWindow();

	// 死んでたら処理しない
	if (isDead_) {
		return;
	}

	switch (phase_) {
	case Boss::p0:
		Phase_0();
		break;
	case Boss::p1:
		Phase_1();
		break;
	case Boss::p2:
		Phase_2();
		break;
	case Boss::p3:
		Phase_3();
		break;
	case Boss::p4:
		Phase_4();
		break;
	case Boss::transition:
		Phase_Transition();
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

	ImGui::Text("Phase : %d", (int)phase_);
	ImGui::Text("HP : %d", hp_);
	ImGui::Text("IsDead : %s", isDead_ ? "TRUE" : "FALSE");

	ImGui::Separator();

	if (ImGui::TreeNode("Frames")) {
		ImGui::Text("1 : %d (%d)", AttackFrame01, DebugFrame01);
		ImGui::Text("2 : %d (%d)", AttackFrame02, DebugFrame02);
		ImGui::Text("3 : %d (%d)", AttackFrame03, DebugFrame03);
		ImGui::TreePop();
	}

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

void Boss::EnterBulletFunction(int mask, IBullet* data) {
	// プレイヤーに当たった時
	if (mask == MPlayer()) {
		data->isActive = false;
		// 当たり判定消えないのがバグになりそう
		//data->collider_->isActive = false;
	}
	// プレイヤーの弾
	if (mask == MPlayerBullet()) {
		data->isActive = false;
	}
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
	data->aliveFrame_ = 70;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 1.0f;
	data->collider_ = std::make_shared<ShapeCollider<Sphere>>(&data->colSphere_);
	// マスク
	data->collider_->mask = MBossBullet();

	// ヒット時処理
	data->collider_->enterLambda = [=](int mask) {
		EnterBulletFunction(mask, data);
		data->collider_->isEnable = data->isActive;
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(data->collider_);
	// 登録
	bulletManager_.Regist(data);
}

void Boss::CreateBulletEffective(float speed) {
	// 弾を生成する
	EffectiveBullet* data = new EffectiveBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	// 座標
	Vector3 pos = player_->GetTransform()->translation_;
	// 座標にランダムに足す
	pos.x += rand() % 20 - 10.0f;
	pos.y += rand() % 20 - 10.0f;
	Vector3 norm = Normalize(pos);
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = norm.x * speed;
	data->velocity_.y = norm.y * speed;
	data->aliveLength_ = 50;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 1.0f;
	data->collider_ = std::make_shared<ShapeCollider<Sphere>>(&data->colSphere_);
	// マスク
	data->collider_->mask = MBossBullet();

	// ヒット時処理
	data->collider_->enterLambda = [=](int mask) {
		EnterBulletFunction(mask, data);
		data->collider_->isEnable = data->isActive;
		};
	// 終了時の関数
	data->endFunction = [=]() {
		// 弾がどこにも当たらずに終了したら呼ばれる
		// 場所を正規化
		Vector3 norm = Normalize(data->transform_.translation_);
		// 波を発生させる
		CreateBulletWave(std::atan2(norm.y, norm.x), 5.0f);
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(data->collider_);
	// 登録
	bulletManager_.Regist(data);
}

void Boss::CreateBulletEffective2Way(float theta, float speed) {
	// 一つ目
	// 弾を生成する
	EffectiveBullet* data = new EffectiveBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	// 角度を出す
	float pTheta = player_->GetTheta();
	// 座標
	Vector3 pos = { std::cosf(pTheta + theta),std::sinf(pTheta + theta),0.0f };
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = pos.x * speed;
	data->velocity_.y = pos.y * speed;
	data->aliveLength_ = 50;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 1.0f;
	data->collider_ = std::make_shared<ShapeCollider<Sphere>>(&data->colSphere_);
	// マスク
	data->collider_->mask = MBossBullet();

	// ヒット時処理
	data->collider_->enterLambda = [=](int mask) {
		EnterBulletFunction(mask, data);
		data->collider_->isEnable = data->isActive;
		};
	// 終了時の関数
	data->endFunction = [=]() {
		// 弾がどこにも当たらずに終了したら呼ばれる
		// 場所を正規化
		Vector3 norm = Normalize(data->transform_.translation_);
		// 波を発生させる
		CreateBulletWave(std::atan2(norm.y, norm.x), 3.0f);
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(data->collider_);
	// 登録
	bulletManager_.Regist(data);

	// 二つ目
	// 弾を生成する
	data = new EffectiveBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	// 座標
	pos = { std::cosf(pTheta - theta),std::sinf(pTheta - theta),0.0f };
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = pos.x * speed;
	data->velocity_.y = pos.y * speed;
	data->aliveLength_ = 50;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 1.0f;
	data->collider_ = std::make_shared<ShapeCollider<Sphere>>(&data->colSphere_);
	// マスク
	data->collider_->mask = MBossBullet();

	// ヒット時処理
	data->collider_->enterLambda = [=](int mask) {
		EnterBulletFunction(mask, data);
		data->collider_->isEnable = data->isActive;
		};
	// 終了時の関数
	data->endFunction = [=]() {
		// 弾がどこにも当たらずに終了したら呼ばれる
		// 場所を正規化
		Vector3 norm = Normalize(data->transform_.translation_);
		// 波を発生させる
		CreateBulletWave(std::atan2(norm.y, norm.x), 3.0f);
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
		EnterBulletFunction(mask, data);
		data->collider_->isEnable = data->isActive;
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
		EnterBulletFunction(mask, data);
		data->collider_->isEnable = data->isActive;
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(data->collider_);
	// 登録
	bulletManager_.Regist(data);
}

void Boss::DecreasHP(int damage) {
	hp_ -= damage;
}

// エネミー攻撃処理
void Boss::EnemyAttack_1() {
	// プレイヤーを狙って飛んでくる弾
	CreateBulletSimple();
}

void Boss::EnemyAttack_2() {
	// プレイヤーの周りを狙って飛んでくる弾
	CreateBulletEffective(0.8f);
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

void Boss::EnemyAttack_4() {
	// プレイヤーを狙って飛んでくる弾
	CreateBulletSimple();
	// プレイヤーの周りを狙って飛んでくる弾
	CreateBulletEffective(0.5f);
}


void Boss::Phase_0() {
	// フェーズ1へ移行
	if (hp_ <= 0) {
		phase_ = transition;
		nextPhase_ = p1;
		hp_ = 10;
	}
}

//エネミーフェーズ処理
void Boss::Phase_1() {

	AttackFrame01--;

	//攻撃処理呼び出し
	if (AttackFrame01 <= 0) {
		EnemyAttack_1();
		//フレーム初期化
		AttackFrame01 = 80 + rand() % 20 - 10;

#ifdef _DEBUG
		DebugFrame01 = AttackFrame01;
#endif // _DEBUG
	}

	// フェーズ２へ移行
	if (hp_ <= 0) {
		phase_ = transition;
		nextPhase_ = p2;
		hp_ = 10;
	}
}

void Boss::Phase_2() {

	AttackFrame01--;
	AttackFrame02--;

	// 攻撃処理呼び出し
	if (AttackFrame01 <= 0) {
		EnemyAttack_1();
		AttackFrame01 = 80 + rand() % 30 - 15;

#ifdef _DEBUG
		DebugFrame01 = AttackFrame01;
#endif // _DEBUG
	}
	// 攻撃処理呼び出し
	if (AttackFrame02 <= 0) {
		EnemyAttack_2();
		AttackFrame02 = 100 + rand() % 10;

#ifdef _DEBUG
		DebugFrame02 = AttackFrame02;
#endif // _DEBUG
	}

	//フェーズ３へ移行
	if (hp_ <= 0) {
		phase_ = transition;
		nextPhase_ = p3;
		hp_ = 15;
	}
}

void Boss::Phase_3() {

	AttackFrame01--;
	AttackFrame03--;

	// 攻撃処理呼び出し
	if (AttackFrame01 <= 0) {
		EnemyAttack_1();
		AttackFrame01 = 100 + rand() % 20 - 15;

#ifdef _DEBUG
		DebugFrame01 = AttackFrame01;
#endif // _DEBUG
	}
	// 攻撃処理呼び出し
	if (AttackFrame03 <= 0) {
		EnemyAttack_2();
		//EnemyAttack_3();
		CreateBulletEffective2Way(0.6f, 0.75f);
		AttackFrame03 = 180 + rand() % 20 - 15;

#ifdef _DEBUG
		DebugFrame03 = AttackFrame03;
#endif // _DEBUG
	}

	// フェーズ４へ移行
	if (hp_ <= 0) {
		phase_ = transition;
		nextPhase_ = p4;
	}
}

void Boss::Phase_4() {
	// 死亡時の演出
	hp_--;
	if (hp_ <= 0) {
		isDead_ = true;
	}
}

void Boss::Phase_Transition() {
	// フェーズ移行時の行動
	endTransition_ = true;
	if (endTransition_) {
		phase_ = nextPhase_;
		endTransition_ = false;
		return;
	}
}
