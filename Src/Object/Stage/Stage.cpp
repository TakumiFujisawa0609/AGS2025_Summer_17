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
#include "../../Scene/GameScene.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "Stage.h"

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init(GameScene* scene,Player*player,Camera*camera)
{
	// ゲームシーンの機能を使えるようにする
	gameScene_ = scene;
	// プレイヤーの機能を使えるようにする
	player_ = player;
	// カメラの機能を使えるようにする
	camera_ = camera;

	// 分割された画像を読み込み
	ResourceManager& res = ResourceManager::GetInstance();
	mapChip_ = res.Load(ResourceManager::SRC::MAPCHIP).handleIds_;

	

	// 外部ファイルからマップデータを読み込む
	LoadGroundCsvData();
}

void Stage::Update()
{
	//
}

void Stage::Draw()
{
	// マップチップの描画
	for (int y = 0; y < MAP_GROUND_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_GROUND_SIZE_X; x++)
		{
			// マップチップ番号を取得
			int chipNo = groundMap_[y][x];
			//マップチップのワールド座標
			int mapChipWorldPosX = x * CHIP_SIZE_X;
			int mapChipWorldPosY = y * CHIP_SIZE_Y;

			//カメラ座標の取得
			Vector2 cameraPos = camera_->GetCameraPos();

			//マップチップ番号から画像のハンドルIDを取得
			int imgHandle = mapChip_[chipNo];


			//マップチップのスクリーン座標
			//２Dでは「スクリーン座標＝ワールド座標ーカメラ座標」
			int mapChipScreenPosX = mapChipWorldPosX -cameraPos.x;
			int mapChipScreenPosY = mapChipWorldPosY ;

			// マップチップ番号が-1でなければ描画する
			if (chipNo != -1)
			{
				
				DrawRotaGraphF(mapChipScreenPosX, mapChipScreenPosY, 1.0, 0.0, imgHandle, true);

				
				
				//DrawGraph(mapChipScreenPosX, mapChipScreenPosY,imgHandle, true);
			}
		}
	}

}

void Stage::Release()
{
	// 読み込んだ画像の解放
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		DeleteGraph(mapChip_[i]);
	}
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
	std::ifstream ifs = std::ifstream("Data/Image/Stage/Stage2.csv");
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

int Stage::GetChipNo(Vector2 mapPos)
{
	// マップ範囲外であれば判定しない
	if (mapPos.x < 0 || MAP_GROUND_SIZE_X <= mapPos.x
		|| mapPos.y < 0 || MAP_GROUND_SIZE_Y <= mapPos.y) {
		return -1;
	}

	return groundMap_[mapPos.y][mapPos.x];
}

bool Stage::IsCollisionStage(Vector2 worldPos)
{
	// ワールド座標からマップ座標へ変換する
	Vector2 mapPos = player_->World2MapPos(worldPos);

	// プレイヤーがいる位置のマップチップ番号を取得する
	int chipNo = GetChipNo(mapPos);

	// 障害物のチップ番号と当たっていたら真を返す
	if (chipNo==0|| chipNo == 1|| chipNo == 2)
	{
		return true;
	}

	return false;
}

