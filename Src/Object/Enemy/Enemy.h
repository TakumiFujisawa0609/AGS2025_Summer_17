#pragma once

class Enemy
{
public:

	static constexpr VECTOR INIT_POS = { 0.0f, 32.0f, 0.0f };
	static constexpr float MOVE_SPEED = 3.0f;

	//プロトタイプ宣言
	void Init();
	void Update();
	void Draw();

	//関数
	void Move();
	void Attack();

private:

	// 座標
	VECTOR pos_;
	// 画像の読み込み
	int img_;
	// 攻撃のクールダウンカウント
	int attackCnt_;
	// 生存判定
	bool isAlive_;
	// 攻撃中判定
	bool isAttack_;

};