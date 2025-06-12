//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>

class Player;
class StageManager;
class EnemyManager;
class Stage;
class Camera;
class Wall;
class Blast;
class Plants;
class Water;

class GameScene : public SceneBase
{

public:
	
	
private:

	// プレイヤー
	Player* player_;
	// エネミー
	EnemyManager* enemyManager_;
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

	//背景
	int backImg_;

	

public:

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void);
};
