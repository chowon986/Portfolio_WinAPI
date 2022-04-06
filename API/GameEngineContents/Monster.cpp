#include "Monster.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

Monster::Monster()
	: HP_(1)
	, Pos_(0, 0)
	, Speed_(10)
{
}

Monster::~Monster()
{
}

void Monster::Walk()
{
}

void Monster::Jump()
{
}

bool Monster::IsDie()
{
	return false;
}

void Monster::attack()
{
}

void Monster::GetPos(float4 _Pos)
{
}

void Monster::Start()
{
	//WaddlediRenderer_ = CreateRenderer("monster0.bmp");
	//GameEngineImage* WaddlediImage = WaddlediRenderer_->GetImage();
	//WaddlediImage->CutCount(10, 26);
	//WaddlediRenderer_->CreateAnimation("monster0.bmp", "WaddlediIdel", 7, 13, 0.3f, true);
}

void Monster::Update()
{
	//WaddlediRenderer_->ChangeAnimation("WaddlediIdel");
}

void Monster::Render()
{
}
