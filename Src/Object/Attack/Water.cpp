
#include <string>
#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "../Camera/Camera.h"
#include "Water.h"

void Water::Init(Camera*camera)
{
	camera_ = camera;
	//パーティクル画像読み込み
	LoadDivGraph("Data/Image/Attack/EffectCyan.png", MAX_IMG_SIZE, MAX_IMG_SIZE, 1, IMG_SIZE_X, IMG_SIZE_Y, images_, true);
	//粒子の初期化
	InitParticle();
}

void Water::InitParticle(void)
{
	//発射方向のラジアン
	float deg = 0.0f;

	while (deg < 360.0f)
	{
		//パーティクル作成
		WaterEffectInfo particle;
		//デグリー（度数）をラジアンに変換
		float rad = deg * DX_PI_F / 180.0f;

		particle.dirVec.x = cosf(rad);
		particle.dirVec.y = sinf(rad);

		//可変長配列に追加
		particles_.push_back(particle);
		//指定角度分進行する
		deg += SPLIT_ANGLE;
	}
}

void Water::CreateEffect(Vector2 pos)
{
	// パーティクル1つ1つの初期化を行う
	size_t size = particles_.size();
	for (int i = 0; i < size; i++)
	{

		//位置
		particles_[i].pos = pos;
		//どの方向に粒子を拡散させるか方向はInit時に生成済み
		// 大きさの種類（ランダム）
		particles_[i].size = GetRand(MAX_IMG_SIZE - 1);
		//移動速度（ランダム）算出
		//2～8までの間でランダムのスピードを取りたいが
		//GetRandは0から引数 までの値しかとれないため
		//0～6までの値を取った後に2に足して移動速度を計算している
		particles_[i].speed = MIN_SPEED + GetRand(static_cast<int> (MAX_SPEED - MIN_SPEED));
		//生存時間
		particles_[i].life = MAX_LIFE;
		//透過値
		particles_[i].blendRate = 255.0f;
	}
}

void Water::Update(void)
{
	//粒子1つ1つの更新処理
	size_t size = particles_.size();
	for (int i = 0; i < size; i++)
	{
		if (particles_[i].life <= 0.0f)
		{
			continue;
		}
		//生存時間を減らす
		particles_[i].life -= DEC_LIFE;
		// 透明度を減らす
		particles_[i].blendRate -= DEC_ALPHA;
		//座標更新
		//（方向メスピード）を加算して移動
		particles_[i].pos.x += particles_[i].dirVec.x * particles_[i].speed;
		particles_[i].pos.y += particles_[i].dirVec.y * particles_[i].speed;
	}
}

void Water::Draw(void)
{
	size_t size = particles_.size();
	for (int i = 0; i < size; i++)
	{
		if (particles_[i].life <= 0.0f)
		{
			continue;
		}

		//描画モードを変えて透明度を変更する
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(particles_[i].blendRate));

		//描画
		DrawRotaGraphF(particles_[i].pos.x-camera_->GetCameraPos().x, particles_[i].pos.y, 2.0, 0.0, images_[particles_[i].size], true);
		//描画モードをもとに戻す
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Water::Release(void)
{
	for (int i = 0; i < MAX_IMG_SIZE; i++)
	{
		DeleteGraph(images_[i]);
	}

	//可変長配列のクリア
	particles_.clear();
}