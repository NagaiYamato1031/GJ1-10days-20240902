#pragma once

#include <Utility/Mymath.h>
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// 操作するプレイヤー
/// </summary>
class Player {
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

	WorldTransform* GetTransform() { return &transform_; }

private: //** メンバ変数 **//
	// 入力管理
	Input* input_ = nullptr;

	// 3D モデル
	Model* model_ = nullptr;

	// ワールド座標
	WorldTransform transform_;
};

