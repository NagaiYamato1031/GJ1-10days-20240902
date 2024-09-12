#pragma once

class Score {

public:

	/// <summary>
	/// 
	/// </summary>
	void Init();

	/// <summary>
	/// 
	/// </summary>
	void Update();

	/// <summary>
	/// 
	/// </summary>
	void Draw();

private:
	
	//スコア変数
	int GameScore_ = 0;

private:

	//Getter・Setter
	int GetGameScore() { return GameScore_; }
	void SetGameScore(int Score) { GameScore_ = Score; };

};
