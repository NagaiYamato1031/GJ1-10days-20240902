#pragma once

#include <memory>
#include <vector>
#include "Sprite.h"

#include <Utility/Mymath.h>

class PlayerHP {
private: //** サブクラス **//

	struct SpriteData {
		std::unique_ptr<Sprite> data_;
		Vector2 position_ = { 0.0f,0.0f };
		Vector2 normal_ = { 1.0f,1.0f };
		Vector2 scale_ = { 1.0f,1.0f };
		Vector2 anchorPoint_ = { 0.0f,0.0f };
		uint32_t texture_ = 0u;
		Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };
		void Init(std::string texture = "white1x1.png") {
			data_.reset(Sprite::Create(texture_, position_));
			normal_ = data_->GetSize();
		}
		void Update() {
			data_->SetAnchorPoint(anchorPoint_);
			Vector2 size = normal_;
			size.x *= scale_.x;
			size.y *= scale_.y;
			data_->SetSize(size);
			data_->SetPosition(position_);
			data_->SetColor(color_);
		}
		void Draw() {
			data_->Draw();
		}
	};

	struct HPData : SpriteData {
		bool isDraw_ = true;
	};

public: //** コンストラクタ **//
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerHP() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerHP() = default;

public: //** パブリック関数 **//

	/// <summary>
	/// 初期化
	/// </summary>
	void Init(int hp = 10);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// UI 描画
	/// </summary>
	void DrawSprite();

	/// <summary>
	/// HP の表示を一つ消す
	/// </summary>
	void DecreaseHP();

private: //** プライベート変数 **//

	SpriteData back_;
	std::vector<HPData> HP_;

};