#pragma once

#include <BulletManager/IBullet.h>

/// <summary>
/// ただまっすぐに飛んでいく
/// </summary>
class SimpleBullet : public IBullet {
public: //** コンストラクタ **//

	SimpleBullet() = default;
	~SimpleBullet() override = default;

public: //** パブリック関数 **//

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// モデル描画
	/// </summary>
	void DrawModel(ViewProjection* view) override;

public: //** パブリック関数 **//

	// 進む速度
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };

};