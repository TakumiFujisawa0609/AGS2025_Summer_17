#pragma once
#include "SceneBase.h"
class ClearScene : public SceneBase
{

public:
	// コンストラクタ
	ClearScene(void) = default;
	// デストラクタ
	~ClearScene(void) = default;
	// 初期化
	void Init(void);
	// 更新
	void Update(void);
	// 描画
	void Draw(void);
	
private:

	int Img_; // 背景画像

	int SoundImg_; // 効果音ハンドル

	int clearImg_; // クリア画像

	int  blinkCycle; // 点滅周期

	float frameCount;
	int successSound;; // タイトルBGMのハンドル

};

