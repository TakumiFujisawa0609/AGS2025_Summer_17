//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>

class Player;
class Stage;
class Camera;

class GameScene : public SceneBase
{

public:
	
	
private:

	// プレイヤー
	Player* player_;
	// ステージ
	Stage* stage_;
	// カメラ
	Camera* camera_;


public:
	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

};
