#pragma once
#include"../../Common/Vector2.h"
class Player;

class Camera
{
public:
	//定数

private:
	//変数
	Vector2 cameraPos_;


	//クラス読み込み
	Player* player_;//プレイヤーのポインタ


public:
	//コンストラクタ
	Camera();
	//デストラクタ
	~Camera();
	//初期化
	void Init(Player*player);
	//更新
	void Update();
	//描画
	void Draw();

	//ゲット・セット
	//カメラの位置を取得
	Vector2 GetCameraPos(void);

};

