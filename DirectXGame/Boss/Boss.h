#pragma once

#include <memory>
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Utility/Mymath.h>
#include <BulletManager/BulletManager.h>

// 前方宣言
class Player;

/// <summary>
/// ボス
/// 後で仮想化するかもしれない
/// </summary>
class Boss {
public: //** コンストラクタ **//

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Boss() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Boss() = default;

public: //** パブリック関数 **//

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// モデル描画
	/// </summary>
	void DrawModel(ViewProjection* view);

	/// <summary>
	/// フラグ取得
	/// </summary>
	bool IsDead() const { return isDead_; }

	void SetPlayer(Player* p) { player_ = p; }

private: //** プライベート変数 **//

	// 3D モデル
	std::unique_ptr<Model> model_;

	// ワールド座標
	WorldTransform transform_;

	// 弾管理
	BulletManager bulletManager_;

	// プレイヤーを参照する
	Player* player_ = nullptr;

	//エネミー体力
	int EnemyHP_ = 40;

	//エネミー攻撃遷移フレーム
	int AttackFrame01 = 180;
	int AttackFrame02 = 180;
	int AttackFrame03 = 360;

	// 中心からの回転角
	float theta_ = 0.0f;

	//エネミー死亡判定
	bool isDead_ = false;

	//フェーズ一覧
	enum Phase {
		p1,
		p2,
		p3,
		p4,
	};

	//現在の行動
	Phase phase_ = Phase::p1;

private:

	//エネミー攻撃手段
	void EnemyAttack_1(); //自機狙い

	void EnemyAttack_2(); //自機周辺狙い

	void EnemyAttack_3(); //波発生

	//エネミーフェーズ
	void Phase_01(); //第一段階

	void Phase_02(); //第二段階

	void Phase_03(); //第三段階

	void Phase_04(); //最終段階
};