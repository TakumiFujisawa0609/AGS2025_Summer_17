#pragma once
#include "../../Common/Vector2.h"
class Player;
class Camera;

class Stage
{
public:

	enum class STAGE_ID
	{
		NONE,
		STAGE1,
		STAGE2,
		STAGE3,

	};



	// ステージの分割画像
	static constexpr int NUM_MAP_CHIPS_X = 13;	// マップチップ横画像
	static constexpr int NUM_MAP_CHIPS_Y = 1;	// マップチップ縦枚数
	static constexpr int NUM_MAP_CHIPS = NUM_MAP_CHIPS_X * NUM_MAP_CHIPS_Y;	// 合計

	// マップチップのサイズ
	static constexpr int CHIP_SIZE_X = 32*2;	// 横
	static constexpr int CHIP_SIZE_Y = 32*2;	// 縦
	static constexpr int CHIP_HALF_SIZE_X = CHIP_SIZE_X / 2;	// 横半分
	static constexpr int CHIP_HALF_SIZE_Y = CHIP_SIZE_Y / 2;	// 縦半分

	// 地上マップのサイズ(縦枚数×横枚数)
	static constexpr int MAP_GROUND_SIZE_X = 100;
	static constexpr int MAP_GROUND_SIZE_Y = 12;

	// 地上マップのサイズ(縦枚数×横枚数)
	static constexpr int MAP3_GROUND_SIZE_X = 100;
	static constexpr int MAP3_GROUND_SIZE_Y = 24;
private:
	

	int r_;
	int g_;
	int b_;
	int rgb_;
	int j_;
	int m_;
	int d_;
	int k_;



	// マップ画像
	int* mapChip_;

	// 地上マップ
	int groundMap_[MAP_GROUND_SIZE_Y][MAP_GROUND_SIZE_X];
	int groundMap3_[MAP3_GROUND_SIZE_Y][MAP3_GROUND_SIZE_X];

	// プレイヤーのポインタ変数
	Player* player_;

	// カメラのポインタ変数
	Camera* camera_;
	STAGE_ID stageId_;

	int id_;

public:

	Stage();
	~Stage();

	void Init(Player* player, Camera* camera);
	void Update();
	void Draw();
	void Release();

	void InitStage1();
	void UpdateStage1();
	void DrawStage1();
	void LoadGroundCsvDataStage1(void);

	void InitStage2();
	void UpdateStage2();
	void DrawStage2();
	void LoadGroundCsvDataStage2(void);

	void InitStage3();
	void UpdateStage3();
	void DrawStage3();
	void LoadGroundCsvDataStage3(void);



	// 外部ファイルから地上のステージデータを読み込む
	void LoadGroundCsvData(void);

	// マップチップ番号を取得する
	int GetChipNo(Vector2 mapPos);
	int GetChipNo3(Vector2 mapPos);
	bool IsCollisionStage(Vector2 worldPos);
	bool IsCollisionStage3(Vector2 worldPos);

	int  GetStageId(void);

};

