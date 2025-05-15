#pragma once


class Player
{
public:
	//定数


private:
	//変数
	int* img_;
	Vector2 pos_;


public:
	
	//プロトタイプ宣言
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();

	//関数
	void Move();

};

