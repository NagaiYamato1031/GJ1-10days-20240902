#include "Score.h"
#include <stdio.h>

void Score::Init() {

	//０で初期化
	GameScore_ = 0; 
}

void Score::Update() {}

void Score::Draw() {

	char str[100];

	for (int i = 0; i < GameScore_; i++) {
		 
		sprintf_s(str, "GameScore   %d", GameScore_);
	}
}
