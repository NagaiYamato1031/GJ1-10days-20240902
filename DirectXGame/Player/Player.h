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
	/// ワールド座標取得
	/// </summary>
	WorldTransform* GetTransform() { return &transform_; }

	/// <summary>
	/// デバッグ情報
	/// </summary>
	void DebugWindow();

private: //** メンバ変数 **//
	// 一度に変更する角度
	float kSpeed_ = 0.02f;

	// 中心からの距離
	float kPaddingCenter_ = 50.0f;

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

	// 横移動は完全に別原理で動かさなければいけないのでは...?

	// 現在の行動
	Behavior behavior_ = Behavior::None;
	// 次の行動
	std::optional<Behavior> reqBehavior_ = std::nullopt;

	// 行動初期化関数配列
	std::vector<void(Player::*)()> initFunc;

	// 行動更新関数配列
	std::vector<void(Player::*)()> updateFunc;


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
};

