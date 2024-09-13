#pragma once

#include <FollowCamera/FollowCamera.h>
#include <Player/Player.h>
#include <Stage/Stage.h>
#include <Skydome/Skydome.h>
#include <Boss/Boss.h>
#include <Collider/CollisionManager.h>
#include <Boss/DisplayHp.h>

#include "SceneManager/IScene.h"

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

	// ハンドル
	uint32_t soundHandle_ = 0u;


private: //** メンバ関数 **//

};