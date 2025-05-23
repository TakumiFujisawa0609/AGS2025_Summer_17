#include <math.h>
#include <DxLib.h>
#include"FpsControll.h"

//定数宣言
static const int N = 60;         //平均をとるサンプル数
static const int FPS = 60;       //設定下fps

//変数宣言
static int _mStartTime;           //測定開始時刻
static int _mConut;               //カウンタ
static float _mFps;               //fps

//初期化
void FpsControll_Initialize()
{
	_mStartTime = GetNowCount();
	_mConut = 0;
	_mFps = 0;
}


//FPS制御
bool FpsControll_Update()
{
	if (_mConut == 0)
	{
		_mStartTime = GetNowCount();
	}

	if (_mConut == N)
	{
		int t = GetNowCount();
		_mFps = 1000.f / ((t - _mStartTime) / (float)N);
		_mConut = 0;
		_mStartTime = t;
	}
	_mConut++;

	return true;
}

//FPS表示
void FpsControll_Draw()
{
	DrawFormatString(770, 670, GetColor(255, 255, 255), "%.1f", _mFps);
}

//時間測定
void FpsControll_Wait()
{
	int _tookTime = GetNowCount() - _mStartTime;         //かかった時間
	int _waitTime = _mConut * 1000 / FPS - _tookTime;    //待つべき時間

	if (_waitTime > 0)
	{
		Sleep(_waitTime);
	}
}
