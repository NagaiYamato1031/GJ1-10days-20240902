#pragma once

#include "SceneManager/IScene.h"

#include "DirectXCommon.h"
#include "Sprite.h"

#include <Skydome/Skydome.h>

// IScene クラスを継承した終了時のシーン
class EndScene : public ACJPN::Scene::IScene {
public: //** パブリック関数 **//

	EndScene();
	~EndScene();

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

	DirectXCommon* dxCommon_ = nullptr;

	// カメラ
	ViewProjection camera_;

	// スカイドーム
	Skydome skydome_;

	// 画像表示
	Vector2 spriteTitlePosition_ = { 0, 0 };
	uint32_t textHandleTitle_ = 0;
	std::unique_ptr<Sprite> spriteTitle_;

private: //** メンバ関数 **//
};