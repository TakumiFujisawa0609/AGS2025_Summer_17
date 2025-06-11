#pragma once


class Player;
class EnemyManager;
class Stage;
class Camera;
class Wall;
class Blast;
class Plants;
class Water;

class StageManager
{
public:
	enum class STAGE_TYPE
	{
		NONE,
		STAGE1,
		STAGE2,
		STAGE3,

	};


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

	STAGE_TYPE stageType;

public:

	StageManager();
	~StageManager();
	void Init(Player* player_,	EnemyManager* enemyManager_,Stage* stage_,Camera* camera_,Wall* wall_,Blast* blast_,	Plants* plants_,Water* water_);
	void Update();
	void Draw();

	void ChangeStage(STAGE_TYPE id);


};

