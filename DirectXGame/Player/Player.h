#pragma once

#include <memory>
#include <optional>

#include <Utility/Mymath.h>
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <BulletManager/BulletManager.h>
#include <Collider/CollisionManager.h>
#include "PlayerHP.h"

/// <summary>
/// 操作するプレイヤー
/// </summary>
class Player {
private: //** サブクラス **//

	/// <summary>
	/// 各振る舞い
	/// </summary>
	enum Behavior {
		None = 0,
		Jump,
		Fall,
		Drop,

		_Count,
	};

	/// <summary>
	/// フラグを管理する構造体
	/// </summary>
	struct Flags {
		// プレイヤーが地面についているフラグ
		bool isGround_ = true;
		// ジャンプしているフラグ
		bool isJumping_ = false;
		// 先行入力
		bool isDrop_ = false;
		// 無敵判定
		bool isInvincible_ = false;
		// 描画フラグ
		bool isDraw_ = true;
	};

public: //** コンストラクタ **//

	Player() = default;
	~Player() = default;

public: // パブリック関数 **//

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
	/// UI 描画
	/// </summary>
	void DrawOverlay();

	/// <summary>
	/// ワールド座標取得
	/// </summary>
	WorldTransform* GetTransform() { return &transform_; }

	/// <summary>
	/// 角度を取得
	/// </summary>
	float GetTheta() const { return theta_; }

	/// <summary>
	/// デバッグ情報
	/// </summary>
	void DebugWindow();

	bool IsActive() const { return isActive_; }
	bool IsDead() const { return isDead_; }

private: //** メンバ変数 **//

	// このクラスが動いているかどうか
	bool isActive_ = true;

	// 死んでしまったかどうか
	bool isDead_ = false;

	// 無敵時間固定値
	int kInvincibleFrame_ = 60;

	// 一度に変更する角度
	float kSpeed_ = 0.01f;

	// 中心からの距離
	float kPaddingCenter_ = 50.0f;
	// 急降下ができる距離
	float kPaddingDrop_ = 10.0f;

	// 無敵判定フレーム
	int invincibleFrame_ = 0;

	// 入力管理
	Input* input_ = nullptr;

	// 3D モデル
	std::unique_ptr<Model> model_;

	// ワールド座標
	WorldTransform transform_;

	// フラグ
	Flags flag_;

	// 弾管理
	BulletManager bulletManager_;

	// プレイヤーの HP を表示
	PlayerHP playerHP_;

	// 中心からの回転角
	float theta_ = 0.0f;

	// ステージからの距離
	float distance_ = 0.0f;
	// ジャンプ挙動を滑らかにする変数
	float fineAir_ = 0.0f;

	// 最終的な原点からの距離
	float latestDistance_ = 0.0f;

	// 経過時間
	int elapsedFrame_ = 0;

	// 体力
	int hp_ = 10;

	// 横移動は完全に別原理で動かさなければいけないのでは...?

	// 現在の行動
	Behavior behavior_ = Behavior::None;
	// 次の行動
	std::optional<Behavior> reqBehavior_ = std::nullopt;

	// 行動初期化関数配列
	std::vector<void(Player::*)()> initFunc;

	// 行動更新関数配列
	std::vector<void(Player::*)()> updateFunc;

	// 当たり判定
	ACJPN::Math::Sphere colSphere_;
	std::shared_ptr < ACJPN::Collider::ShapeCollider<ACJPN::Math::Sphere>> collider_;

private: //** メンバ関数 **//

	/// <summary>
	/// 行動毎の関数を初期化更新する配列を初期化する
	/// </summary>
	void InitFunctionArray();

	//--** 各行動 **--//

	//** 初期化 **//
	void InitNone();
	void InitJump();
	void InitFall();
	void InitDrop();

	//** 更新 **//
	void UpdateNone();
	void UpdateJump();
	void UpdateFall();
	void UpdateDrop();


	/// <summary>
	/// 当たり判定の初期設定
	/// </summary>
	void InitCollision();

	/// <summary>
	/// 撃つ弾を生成していろいろ登録する
	/// </summary>
	void CreateBullet();

	/// <summary>
	/// HP を減らす
	/// </summary>
	void DecreaseHP(int damage);

	/// <summary>
	/// 死んでいる時に更新する
	/// ごり押しアニメーション
	/// </summary>
	void UpdateDeath();
};

