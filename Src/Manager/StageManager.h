#pragma once

class Fader;
class Player;
class EnemyManager;
class EnemyFire;
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
	EnemyFire* enemyFire_;
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

	STAGE_TYPE nextStageType;

	
	std::unique_ptr<Fader> fader_;

	int back3Img_;
	//背景
	int backImg_;

	int backGrassImg_;

	int backSkyImg_;

	int Img_;

	int doaImg_[3];

	bool isChange_;

	int changeCnt_;

	int animCnt_;

	int skuroru_;

	// シーン遷移中判定
	bool isSceneChanging_;


	// フェード
	void Fade(void);

	int BackSoundHandle_; // 背景BGMのハンドル

	int BackSoundHandle3_; // 3ステ背景BGMのハンドル

public:

	StageManager();
	~StageManager();
	void Init(Player* player_, EnemyManager* enemyManager_, EnemyFire* enemyFire, Stage* stage_, Camera* camera_, Wall* wall_, Blast* blast_, Plants* plants_, Water* water_);
	void Update();
	void Draw();
	void Update1();
	void Draw1();
	void Update2();
	void Draw2();
	void Update3();
	void Draw3();
	void ChangeStage(STAGE_TYPE id);
	void DoChangeStage(STAGE_TYPE id);


	
};

