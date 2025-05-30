#pragma once

#include "SceneBase.h"
#include"../Manager/ResourceManager.h"


class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	
	
private:

	int img_;  // 画像ハンドル
	
	int  blinkCycle; // 点滅周期

	float frameCount;

};
