#include "Tiktik.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Tiktik::Tiktik()
	: Monster()
	, Level_(nullptr)
	, ColMapImage_(nullptr)
{
}

Tiktik::~Tiktik()
{
}

void Tiktik::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* TiktikRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* TiktikImage = TiktikRenderer->GetImage();
	TiktikImage->CutCount(10, 26);
	TiktikRenderer->CreateAnimation("monster0.bmp", "TiktikIdle", 137, 145, 0.3f, true);
	TiktikRenderer->ChangeAnimation("TiktikIdle");
}


void Tiktik::Render()
{
}

void Tiktik::Update()
{
	//PrevPos_ = GetPosition();

	//float4 NewPos;
	//NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	//NewPos.y = GetPosition().y;
	//SetPosition(NewPos);

	//if (true == CheckMapCollision())
	//{
	//	SetPosition(PrevPos_);
	//}
}

bool Tiktik::CheckMapCollision()
{
	return true;
}