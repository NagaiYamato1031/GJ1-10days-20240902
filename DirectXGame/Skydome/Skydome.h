#pragma once

#include <memory>
#include <Utility/Mymath.h>
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


class Skydome {
public:/*コンストラクタ*/
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Skydome() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Skydome() = default;

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
	/// デバッグ表示
	/// </summary>
	void DebugWindow();

private:
		// 3D モデル
	std::unique_ptr<Model> model_;

	// ワールド座標
	WorldTransform transform_;
};
