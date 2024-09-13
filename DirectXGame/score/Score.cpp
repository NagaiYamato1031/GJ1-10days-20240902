#include "Score.h"

#include <time.h>
#include <stdio.h>
#include <ImGuiManager.h>
#include <TextureManager.h>

using namespace ACJPN;
using namespace ACJPN::Math;

void Score::Init(const Vector2& position) { 
	time_ = 60;
	digit_ = 10;
	targetScore_ = 0;
	isScore = false;
	
	textureHndle_[0] = TextureManager::Load("numbers/0.png");
	textureHndle_[1] = TextureManager::Load("numbers/1.png");
	textureHndle_[2] = TextureManager::Load("numbers/2.png");
	textureHndle_[3] = TextureManager::Load("numbers/3.png");
	textureHndle_[4] = TextureManager::Load("numbers/4.png");
	textureHndle_[5] = TextureManager::Load("numbers/5.png");
	textureHndle_[6] = TextureManager::Load("numbers/6.png");
	textureHndle_[7] = TextureManager::Load("numbers/7.png");
	textureHndle_[8] = TextureManager::Load("numbers/8.png");
	textureHndle_[9] = TextureManager::Load("numbers/9.png");
	for (int i = 0; i < digit_; i++) {
		number[i] = 0;
		Vector2 createPos = Vector2(position.x+32*(size.x+i), position.y);
		Sprite* newSprite= Sprite::Create(textureHndle_[0], createPos);
		spriteNumbers_.push_back(newSprite);
	}
}


void Score::Update() { 
	if (targetScore_ != 0) {

		if (score_ < targetScore_) {
			score_ += gettingScore_;
			if (score_ >= targetScore_) {
				score_ = (float)targetScore_;
			}
			SelectNumber((int)score_);
		}
	}
}

void Score::Draw() { 
	for (auto it = spriteNumbers_.begin(); it != spriteNumbers_.end();) {
		Sprite* spriteNumber = *it;
		spriteNumber->Draw();
		++it;
	}
}


void Score::SelectNumber(int score) { 
;	int scoreBuff = score; 
	for (int i = digit_; i > 0; i--) {
		int ten = 1;
		for (int j = 1; j <  i; j++) {
			ten *= 10;
		}
		number[digit_ - i] = scoreBuff / ten;
		scoreBuff = scoreBuff % ten;		
	}
	int i = 0;
	for (auto it = spriteNumbers_.begin(); it != spriteNumbers_.end();) {
		Sprite* spriteNumber = *it;
		if (number[i] == 0) {
			spriteNumber->SetTextureHandle(textureHndle_[0]);
		} else if (number[i] == 1) {
			spriteNumber->SetTextureHandle(textureHndle_[1]);
		} else if (number[i] == 2) {
			spriteNumber->SetTextureHandle(textureHndle_[2]);
		} else if (number[i] == 3) {
			spriteNumber->SetTextureHandle(textureHndle_[3]);
		} else if (number[i] == 4) {
			spriteNumber->SetTextureHandle(textureHndle_[4]);
		} else if (number[i] == 5) {
			spriteNumber->SetTextureHandle(textureHndle_[5]);
		} else if (number[i] == 6) {
			spriteNumber->SetTextureHandle(textureHndle_[6]);
		} else if (number[i] == 7) {
			spriteNumber->SetTextureHandle(textureHndle_[7]);
		} else if (number[i] == 8) {
			spriteNumber->SetTextureHandle(textureHndle_[8]);
		} else if (number[i] == 9) {
			spriteNumber->SetTextureHandle(textureHndle_[9]);
		}
		i++;
		++it;
	}

}

void Score::EnterTScore(const int& score) {
	targetScore_ = score;
	score_ = 0;
	gettingScore_ = (float)(score) / time_;
	isScore = true;
}
bool Score::IsActive() {
	return isScore;
}

void Score::Destroy() {
	//for (int i = 0; i < digit_; i++) {
	//	delete spriteNumber[i];
	//}
}
