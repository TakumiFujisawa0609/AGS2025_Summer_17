//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>

class Player;
class Enemy;

class GameScene : public SceneBase
{

public:
	
	
private:

	// プレイヤー
	Player* player_;
	// プレイヤー
	Enemy* enemy_;

public:
	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

};
