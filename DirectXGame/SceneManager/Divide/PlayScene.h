#pragma once

#include "SceneManager/IScene.h"

#include <TextureManager.h>
#include <FollowCamera/FollowCamera.h>
#include <Player/Player.h>
#include <Skydome/Skydome.h>
#include <Stage/Stage.h>
#include <Boss/Boss.h>
#include <Collider/CollisionManager.h>

// IScene クラスを継承したゲームプレイシーン
class PlayScene : public ACJPN::Scene::IScene {
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

	//スカイドーム
	Skydome skydome_;
	// ステージ
	Stage stage_;
	// カメラ
	FollowCamera camera_;
	// プレイヤー
	Player player_;
	// ボス
	Boss boss_;

	// 遷移するフレーム
	int kTransitionFrame_ = 60;

	// 時間を測る
	int time = 0;

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