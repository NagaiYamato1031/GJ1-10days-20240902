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

	/// <summary>
	/// ワールド座標取得
	/// </summary>
	WorldTransform* GetTransform() { return &transform_; }

	/// <summary>
	/// デバッグ情報
	/// </summary>
	void DebugWindow();

private: //** メンバ変数 **//
	// 入力管理
	Input* input_ = nullptr;

	// 3D モデル
	Model* model_ = nullptr;

	// ワールド座標
	WorldTransform transform_;

	// 中心からの距離
	float kPaddingCenter_ = 50.0f;
	
	// 中心からの回転角
	float theta_ = 0.0f;

	// 一度に変更する角度
	float kSpeed_ = 0.02f;

};

