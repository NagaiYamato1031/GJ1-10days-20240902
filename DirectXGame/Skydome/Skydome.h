#pragma once

#include <memory>
#include <Utility/Mymath.h>
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


class Skydome {
public:/*コンストラクタ*/
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Skydome() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Skydome() = default;

	public: //** パブリック関数 **//
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// モデル描画
	/// </summary>
	void DrawModel(ViewProjection* view);

	/// <summary>
	/// デバッグ表示
	/// </summary>
	void DebugWindow();


	/// <summary>
	/// チカチカする演出
	/// </summary>
	void DirectionTwinkle();

	/// <summary>
	/// 赤くなったりする演出
	/// </summary>
	void DirectionRed();

	/// <summary>
	/// 暗くなる演出
	/// </summary>
	void DirectionTurnOff();

private:
		// 3D モデル
	std::unique_ptr<Model> model_;

	// ワールド座標
	WorldTransform transform_;
	// 色変更
	ObjectColor objColor_;
	// 色
	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	Vector4 preColor_ = { 1.0f,1.0f,1.0f,1.0f };

	// 色の固定値
	int kColorRange1_ = 10;
	int kColorRange2_ = 100;
	int kColorRange3_ = 250;

	// 時間で変える変数
	int t = 0;
	// フラグでプラスマイナスを変える
	bool isToggle_ = false;

	// 暗くする演出用のフラグ
	bool endTurnOff_ = false;

	// 関数が呼ばれた瞬間のフラグ
	bool isCall_ = false;

};
