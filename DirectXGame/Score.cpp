#include "Score.h"
#include <stdio.h>

void Score::Init() {

	//０で初期化
	GameScore_ = 0; 
}

void Score::Update() {}

void Score::Draw() {

	char str[100];
	sprintf_s(str, "SCORE %d", GameScore_);
}
