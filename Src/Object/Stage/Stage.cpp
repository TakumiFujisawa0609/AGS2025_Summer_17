//==============================

// Stage.cpp

//===============================
#include <DxLib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/ResourceManager.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "Stage.h"

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init(Player*player,Camera*camera)
{
	// ゲームシーンの機能を使えるようにする
	
	// プレイヤーの機能を使えるようにする
	player_ = player;
	// カメラの機能を使えるようにする
	camera_ = camera;

	
	// 分割された画像を読み込み
	
	InitStage1();
	

}

void Stage::Update()
{
	
}

void Stage::Draw()
{

	//カメラ座標の取得
	Vector2 cameraPos = camera_->GetCameraPos();

	// マップチップの描画
	for (int y = 0; y < MAP_GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_GROUND_SIZE_X; x++)
		{
			// マップチップ番号を取得
			int chipNo = groundMap_[y][x];

			//マップチップ番号から画像のハンドルIDを取得
			int imgHandle = mapChip_[chipNo];


			//マップチップのワールド座標
			int mapChipWorldPosX = x * CHIP_SIZE_X;
			int mapChipWorldPosY = y * CHIP_SIZE_Y;

			

			//マップチップのスクリーン座標
			//２Dでは「スクリーン座標＝ワールド座標ーカメラ座標」
			int mapChipScreenPosX = mapChipWorldPosX - cameraPos.x;
			int mapChipScreenPosY = mapChipWorldPosY - cameraPos.y;

			
				//DrawRotaGraphF(mapChipScreenPosX, mapChipScreenPosY, 1.0, 0.0, imgHandle, true);

				
				
				DrawGraph(mapChipScreenPosX, mapChipScreenPosY,imgHandle, true);
				
		}
	}
	DrawGraph(CHIP_SIZE_X - cameraPos.x, CHIP_SIZE_X*2, m_, true);
	DrawGraph(CHIP_SIZE_X * 12 - cameraPos.x, CHIP_SIZE_X*2, j_, true);
	DrawGraph(CHIP_SIZE_X * 22 - cameraPos.x, CHIP_SIZE_X*2, d_, true);
	DrawGraph(CHIP_SIZE_X * 27 - cameraPos.x, CHIP_SIZE_X*2, rgb_, true);
	DrawGraph(CHIP_SIZE_X * 32 - cameraPos.x, CHIP_SIZE_X*2, g_, true);
	DrawGraph(CHIP_SIZE_X * 45 - cameraPos.x, CHIP_SIZE_X*2, r_, true);
	DrawGraph(CHIP_SIZE_X * 59 - cameraPos.x, CHIP_SIZE_X*2, b_, true);
	DrawGraph(CHIP_SIZE_X * 37 - cameraPos.x, CHIP_SIZE_X * 2, k_, true);
}

void Stage::Release()
{
	// 読み込んだ画像の解放
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		DeleteGraph(mapChip_[i]);
	}
	DeleteGraph(m_);
	DeleteGraph(j_);
	DeleteGraph(d_);
	DeleteGraph(rgb_);
	DeleteGraph(g_);
	DeleteGraph(r_);
	DeleteGraph(b_);
	DeleteGraph(k_);
}

void Stage::LoadGroundCsvData(void)
{
	// 地上データの初期化
	for (int y = 0; y < MAP_GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_GROUND_SIZE_X; x++)
		{
			groundMap_[y][x] = -1;
		}
	}

	// ファイルの読み込み
	std::ifstream ifs = std::ifstream("Data/Image/Stage/Stage3.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// ファイルを１行ずつ読み込む
	std::string line;
	std::string c;
	int chipNo = 0;
	int x = 0;
	int y = 0;
	while (getline(ifs, line))
	{
		// 1行情報 string を ifstream の仲間に変換
		std::istringstream stream(line);

		// 1文字ずつ読み込み(カンマ区切り)
		x = 0;
		while (getline(stream, c, ','))
		{
			// stringからintに変換
			chipNo = stoi(c);

			// 2次元配列にマップチップ番号を格納
			groundMap_[y][x] = chipNo;

			++x;
		}
		++y;
	}

	stageId_ = STAGE_ID::STAGE1;
}

int Stage::GetChipNo(Vector2 mapPos)
{
	// マップ範囲外であれば判定しない
	if (mapPos.x < 0 || MAP_GROUND_SIZE_X <= mapPos.x
		|| mapPos.y < 0 || MAP_GROUND_SIZE_Y <= mapPos.y) 
	{
		return -1;
	}
	
	return groundMap_[mapPos.y][mapPos.x];
}
int Stage::GetChipNo3(Vector2 mapPos)
{
	// マップ範囲外であれば判定しない
	if (mapPos.x < 0 || MAP3_GROUND_SIZE_X <= mapPos.x
		|| mapPos.y < 0 || MAP3_GROUND_SIZE_Y <= mapPos.y)
	{
		return -1;
	}

	return groundMap3_[mapPos.y][mapPos.x];
}

bool Stage::IsCollisionStage(Vector2 worldPos)
{
	// ワールド座標からマップ座標へ変換する
	Vector2 mapPos = player_->World2MapPos(worldPos);

	// プレイヤーがいる位置のマップチップ番号を取得する
	int chipNo = GetChipNo(mapPos);

	// 障害物のチップ番号と当たっていたら真を返す
	if (chipNo==0|| chipNo == 1|| chipNo == 2||chipNo==3)
	{
		return true;
	}

	return false;
}
bool Stage::IsCollisionStage3(Vector2 worldPos)
{
	// ワールド座標からマップ座標へ変換する
	Vector2 mapPos = player_->World2MapPos(worldPos);

	// プレイヤーがいる位置のマップチップ番号を取得する
	int chipNo = GetChipNo3(mapPos);

	// 障害物のチップ番号と当たっていたら真を返す
	if (chipNo == 0 || chipNo == 1 || chipNo == 2 || chipNo == 3)
	{
		return true;
	}

	return false;
}

void Stage::InitStage1()
{
	ResourceManager& res = ResourceManager::GetInstance();
	mapChip_ = res.Load(ResourceManager::SRC::MAPCHIP).handleIds_;

	b_ = LoadGraph("Data/Image/Stage/B.png");
	g_ = LoadGraph("Data/Image/Stage/G.png");
	j_ = LoadGraph("Data/Image/Stage/Janp.png");
	r_ = LoadGraph("Data/Image/Stage/R.png");
	rgb_ = LoadGraph("Data/Image/Stage/RGB.png");
	m_ = LoadGraph("Data/Image/Stage/Move.png");
	d_ = LoadGraph("Data/Image/Stage/Move+.png");
	k_ = LoadGraph("Data/Image/Stage/k.png");
	// 外部ファイルからマップデータを読み込む
	LoadGroundCsvDataStage1();
	id_ = 1;
}

void Stage::UpdateStage1()
{

}
void Stage::DrawStage1()
{
	//カメラ座標の取得
	Vector2 cameraPos = camera_->GetCameraPos();

	// マップチップの描画
	for (int y = 0; y < MAP_GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_GROUND_SIZE_X; x++)
		{
			// マップチップ番号を取得
			int chipNo = groundMap_[y][x];

			//マップチップ番号から画像のハンドルIDを取得
			int imgHandle = mapChip_[chipNo];


			//マップチップのワールド座標
			int mapChipWorldPosX = x * CHIP_SIZE_X;
			int mapChipWorldPosY = y * CHIP_SIZE_Y;



			//マップチップのスクリーン座標
			//２Dでは「スクリーン座標＝ワールド座標ーカメラ座標」
			int mapChipScreenPosX = mapChipWorldPosX - cameraPos.x;
			int mapChipScreenPosY = mapChipWorldPosY - cameraPos.y;


			//DrawRotaGraphF(mapChipScreenPosX, mapChipScreenPosY, 1.0, 0.0, imgHandle, true);



			DrawGraph(mapChipScreenPosX, mapChipScreenPosY, imgHandle, true);

		}
	}
	DrawGraph(CHIP_SIZE_X - cameraPos.x, CHIP_SIZE_X * 2, m_, true);
	DrawGraph(CHIP_SIZE_X * 12 - cameraPos.x, CHIP_SIZE_X * 2, j_, true);
	DrawGraph(CHIP_SIZE_X * 22 - cameraPos.x, CHIP_SIZE_X * 2, d_, true);
	DrawGraph(CHIP_SIZE_X * 27 - cameraPos.x, CHIP_SIZE_X * 2, rgb_, true);
	DrawGraph(CHIP_SIZE_X * 32 - cameraPos.x, CHIP_SIZE_X * 2, g_, true);
	DrawGraph(CHIP_SIZE_X * 45 - cameraPos.x, CHIP_SIZE_X * 2, r_, true);
	DrawGraph(CHIP_SIZE_X * 59 - cameraPos.x, CHIP_SIZE_X * 2, b_, true);
	DrawGraph(CHIP_SIZE_X * 37 - cameraPos.x, CHIP_SIZE_X * 2, k_, true);
}

void Stage::LoadGroundCsvDataStage1(void)
{
	// 地上データの初期化
	for (int y = 0; y < MAP_GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_GROUND_SIZE_X; x++)
		{
			groundMap_[y][x] = -1;
		}
	}

	// ファイルの読み込み
	std::ifstream ifs = std::ifstream("Data/Image/Stage/Stage3.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// ファイルを１行ずつ読み込む
	std::string line;
	std::string c;
	int chipNo = 0;
	int x = 0;
	int y = 0;
	while (getline(ifs, line))
	{
		// 1行情報 string を ifstream の仲間に変換
		std::istringstream stream(line);

		// 1文字ずつ読み込み(カンマ区切り)
		x = 0;
		while (getline(stream, c, ','))
		{
			// stringからintに変換
			chipNo = stoi(c);

			// 2次元配列にマップチップ番号を格納
			groundMap_[y][x] = chipNo;

			++x;
		}
		++y;
	}
}

void Stage::InitStage2()
{
	// 分割された画像を読み込み
	ResourceManager& res = ResourceManager::GetInstance();
	mapChip_ = res.Load(ResourceManager::SRC::MAPCHIP).handleIds_;
	// 外部ファイルからマップデータを読み込む
	LoadGroundCsvDataStage2();
	id_ = 2;
}

void Stage::UpdateStage2()
{

}
void Stage::DrawStage2()
{
	//カメラ座標の取得
	Vector2 cameraPos = camera_->GetCameraPos();

	// マップチップの描画
	for (int y = 0; y < MAP_GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_GROUND_SIZE_X; x++)
		{
			// マップチップ番号を取得
			int chipNo = groundMap_[y][x];

			//マップチップ番号から画像のハンドルIDを取得
			int imgHandle = mapChip_[chipNo];


			//マップチップのワールド座標
			int mapChipWorldPosX = x * CHIP_SIZE_X;
			int mapChipWorldPosY = y * CHIP_SIZE_Y;



			//マップチップのスクリーン座標
			//２Dでは「スクリーン座標＝ワールド座標ーカメラ座標」
			int mapChipScreenPosX = mapChipWorldPosX - cameraPos.x;
			int mapChipScreenPosY = mapChipWorldPosY - cameraPos.y;


			//DrawRotaGraphF(mapChipScreenPosX, mapChipScreenPosY, 1.0, 0.0, imgHandle, true);



			DrawGraph(mapChipScreenPosX, mapChipScreenPosY, imgHandle, true);

		}
	}
}

void Stage::LoadGroundCsvDataStage2(void)
{
	// 地上データの初期化
	for (int y = 0; y < MAP_GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_GROUND_SIZE_X; x++)
		{
			groundMap_[y][x] = -1;
		}
	}

	// ファイルの読み込み
	std::ifstream ifs = std::ifstream("Data/Image/Stage/Stage4.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// ファイルを１行ずつ読み込む
	std::string line;
	std::string c;
	int chipNo = 0;
	int x = 0;
	int y = 0;
	while (getline(ifs, line))
	{
		// 1行情報 string を ifstream の仲間に変換
		std::istringstream stream(line);

		// 1文字ずつ読み込み(カンマ区切り)
		x = 0;
		while (getline(stream, c, ','))
		{
			// stringからintに変換
			chipNo = stoi(c);

			// 2次元配列にマップチップ番号を格納
			groundMap_[y][x] = chipNo;

			++x;
		}
		++y;
	}
}

void Stage::InitStage3()
{
	stageId_ = STAGE_ID::STAGE3;
	// 分割された画像を読み込み
	ResourceManager& res = ResourceManager::GetInstance();
	mapChip_ = res.Load(ResourceManager::SRC::MAPCHIP).handleIds_;
	// 外部ファイルからマップデータを読み込む
	LoadGroundCsvDataStage3();
	id_ = 3;
}

void Stage::UpdateStage3()
{

}
void Stage::DrawStage3()
{
	//カメラ座標の取得
	Vector2 cameraPos = camera_->GetCameraPos();

	// マップチップの描画
	for (int y = 0; y < MAP3_GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP3_GROUND_SIZE_X; x++)
		{
			// マップチップ番号を取得
			int chipNo = groundMap3_[y][x];

			//マップチップ番号から画像のハンドルIDを取得
			int imgHandle = mapChip_[chipNo];


			//マップチップのワールド座標
			int mapChipWorldPosX = x * CHIP_SIZE_X;
			int mapChipWorldPosY = y * CHIP_SIZE_Y;



			//マップチップのスクリーン座標
			//２Dでは「スクリーン座標＝ワールド座標ーカメラ座標」
			int mapChipScreenPosX = mapChipWorldPosX - cameraPos.x;
			int mapChipScreenPosY = mapChipWorldPosY - cameraPos.y;


			//DrawRotaGraphF(mapChipScreenPosX, mapChipScreenPosY, 1.0, 0.0, imgHandle, true);



			DrawGraph(mapChipScreenPosX, mapChipScreenPosY, imgHandle, true);

		}
	}
}

void Stage::LoadGroundCsvDataStage3(void)
{
	// 地上データの初期化
	for (int y = 0; y < MAP3_GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP3_GROUND_SIZE_X; x++)
		{
			groundMap3_[y][x] = -1;
		}
	}

	// ファイルの読み込み
	std::ifstream ifs = std::ifstream("Data/Image/Stage/Stage5.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// ファイルを１行ずつ読み込む
	std::string line;
	std::string c;
	int chipNo = 0;
	int x = 0;
	int y = 0;
	while (getline(ifs, line))
	{
		// 1行情報 string を ifstream の仲間に変換
		std::istringstream stream(line);

		// 1文字ずつ読み込み(カンマ区切り)
		x = 0;
		while (getline(stream, c, ','))
		{
			// stringからintに変換
			chipNo = stoi(c);

			// 2次元配列にマップチップ番号を格納
			groundMap3_[y][x] = chipNo;

			++x;
		}
		++y;
	}
}
int Stage::GetStageId(void)
{
	

	return id_;
}