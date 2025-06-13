#pragma once
#include<DxLib.h>
#include "SceneBase.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"




class GameOverScene
{
public:
	// コンストラクタ
	GameOverScene(void);

	// デストラクタ
	~GameOverScene(void);
	// 初期化
	void Init(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);
};

