#pragma once

#include <functional>
#include <BulletManager/IBullet.h>
#include <Collider/CollisionManager.h>
#include <Particle/ParticleEffects.h>

/// <summary>
/// 波を起こす機能を持った弾
/// 体力があって跳ねる
/// </summary>
class BoundBullet : public IBullet {
public: //** コンストラクタ **//

	BoundBullet() = default;
	~BoundBullet() override = default;

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

	/// <summary>
	/// HP を減らす
	/// </summary>
	void DecreaseHP(int damage);

public: //** パブリック関数 **//

	// 生存する距離
	float aliveLength_ = 50.0f;

	// 弾が消えるときに呼ばれる関数を入れる
	std::function<void()> endFunction = []() {};

	// 弾の体力
	int hp_ = 2;

	// 速度が外側に向かっているか
	bool isOutMove_ = true;

	// 進む速度
	Vector3 direct_ = { 0.0f,0.0f,0.0f };
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };

	// 当たり判定
	ACJPN::Math::Sphere colSphere_;
	std::shared_ptr < ACJPN::Collider::ShapeCollider<ACJPN::Math::Sphere>> collider_;
};