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
	model_.reset(Model::CreateFromOBJ("BossEnemy"));
	transform_.Initialize();
	transform_.scale_ = { 10.0f,10.0f,1.0f };

	//Hpbarの中心からの距離とか初期化
	displayHp_.Init();

	// 弾管理クラス初期化
	bulletManager_.Init();

	//ＨＰ・フラグ・フェーズ初期化
	hp_ = 1;
	isActive_ = true;
	isDead_ = false;
	phase_ = p0;
	nextPhase_ = p1;

	// 当たり判定を初期化
	InitCollision();

	// ランダムを初期化
	srand((unsigned)time(nullptr));

	// 色を保存
	// 緑
	colors_.push_back({ 0.0f,0.75f,0.0f,1.0f });
	// 黄
	colors_.push_back({ 0.95f,0.95f,0.0f,1.0f });
	colors_.push_back({ 0.95f,0.95f,0.0f,1.0f });
	// 赤
	colors_.push_back({ 0.75f,0.0f,0.0f,1.0f });
	// 灰
	colors_.push_back({ 0.25f,0.25f,0.25f,1.0f });
	// 初期化
	objectColor_.Initialize();
}

void Boss::Update() {
	//Hpbar更新
	displayHp_.Update();

	// デバッグ表示
	DebugWindow();

	// 死んでたら処理しない
	if (isDead_) {
		// 弾を消す
		bulletManager_.Init();
		UpdateDeath();
		return;
	}
	// プレイヤーが死んでいたら弾を消す
	if (player_->IsDead()) {
		bulletManager_.Init();
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

	// 色変更
	objectColor_.SetColor(colors_[colorIndex_]);
	objectColor_.TransferMatrix();

	// 行列の更新
	transform_.UpdateMatrix();
}

void Boss::DrawModel(ViewProjection* view) {

	//弾管理クラス描画
	bulletManager_.DrawModel(view);

	model_->Draw(transform_, *view, &objectColor_);
	displayHp_.DrawModel(view);
}

void Boss::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("BossWindow");

	if (ImGui::SliderInt("Phase", (int*)&phase_, 0, Phase::p4)) {
		colorIndex_ = phase_;
	}
	if (ImGui::Button("Reset")) {
		hp_ = 10;
		isDead_ = false;
	}
	ImGui::Text("HP : %d", hp_);
	ImGui::Text("IsDead : %s", isDead_ ? "TRUE" : "FALSE");

	if (ImGui::Button("Decrease")) {
		DecreaseHP(1);
	}

	if (ImGui::TreeNode("BulletFunction")) {

		if (ImGui::TreeNode("Effective")) {
			static float speed = 0.45f;
			ImGui::DragFloat("speed", &speed, 0.01f);
			if (ImGui::Button("Shot")) {
				CreateBulletEffective(speed);
			}
			ImGui::TreePop();
			ImGui::Separator();
		}
		if (ImGui::TreeNode("Homing")) {
			static float speed = 0.45f;
			ImGui::DragFloat("speed", &speed, 0.01f);
			if (ImGui::Button("Shot")) {
				CreateBulletHoming(speed);
			}
			ImGui::TreePop();
			ImGui::Separator();
		}
		if (ImGui::TreeNode("2Way")) {
			static float theta = 0.8f;
			static float speed = 0.45f;
			ImGui::DragFloat("theta", &theta, 0.001f);
			ImGui::DragFloat("speed", &speed, 0.01f);
			if (ImGui::Button("Shot")) {
				CreateBulletEffective2Way(theta, speed);
			}
			ImGui::TreePop();
			ImGui::Separator();
		}
		if (ImGui::TreeNode("Bound")) {
			static float speed = 0.45f;
			ImGui::DragFloat("speed", &speed, 0.01f);
			if (ImGui::Button("Shot")) {
				CreateBulletBound(speed);
			}
			ImGui::TreePop();
			ImGui::Separator();
		}

		ImGui::TreePop();
		ImGui::Separator();
	}

	ImGui::Separator();

	if (ImGui::TreeNode("Frames")) {
		ImGui::Text("1 : %d (%d)", AttackFrame01, DebugFrame01);
		ImGui::Text("2 : %d (%d)", AttackFrame02, DebugFrame02);
		ImGui::Text("3 : %d (%d)", AttackFrame03, DebugFrame03);
		ImGui::TreePop();
	}
	ImGui::Separator();

	if (ImGui::TreeNode("Color")) {
		ImGui::Text("ColorIndex : %d", colorIndex_);
		for (size_t i = 0; i < colors_.size(); i++) {
			ImGui::Text("Color[%d] : %.1f, %.1f, %.1f, %.1f", i, colors_[i].x, colors_[i].y, colors_[i].z, colors_[i].w);
		}

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
			DecreaseHP(1);
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

void Boss::CreateBulletEffective(float speed) {
	// 弾を生成する
	EffectiveBullet* data = new EffectiveBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	data->transform_.scale_ = { 2.0f,2.0f,1.0f };
	// 座標
	Vector3 pos = player_->GetTransform()->translation_;
	Vector3 norm = Normalize(pos);
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = norm.x * speed;
	data->velocity_.y = norm.y * speed;
	data->aliveLength_ = kPaddingCenter_;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 4.0f;
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
		CreateBulletWave(std::atan2(norm.y, norm.x), 10.0f);
		};

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(data->collider_);
	// 登録
	bulletManager_.Regist(data);
}

void Boss::CreateBulletHoming(float speed) {
	// 弾を生成する
	HomingBullet* data = new HomingBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	data->transform_.scale_ = { 2.0f,2.0f,1.0f };
	// 座標
	Vector3 pos = player_->GetTransform()->translation_;
	Vector3 norm = Normalize(pos);
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = norm.x * speed;
	data->velocity_.y = norm.y * speed;
	data->aliveLength_ = kPaddingCenter_;
	data->player_ = player_;
	data->speed_ = speed;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 4.0f;
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

void Boss::CreateBulletBound(float speed) {
	// 弾を生成する
	BoundBullet* data = new BoundBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	data->transform_.scale_ = { 2.0f,2.0f,1.0f };
	// 座標
	Vector3 pos = player_->GetTransform()->translation_;
	Vector3 norm = Normalize(pos);
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = norm.x * speed;
	data->velocity_.y = norm.y * speed;
	data->aliveLength_ = kPaddingCenter_;
	data->hp_ = 2;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 4.0f;
	data->collider_ = std::make_shared<ShapeCollider<Sphere>>(&data->colSphere_);
	// マスク
	data->collider_->mask = MBossBullet();

	// ヒット時処理
	data->collider_->enterLambda = [=](int mask) {
		if (mask == MPlayerBullet()) {
			data->DecreaseHP(1);
		}
		};
	// 終了時の関数
	data->endFunction = [=]() {
		// 弾がどこにも当たらずに終了したら呼ばれる
		// 場所を正規化
		Vector3 norm = Normalize(data->transform_.translation_);
		// 波を発生させる
		CreateBulletWave(std::atan2(norm.y, norm.x), 10.0f);
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
	data->transform_.scale_ = { 2.0f,2.0f,1.0f };
	// 角度を出す
	float pTheta = player_->GetTheta();
	// 座標
	Vector3 pos = { std::cosf(pTheta + theta),std::sinf(pTheta + theta),0.0f };
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = pos.x * speed;
	data->velocity_.y = pos.y * speed;
	data->aliveLength_ = kPaddingCenter_;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 4.0f;
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
		// 2 Way の真ん中まで届かせたい
		CreateBulletWave(std::atan2(norm.y, norm.x), 10.0f);
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
	data->transform_.scale_ = { 2.0f,2.0f,1.0f };
	// 座標
	pos = { std::cosf(pTheta - theta),std::sinf(pTheta - theta),0.0f };
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = pos.x * speed;
	data->velocity_.y = pos.y * speed;
	data->aliveLength_ = kPaddingCenter_;
	//　球の当たり判定
	data->colSphere_.center = { 0.0f,0.0f,0.0f };
	data->colSphere_.radius = 4.0f;
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
		CreateBulletWave(std::atan2(norm.y, norm.x), 10.0f);
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

void Boss::DecreaseHP(int damage) {
	// フェーズ移行中は無敵
	if (phase_ == Phase::transition) {
		return;
	}
	hp_ -= damage;
	displayHp_.DamageBreak();
}

// エネミー攻撃処理
void Boss::EnemyAttack_1() {
	// プレイヤーを狙って飛んでくる弾
	CreateBulletEffective();
}

void Boss::EnemyAttack_2() {
	// プレイヤーの周りを狙って飛んでくる弾
	CreateBulletHoming(0.4f);
}

void Boss::EnemyAttack_3() {
	// バウンドする弾を撃つ
	CreateBulletBound(0.2f);
}

void Boss::EnemyAttack_4() {
	// プレイヤーを狙って飛んでくる弾
	CreateBulletEffective();
	// 2 Way を撃つ
	CreateBulletEffective2Way(2.37f, 1.0f);
}


void Boss::Phase_0() {
	// フェーズ1へ移行
	if (hp_ <= 0) {
		phase_ = transition;
		nextPhase_ = p1;
		hp_ = 6;
		transitionFrame_ = 60;
	}
}

//エネミーフェーズ処理
void Boss::Phase_1() {

	AttackFrame01--;
	AttackFrame02--;

	//攻撃処理呼び出し
	if (AttackFrame01 <= 0) {
		EnemyAttack_1();
		//フレーム初期化
		AttackFrame01 = 200 + rand() % 10;

#ifdef _DEBUG
		DebugFrame01 = AttackFrame01;
#endif // _DEBUG
	}
	// 攻撃処理呼び出し
	if (AttackFrame02 <= 0) {
		EnemyAttack_2();
		AttackFrame02 = 600 - rand() % 10;

#ifdef _DEBUG
		DebugFrame02 = AttackFrame02;
#endif // _DEBUG
	}

	// フェーズ２へ移行
	if (hp_ <= 0) {
		phase_ = transition;
		nextPhase_ = p2;
		hp_ = 8;
		transitionFrame_ = 60;

	}
}

void Boss::Phase_2() {

	AttackFrame01--;
	AttackFrame02--;
	AttackFrame03--;

	// 攻撃処理呼び出し
	if (AttackFrame01 <= 0) {
		EnemyAttack_4();
		AttackFrame01 = 200 + rand() % 15;

#ifdef _DEBUG
		DebugFrame01 = AttackFrame01;
#endif // _DEBUG
	}
	// 攻撃処理呼び出し
	if (AttackFrame02 <= 0) {
		EnemyAttack_2();
		AttackFrame02 = 600 - rand() % 10;

#ifdef _DEBUG
		DebugFrame02 = AttackFrame02;
#endif // _DEBUG
	}
	// 攻撃処理呼び出し
	if (AttackFrame03 <= 0) {
		//EnemyAttack_3();
		CreateBulletEffective2Way(0.6f, 0.5f);
		AttackFrame03 = 500 + rand() % 15;

#ifdef _DEBUG
		DebugFrame03 = AttackFrame03;
#endif // _DEBUG
	}

	//フェーズ３へ移行
	if (hp_ <= 0) {
		phase_ = transition;
		nextPhase_ = p3;
		hp_ = 10;
		transitionFrame_ = 60;
	}
}

void Boss::Phase_3() {

	AttackFrame01--;
	AttackFrame02--;
	AttackFrame03--;

	// 攻撃処理呼び出し
	if (AttackFrame01 <= 0) {
		EnemyAttack_4();
		AttackFrame01 = 150 + rand() % 20 - 15;

#ifdef _DEBUG
		DebugFrame01 = AttackFrame01;
#endif // _DEBUG
	}
	// 攻撃処理呼び出し
	if (AttackFrame02 <= 0) {
		EnemyAttack_3();
		AttackFrame02 = 600 - rand() % 10;

#ifdef _DEBUG
		DebugFrame02 = AttackFrame02;
#endif // _DEBUG
	}
	// 攻撃処理呼び出し
	if (AttackFrame03 <= 0) {
		//EnemyAttack_2();
		//EnemyAttack_3();
		CreateBulletEffective2Way(1.0f, 0.75f);
		AttackFrame03 = 180 + rand() % 20 - 15;

#ifdef _DEBUG
		DebugFrame03 = AttackFrame03;
#endif // _DEBUG
	}

	// フェーズ４へ移行
	if (hp_ <= 0) {
		phase_ = transition;
		nextPhase_ = p4;
		transitionFrame_ = 60;
		// 弾を消す
		bulletManager_.Init();
	}
}

void Boss::Phase_4() {
	// 現状何もしていない
	isDead_ = true;
}

void Boss::Phase_Transition() {
	// フェーズ移行時の行動
	transitionFrame_--;
	if (transitionFrame_ <= 0) {
		phase_ = nextPhase_;
		colorIndex_ = phase_;
		//Hpbar表示
		displayHp_.Create(transform_.translation_, hp_);
		return;
	}
}

void Boss::UpdateDeath() {
	animationFrame_++;
	if (300 <= animationFrame_) {
		// 演出した後に役割が終わったことを知らせる
		isActive_ = false;
		return;
	}
	if (animationFrame_ <= 200) {
		transform_.scale_ -= {0.03f, 0.03f, 0.03f};
	}
	transform_.UpdateMatrix();
}
