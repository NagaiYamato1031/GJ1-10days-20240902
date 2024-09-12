#pragma once

#include <BulletManager/IBullet.h>
#include <Collider/CollisionManager.h>

/// <summary>
/// ステージに沿うように原点から一定の範囲離れたところを回転する
/// </summary>
class WaveBullet : public IBullet {
public: //** コンストラクタ **//

	WaveBullet() = default;
	~WaveBullet() override = default;

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

	// 値は 1 の時を考えている
	// 最大サイズ
	float kMaxSize = 5.0f;
	// 最小サイズ
	float kMinSize = 0.5f;

	// 円状の角度
	float theta_ = 0.0f;
	// 進む角度
	float omega_ = 0.001f;

	// 波の強さ
	float power_ = 1.0f;

	// 当たり判定
	ACJPN::Math::Sphere colSphere_;
	std::shared_ptr < ACJPN::Collider::ShapeCollider<ACJPN::Math::Sphere>> collider_;
};