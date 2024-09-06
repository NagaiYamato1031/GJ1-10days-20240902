#pragma once
#include "SceneManager/IScene.h"

/// <summary>
/// IScene クラスを継承したテストシーン
/// このファイルの変更は git に登録されない
/// </summary>
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
	

private: //** メンバ関数 **//
};