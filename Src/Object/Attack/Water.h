#pragma once
#include<vector>
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
class Camera;

class Water
{
public:
	//画像の種類（粒子の大きさが異なる）
	static constexpr int MAX_IMG_SIZE = 6;

	//画像サイズ横
	static constexpr int IMG_SIZE_X = 16;

	//画像サイズ
	static constexpr int IMG_SIZE_Y = 16;

	//粒子拡散（分割）角度
	static constexpr float SPLIT_ANGLE = 30.0f;

	//粒子の生存時間
	static constexpr float MAX_LIFE = 0.2f;

	//生存時間減少値
	static constexpr float DEC_LIFE = 0.01f;

	//移動速度（最小）
	static constexpr float MIN_SPEED = 2.0f;

	//移動速度（最大）
	static constexpr float MAX_SPEED = 8.0f;

	//最大透過知
	static constexpr float MAX_ALPHA = 255.0f;

	//透過減少値
	static constexpr float DEC_ALPHA = 8.0f;

	//粒子の1つずつの情報
	struct WaterEffectInfo
	{
		Vector2 pos;
		Vector2F dirVec;
		int size = 0;
		float speed = 0.0f;
		float life = 0.0f;
		float blendRate = 0.0f;
	};

	void Init(Camera*camera);
	void Update(void);
	void Draw(void);
	void Release(void);

	//指定座標にエフェクトを生成する
	void CreateEffect(Vector2 pos);


private:

	Camera* camera_;

	//画像
	int images_[MAX_IMG_SIZE];

	int WaterSoundHandle;

	//粒子
	std::vector<WaterEffectInfo> particles_;
	//粒子の初期化
	void InitParticle(void);
};

