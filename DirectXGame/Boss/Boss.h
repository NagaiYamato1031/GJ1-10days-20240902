#pragma once

#include <memory>
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Utility/Mymath.h>
#include <BulletManager/BulletManager.h>
#include <Collider/CollisionManager.h>
#include "DisplayHp.h"

// 前方宣言
class Player;

/// <summary>
/// ボス
/// 後で仮想化するかもしれない
/// </summary>
class Boss {
public: //** コンストラクタ **//

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Boss() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Boss() = default;

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
	/// フラグ取得
	/// </summary>
	bool IsActive() const { return isActive_; }
	/// <summary>
	/// フラグ取得
	/// </summary>
	bool IsDead() const { return isDead_; }
	/// <summary>
	/// フェーズを取得
	/// </summary>
	int GetPhase() const { return phase_; }
	WorldTransform* GetTransform() { return &transform_; }

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	/// <param name="p"></param>
	void SetPlayer(Player* p) { player_ = p; }


	/// <summary>
	/// デバッグ表示
	/// </summary>
	void DebugWindow();

private: //** プライベート変数 **//

	// ステージにあたる距離
	float kPaddingCenter_ = 45.0f;

	// 3D モデル
	std::unique_ptr<Model> model_;

	// ワールド座標
	WorldTransform transform_;

	// 弾管理
	BulletManager bulletManager_;

	// プレイヤーを参照する
	Player* player_ = nullptr;

	//Hp出す奴
	DisplayHp displayHp_;

	//エネミー体力
	int hp_ = 40;

	// 移行フレーム
	int transitionFrame_ = 0;
	// 色を保存
	std::vector<Vector4> colors_;
	// 色の添え字
	int colorIndex_ = 0;
	// オブジェクトの色を変えるもの
	ObjectColor objectColor_;

	//エネミー攻撃遷移フレーム
	int AttackFrame01 = 80;
	int AttackFrame02 = 180;
	int AttackFrame03 = 360;
	int AttackFrame04 = 360;

#ifdef _DEBUG

	// 最初に何フレームか表示するための変数
	int DebugFrame01 = 180;
	int DebugFrame02 = 180;
	int DebugFrame03 = 360;

#endif // _DEBUG

	// クラスが稼働状態か
	bool isActive_ = true;

	//エネミー死亡判定
	bool isDead_ = false;

	//フェーズ一覧
	enum Phase {
		p0,
		p1,
		p2,
		p3,
		p4,

		transition,
	};

	//現在の行動
	Phase phase_ = Phase::p0;
	// 次の行動
	Phase nextPhase_ = Phase::p1;

	// 球の当たり判定
	ACJPN::Math::Sphere colSphere_;
	std::shared_ptr<ACJPN::Collider::ShapeCollider<ACJPN::Math::Sphere>> collider_;

	// アニメーション用の時間
	int animationFrame_ = 0;


private: //** プライベート関数 **//

	/// <summary>
	/// 当たり判定を初期化
	/// </summary>
	void InitCollision();

	/// <summary>
	/// 弾の共通ヒット時処理
	/// <param>打ち返せる弾には使わない</param>
	/// </summary>
	/// <param name="mask">マスク</param>
	/// <param name="data">データ</param>
	void EnterBulletFunction(int mask, IBullet* data);

	/// <summary>
	/// まっすぐ飛ばして波も出る弾を生成する
	/// </summary>
	void CreateBulletEffective(float speed = 1.0f);
	/// <summary>
	/// ホーミングして波を発生させる弾を生成する
	/// </summary>
	/// <param name="speed">速度 : 0.5f 以下がいい感じ</param>
	void CreateBulletHoming(float speed = 0.5f);
	/// <summary>
	/// バウンドして波を発生させる弾を生成する
	/// </summary>
	/// <param name="speed">速度 : 1.0f</param>
	void CreateBulletBound(float speed = 1.0f);
	/// <summary>
	/// バウンドして波を発生させる弾 2 Way で生成する
	/// </summary>
	/// <param name="speed">速度 : 0.45f</param>
	void CreateBulletBound2Way(float theta, float speed = 0.45f, int hp = 3);
	/// <summary>
	/// 弾を角度分開いて、二方向に撃ち出す
	/// </summary>
	void CreateBulletEffective2Way(float theta, float speed = 1.0f);
	/// <summary>
	/// 角度から波を生成する
	/// </summary>
	void CreateBulletWave(float theta, float power);

	/// <summary>
	/// HP を減らす
	/// </summary>
	void DecreaseHP(int damage);

	//エネミー攻撃手段
	void EnemyAttack_1(); //自機狙い

	void EnemyAttack_2(); //自機周辺狙い

	void EnemyAttack_3(); //波発生

	void EnemyAttack_4(); // 自機 + 周辺

	void EnemyAttack_5(); // 真横バウンド x2

	//エネミーフェーズ
	void Phase_0(); //第零段階

	void Phase_1(); //第一段階

	void Phase_2(); //第二段階

	void Phase_3(); //第三段階

	void Phase_4(); //死亡段階

	/// <summary>
	/// 状態を切り替えているフェーズ
	/// </summary>
	void Phase_Transition();

	/// <summary>
	/// 死んでいる時に更新する
	/// アニメーションとかをごり押ししたい
	/// </summary>
	void UpdateDeath();
};