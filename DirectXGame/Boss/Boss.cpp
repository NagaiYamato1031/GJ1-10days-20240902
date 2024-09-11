#include "Boss.h"
#include <BulletManager/Divide/BulletList.h>
#include <Player/Player.h>

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
	EnemyHP_ = 40;
	isDead_ = false;
	phase_ = p1;
	//　球の当たり判定
	colSphere_.center = { 0.0f,0.0f,0.0f };
	colSphere_.radius = 10.0f;
	collider_ = std::make_shared<ShapeCollider<Sphere>>(&colSphere_);
	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->RegistCollider(MBoss(), collider_);
}

void Boss::Update() {

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
	if (EnemyHP_ >= 29 && EnemyHP_ <= 30) {
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
	if (EnemyHP_ >= 19 && EnemyHP_ <= 28) {
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
	if (EnemyHP_ >= 9 && EnemyHP_ <= 18) {
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

	//エネミーのHPが０以下になったらEndSceneに移行
	if (EnemyHP_ >= 0 && EnemyHP_ <= 9) {

		//フラグをTrueにする
		isDead_ = true;
	}
}

// エネミー攻撃処理
void Boss::EnemyAttack_1() {

	// プレイヤーを狙って飛んでくる弾
	SimpleBullet* data = new SimpleBullet;
	data->Init();
	data->transform_.translation_ = transform_.translation_;
	// 座標
	Vector3 pos = player_->GetTransform()->translation_;
	Vector3 norm = Normalize(pos);
	// 弾とプレイヤーの距離を計算する
	data->velocity_.x = norm.x * 1.0f;
	data->velocity_.y = norm.y * 1.0f;
	// 登録
	bulletManager_.Regist(data);
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
