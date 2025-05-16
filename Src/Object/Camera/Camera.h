#pragma once
#include"../../Common/Vector2.h"
class Player;
class GameScene;

class Camera
{
public:
	//定数
	//カメラフォーカス
	static const int FOCAS_X = 300;
	static const int FOCAS_Y = 300;

private:
	//変数
	Vector2 cameraPos_;//カメラの位置


	//クラス読み込み
	GameScene* gameScene_;//ゲームシーンのポインタ
	Player* player_;//プレイヤーのポインタ


public:
	//コンストラクタ
	Camera();
	//デストラクタ
	~Camera();
	//初期化
	void Init(Player*player,GameScene*gameScene);
	//更新
	void Update();
	//描画
	void Draw();

	//ゲット・セット
	//カメラの位置を取得
	Vector2 GetCameraPos(void);

};

