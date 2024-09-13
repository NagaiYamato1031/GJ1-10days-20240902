#include "PlayerHP.h"

void PlayerHP::Init(int hp) {
	float x = 480.0f;
	back_.Init();
	back_.anchorPoint_ = { 0.0f,0.0f };
	back_.scale_ = { 310.0f,40.0f };
	back_.position_ = { x,20.0f };
	back_.color_ = { 0.4f,0.1f,0.1f,0.75f };
	HP_.resize(hp);
	for (size_t i = 0; i < hp; i++) {
		HP_[i].Init();
		HP_[i].anchorPoint_ = { 0.0f,0.0f };
		HP_[i].scale_ = { 20.0f,20.0f };
		HP_[i].position_ = { x + 10.0f,30.0f };
		HP_[i].position_.x += 30 * i;
		float t = 1.0f - (i / (float)hp);
		HP_[i].color_ = { 0.75f * t,0.2f + 1.0f * t,0.2f + 0.3f * t,0.9f };
	}
}

void PlayerHP::Update() {
	back_.Update();
	for (size_t i = 0; i < HP_.size(); i++) {
		HP_[i].Update();
	}
}

void PlayerHP::DrawSprite() {
	back_.Draw();
	for (size_t i = 0; i < HP_.size(); i++) {
		if (HP_[i].isDraw_) {
			HP_[i].Draw();
		}
	}
}

void PlayerHP::DecreaseHP() {
	for (size_t i = 0; i < HP_.size(); i++) {
		if (HP_[i].isDraw_) {
			HP_[i].isDraw_ = false;
			return;
		}
	}
}
