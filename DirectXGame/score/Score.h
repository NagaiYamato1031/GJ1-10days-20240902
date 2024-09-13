#pragma once

#include <Utility/Mymath.h>
#include <WorldTransform.h>
#include <Sprite.h>
#include "list"

class Score {
public: /*コンストラクタ*/
	Score() = default;
	~Score() = default;

public:/*パブリック関数*/
	void Init(const Vector2& position); // 初期化
	void Update();//スコア計算風演出
	void Draw();//スコアの描画
	void SelectNumber(int score);//テクスチャを適応させる
	void EnterTScore(const int& score);//スコアやらを入れる
	void Destroy();
	bool IsActive();

private: /*メンバ変数*/
	
	int time_;//スコア計算演出をする時間
	int targetScore_;//取得したスコア
	float score_;//描画中のスコア
	float gettingScore_;//scoreに加算していく量
	int digit_;//スコアの桁数
	int number[5] = {};
	std::list<Sprite*> spriteNumbers_;
	Vector2 size;
	bool isScore = false;
	
	//数字用のテクスチャ―ハンドル
	uint32_t textureHndle_[10] = {};
	//std::unique_ptr<Sprite>
};
