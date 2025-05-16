//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>

class Player;
<<<<<<< HEAD
class Enemy;
=======
class Stage;
<<<<<<< HEAD
>>>>>>> 0eb14c3af250a85def310bbf5bc90111ef407bd3
=======
class Camera;
>>>>>>> ado_Player

class GameScene : public SceneBase
{

public:
	
	
private:

	// プレイヤー
	Player* player_;
<<<<<<< HEAD
	// プレイヤー
	Enemy* enemy_;
=======
	// ステージ
	Stage* stage_;
	// カメラ
	Camera* camera_;

>>>>>>> 0eb14c3af250a85def310bbf5bc90111ef407bd3

public:
	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

};
