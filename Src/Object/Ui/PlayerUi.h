#pragma once
#include "../../Common/Vector2.h"

class Playr;

class PlayerUi
{
public:

	static constexpr int HP_UI_SIZE_X = 64 * 4;
	static constexpr int HP_UI_SIZE_Y = 64 * 2;
	static constexpr int HP_UI_HALFSIZE_X = 64 * 2;
	static constexpr int HP_UI_HALFSIZE_Y = 64;


private:

	int hpUi_;
	Vector2 uiPos_;
	Vector2 hpPos_;
	Vector2 mpPos_;
	

	Player* player_;

public:
	PlayerUi();
	~PlayerUi();

	void Init(Player*player);
	void Update();
	void Draw();

};

