#include "Moon.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Moon::Moon()
	: Monster()
	,ColMapImage_(nullptr)
	, Level_(nullptr)
{
}

Moon::~Moon()
{
}

void Moon::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* MoonRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* MoonImage = MoonRenderer->GetImage();
	MoonImage->CutCount(10, 26);
	MoonRenderer->CreateAnimation("monster0.bmp", "MoonIdle",0,1,  0.3f, true);
	MoonRenderer->ChangeAnimation("MoonIdle");
}


void Moon::Render()
{
}

void Moon::Update()
{
	PrevPos_ = GetPosition();

	float4 NewPos;
	NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	NewPos.y = GetPosition().y;
	SetPosition(NewPos);

	if (true == CheckMapCollision())
	{
		SetPosition(PrevPos_);
	}
}

bool Moon::CheckMapCollision()
{
	return true;
}