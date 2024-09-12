#pragma once

#include <functional>
#include <BulletManager/IBullet.h>
#include <Collider/CollisionManager.h>

/// <summary>
/// ただまっすぐに飛んでいく
/// </summary>
class SpecialBullet : public IBullet {
public: //** コンストラクタ **//

	SpecialBullet() = default;
	~SpecialBullet() override = default;

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

	// 生きている距離
	int aliveLength_ = 50;

	// 弾の体力
	int hp_ = 1;

	// 弾が消えるときに呼ばれる関数を入れる
	std::function<void()> endFunction = []() {};

	// 進む速度
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };

	// 当たり判定
	ACJPN::Math::Sphere colSphere_;
	std::shared_ptr < ACJPN::Collider::ShapeCollider<ACJPN::Math::Sphere>> collider_;
};