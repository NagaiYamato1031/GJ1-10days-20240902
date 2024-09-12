#pragma once

#include <functional>
#include <BulletManager/IBullet.h>
#include <Collider/CollisionManager.h>

class Player;

/// <summary>
/// 波を起こす機能を持った弾
/// </summary>
class HomingBullet : public IBullet {
public: //** コンストラクタ **//

	HomingBullet() = default;
	~HomingBullet() override = default;

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

	// 生存する距離
	float aliveLength_ = 50.0f;

	// 弾が消えるときに呼ばれる関数を入れる
	std::function<void()> endFunction = []() {};

	// 弾の速度
	float speed_ = 0.5f;

	// プレイヤーの座標を取得する
	Player* player_ = nullptr;

	// 進む速度
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };

	// 当たり判定
	ACJPN::Math::Sphere colSphere_;
	std::shared_ptr < ACJPN::Collider::ShapeCollider<ACJPN::Math::Sphere>> collider_;
};