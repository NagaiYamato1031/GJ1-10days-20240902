#pragma once

#include "SceneManager/IScene.h"

#include "DirectXCommon.h"
#include "Sprite.h"

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

	bool selectTitle_ = true;

	Vector3 toTitlePosition_ = {0, 0, 0};
	Vector3 toPlayPosition_ = {0, 0, 0};

	uint32_t textHandleTitle_ = 0;
	uint32_t textHandlePlay_ = 0;

	Sprite* spriteT_ = nullptr;
	Sprite* spriteP_ = nullptr;


private: //** メンバ関数 **//
};