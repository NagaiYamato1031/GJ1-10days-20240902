#pragma once

#include "SceneManager/IScene.h"

#include "Sprite.h"
#include "TextureManager.h"
#include <FollowCamera/FollowCamera.h>
#include <Player/Player.h>
#include <Skydome/Skydome.h>
#include <Stage/Stage.h>
#include <Boss/Boss.h>
#include <Collider/CollisionManager.h>

// IScene クラスを継承したタイトルシーン
class TitleScene : public ACJPN::Scene::IScene {
public: //** パブリック関数 **//

	TitleScene();
	~TitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 背景の描画
	/// </summary>
	void DrawBackdrop() override;
	/// <summary>
	/// モデルの描画
	/// </summary>
	void Draw3D() override;
	/// <summary>
	/// UI の描画
	/// </summary>
	void DrawOverlay() override;

	/// <summary>
	/// デバッグ情報
	/// </summary>
	void DebugWindow() override;
private: //** メンバ変数 **//

	// 当たり判定マネージャ
	ACJPN::Collider::CollisionManager* collisionManager_ = nullptr;

	// タイトルの画像
	uint32_t textureTitle_ = 0u;
	std::unique_ptr<Sprite> titleSprite_;
	Vector2 kSpritePosition_ = { 1280 * 0.5f,500.0f };

	// スカイドーム
	Skydome skydome_;
	// ステージ
	Stage stage_;
	// プレイヤー
	Player player_;
	// カメラ
	FollowCamera camera_;

	// 当たり判定を作る
	ACJPN::Math::Sphere colSphere_;
	std::shared_ptr < ACJPN::Collider::ShapeCollider<ACJPN::Math::Sphere>> collider_;

private: //** メンバ関数 **//
};