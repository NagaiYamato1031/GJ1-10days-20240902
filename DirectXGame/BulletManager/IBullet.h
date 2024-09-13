#pragma once

#include <memory>

#include <Utility/Mymath.h>
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// すべての弾の継承元
/// </summary>
class IBullet {
public: //** コンストラクタ **//

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IBullet() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IBullet() = default;

public: //** パブリック関数 **//

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() { Init("cube"); };
	/// <summary>
	/// モデルを指定して初期化
	/// </summary>
	/// <param name="name"></param>
	virtual void Init(const std::string& name) {
		model_.reset(Model::CreateFromOBJ(name));
		transform_.Initialize();
	};

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// モデル描画
	/// </summary>
	virtual void DrawModel(ViewProjection* view) { view; }

	void UpdateColor() {
		objColor_.SetColor(color_);
		objColor_.TransferMatrix();
	}

public: //** パブリック変数 **//

	// このインスタンスが稼働状態か
	bool isActive = true;

	// ワールド座標
	WorldTransform transform_;

	// 3D モデル
	std::unique_ptr<Model> model_;
	ObjectColor objColor_;
	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };

	// 経過フレーム
	int elapsedFrame = 0;

};