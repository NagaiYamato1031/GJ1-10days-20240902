#pragma once

#include <Utility/Mymath.h>
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

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

private: //** プライベート変数 **//

	// 3D モデル
	std::unique_ptr<Model> model_;

	// ワールド座標
	WorldTransform transform_;

	// 当たり判定


};