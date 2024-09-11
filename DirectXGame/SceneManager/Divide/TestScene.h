#pragma once

#include <FollowCamera/FollowCamera.h>
#include <Player/Player.h>
#include <Stage/Stage.h>
#include <Boss/Boss.h>
#include <Collider/CollisionManager.h>

#include "SceneManager/IScene.h"

#include "EndScene.h"

// IScene クラスを継承したタイトルシーン
class TestScene : public ACJPN::Scene::IScene {
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

	// 時間を測る
	int time = 0;

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

	ACJPN::Math::Sphere sphere_;
	std::shared_ptr<ACJPN::Collider::ShapeCollider<ACJPN::Math::Sphere>> colSphere;

private: //** メンバ関数 **//

	/// <summary>
	/// 遷移中の更新
	/// </summary>
	void TransitionUpdate();
};