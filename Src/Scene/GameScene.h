//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>

class Player;
class StageManager;
class EnemyManager;
class EnemyFire;
class EnemyPlant;
//class EnemyWater;
class EnemyAttackF;
class EnemyAttackP;
//class EnemyAttackW;
class Stage;
class Camera;
class Wall;
class Blast;
class Plants;
class PlayerUi;
class Water;

class GameScene : public SceneBase
{

public:
	//画面揺れの感覚
	static constexpr int SCREEN_SHAKE_INTERVAL_COUNT = 5;
	// 画面の揺れ幅
	static constexpr int SHAKE_WIDTH = 5;
	
private:

	// プレイヤー
	Player* player_;
	// エネミー
	EnemyManager* enemyManager_;
	EnemyFire* enemyFire_;
	EnemyPlant* enemyPlant_;
	//EnemyWater* enemyWater_;
	EnemyAttackF* enemyAttackF_;
	EnemyAttackP* enemyAttackP_;
	//EnemyAttackW* enemyAttackW_;
	// ステージ
	Stage* stage_;
	// カメラ
	Camera* camera_;
	// 壁
	Wall* wall_;
	//攻撃
	//爆発
	Blast* blast_;
	//植物
	Plants* plants_;
	//水
	Water* water_;

	StageManager* stageManager_;
	PlayerUi* playerUi_;


	//背景
	int backImg_;


	//一時的な描画領域
	int tmpScreen_;
	//画面揺れの感覚
	int screenShakeInterevalCount_;
	//画面の揺れ
	int screenShakePos_;

	//ヒットストップ
	int hitStopCnt_;

public:

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void);

	//ゲット・セット
	int GetHitStop();
	void SetHitStop(int cnt);
};
