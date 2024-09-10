#pragma once

#include "SceneManager/IScene.h"

#include <Player/Player.h>
#include <Particle/ParticleEffects.h>

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
private: //** メンバ変数 **//

	// 時間を測る
	int time = 0;

	// カメラ
	std::unique_ptr<ViewProjection> camera_;

	std::unique_ptr<Player> player_;

	std::unique_ptr<ParticleEffects> particleEffects_;



private: //** メンバ関数 **//

	/// <summary>
	/// 遷移中の更新
	/// </summary>
	void TransitionUpdate();

	float testDeg;
	Vector3 testVec;
};