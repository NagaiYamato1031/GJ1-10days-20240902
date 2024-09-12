#pragma once

#include "SceneManager/IScene.h"

#include <FollowCamera/FollowCamera.h>
#include <Player/Player.h>
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

	// カメラ
	FollowCamera camera_;
	// プレイヤー
	Player player_;
	// ステージ
	Stage stage_;
	// ボス
	Boss boss_;

	// 原点のわかるオブジェクト
	std::unique_ptr<Model> origin_;
	WorldTransform originTransform_;

	// 原点から東にあるオブジェクト
	std::unique_ptr<Model> east_;
	WorldTransform eastTransform_;

private: //** メンバ関数 **//
};