#pragma once

#include"../../Common/Vector2.h"
class Camera;

class Blast
{
public:
	//定数
	// 爆発のアニメーションのフレーム数
	static constexpr int BLAST_ANIM_FRAME = 24;
	// 爆発分割サイズ
	static constexpr int BLAST_SIZE = 96;
	// 横切り取り枚数
	static constexpr int BLAST_DIV_X = 6;
	// 縦切り取り枚数
	static constexpr int BLAST_DIV_Y = 4;
	// 爆発の大きさ
	static constexpr float BLAST_SIZE_X = 0.5f;
	static constexpr float BLAST_SIZE_Y = 0.5f;
	// 爆発のZ座標
	static constexpr float BLAST_Z = 300.0f;

private:
	//変数
	// 爆発画像のロード
	int blastImgs[24];

	// 爆発判定(trueが爆発)
	bool isBlast;
	// 爆発アニメーション用のカウンタ
	int blastImgAnimCount;
	// 爆発座標
	 Vector2 blastPos;

	 Camera* camera_;
public:
	Blast(void);
	~Blast(void);
	void Init(Camera*camera);
	void Update(void);
	void Draw(void);
	void Release(void);
	bool GetIsBlast(void);
	void SetIsBlast(bool is);
	Vector2 GetBlastPos(void);
	void SetBlastPos(Vector2 pos);

};



