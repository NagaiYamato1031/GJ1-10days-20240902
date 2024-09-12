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
	bool IsDead() const { return isDead_; }

	void SetPlayer(Player* p) { player_ = p; }

	/// <summary>
	/// デバッグ表示
	/// </summary>
	void DebugWindow();

private: //** プライベート変数 **//

	// 3D モデル
	std::unique_ptr<Model> model_;

	// ワールド座標
	WorldTransform transform_;

	// 弾管理
	BulletManager bulletManager_;

	// プレイヤーを参照する
	Player* player_ = nullptr;

	//エネミー体力
	int hp_ = 40;
	// 大玉を打ち返す時のフラグ
	bool endTransition_ = false;

	//エネミー攻撃遷移フレーム
	int AttackFrame01 = 80;
	int AttackFrame02 = 180;
	int AttackFrame03 = 360;

#ifdef _DEBUG

	// 最初に何フレームか表示するための変数
	int DebugFrame01 = 180;
	int DebugFrame02 = 180;
	int DebugFrame03 = 360;

#endif // _DEBUG

	// 中心からの回転角
	float theta_ = 0.0f;

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
	/// まっすぐ飛ばして波を波も出る弾を生成する
	/// </summary>
	void CreateBulletSimple(float speed = 1.0f);
	/// <summary>
	/// 少し外れたところに波を発生させる弾を生成する
	/// </summary>
	/// <param name="speed">速度 : 1.0f 以下がいい感じ</param>
	void CreateBulletEffective(float speed = 0.7f);
	/// <summary>
	/// 弾を角度分開いて、二方向に撃ち出す
	/// </summary>
	/// <param name="speed"></param>
	void CreateBulletEffective2Way(float theta, float speed = 1.0f);
	/// <summary>
	/// 角度から波を生成する
	/// </summary>
	void CreateBulletWave(float theta, float power);

	/// <summary>
	/// HP を減らす
	/// </summary>
	void DecreasHP(int damage);

	//エネミー攻撃手段
	void EnemyAttack_1(); //自機狙い

	void EnemyAttack_2(); //自機周辺狙い

	void EnemyAttack_3(); //波発生

	void EnemyAttack_4(); // 自機 + 周辺

	//エネミーフェーズ
	void Phase_0(); //第零段階

	void Phase_1(); //第一段階

	void Phase_2(); //第二段階

	void Phase_3(); //第三段階

	void Phase_4(); //死亡段階

	/// <summary>
	/// 大玉を撃っているフェーズ
	/// </summary>
	void Phase_Transition();
};