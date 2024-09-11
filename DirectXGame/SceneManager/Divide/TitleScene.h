#pragma once

#include "SceneManager/IScene.h"

#include "DirectXCommon.h"
#include "Sprite.h"

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

	DirectXCommon* dxCommon_ = nullptr;

	//タイトル背景画像
	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;

	//タイトル文字
	uint32_t textureHandleMozi_ = 0;
	Sprite* spriteMozi_ = nullptr;

private: //** メンバ関数 **//
};