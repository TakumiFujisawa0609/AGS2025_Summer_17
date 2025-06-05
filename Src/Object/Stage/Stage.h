#pragma once
#include "../../Common/Vector2.h"
class Player;
class GameScene;
class Camera;

class Stage
{
public:

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

	Stage();
	~Stage();

	void Init(GameScene* scene,Player*player,Camera*camera);
	void Update();
	void Draw();
	void Release();



	// 外部ファイルから地上のステージデータを読み込む
	void LoadGroundCsvData(void);

	// マップチップ番号を取得する
	int GetChipNo(Vector2 mapPos);

	bool IsCollisionStage(Vector2 worldPos);
	

	

	




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

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;

	// プレイヤーのポインタ変数
	Player* player_;

	// カメラのポインタ変数
	Camera* camera_;
};

