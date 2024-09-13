#pragma once

#include <FollowCamera/FollowCamera.h>
#include <Player/Player.h>
#include <Stage/Stage.h>
#include <Skydome/Skydome.h>
#include <Boss/Boss.h>
#include <Collider/CollisionManager.h>

#include "SceneManager/IScene.h"

#include "EndScene.h"

#include "Sprite.h"
#include "TextureManager.h"

// IScene クラスを継承したタイトルシーン
class TestScene : public ACJPN::Scene::IScene {
public: //** パブリック関数 **//

	TestScene();
	~TestScene();

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

	Audio* audio_ = nullptr;
	uint32_t soundHandle_ = 0u;


	// 遷移するフレーム
	int kTransitionFrame_ = 60;

	// 時間を測る
	int time = 0;

	// カメラ
	FollowCamera camera_;
	// プレイヤー
	Player player_;
	// ステージ
	Stage stage_;
	//スカイドーム
	Skydome skydome_;
	// ボス
	Boss boss_;

	// 画面遷移用の画像
	uint32_t textureHandle_ = 0u;
	std::unique_ptr<Sprite> transitionSprite_;
	Vector2 transitionPosition_ = { 1280,0 };

private: //** メンバ関数 **//

	/// <summary>
	/// 遷移中の更新
	/// </summary>
	void TransitionUpdate();
};