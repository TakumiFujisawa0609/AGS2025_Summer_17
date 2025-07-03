#include <DxLib.h>
#include "../Camera/Camera.h"
#include "Blast.h"


Blast::Blast(void)
{
	
	for (int i = 0; i < BLAST_ANIM_FRAME; i++)
	{
		blastImgs[i] = -1;
	}
	
	blastPos.x = 0;
	blastPos.y = 0;
	
	isBlast = false;
	
	blastImgAnimCount = 0;

}
Blast::~Blast(void)
{

}
void Blast::Init(Camera*camera)
{
	camera_ = camera;

	LoadDivGraph("Data/Image/Attack/Blast.png", BLAST_ANIM_FRAME, BLAST_DIV_X, BLAST_DIV_Y, BLAST_SIZE, BLAST_SIZE, blastImgs);

	blastSoundHandle = LoadSoundMem("Data/Sound/SE/ShotBomb.mp3");


	
	isBlast = false;
	
	blastImgAnimCount = 0;
	
	blastPos.x = 0.0f;
	blastPos.x = 0.0f;
}

void Blast::Update(void)
{

}
void Blast::Draw(void)
{
	if (isBlast)
	{
		
		blastImgAnimCount++;
		
		if (blastImgAnimCount < 24)
		{
			
			/*DrawBillboard3D(
				blastPos, BLAST_SIZE_X, BLAST_SIZE_Y, BLAST_Z, 0.0f,
				blastImgs[blastImgAnimCount], true);*/
			DrawRotaGraphF(blastPos.x-camera_->GetCameraPos().x, blastPos.y - camera_->GetCameraPos().y, 1.0f, 0.0f, blastImgs[blastImgAnimCount], TRUE);
		}
		else
		{
			
			isBlast = false;
			blastImgAnimCount = 0;
		}
		if (blastImgAnimCount == 1)
		{
			PlaySoundMem(blastSoundHandle, DX_PLAYTYPE_BACK);
		}
		else if (blastImgAnimCount == 23)
		{
			StopSoundMem(blastSoundHandle);
		}
	}
}
void Blast::Release(void)
{
	
	for (int i = 0; i < BLAST_ANIM_FRAME; i++)
	{
		DeleteGraph(blastImgs[i]);
	}

	DeleteSoundMem(blastSoundHandle);
}
bool Blast::GetIsBlast(void)
{
	
	return isBlast;
}
void Blast::SetIsBlast(bool is)
{
	
	isBlast = is;
}
Vector2 Blast::GetBlastPos(void)
{
	
	return blastPos;
}
void Blast::SetBlastPos(Vector2 pos)
{
	
	blastPos = pos;
}
