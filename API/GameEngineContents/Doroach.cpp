#include "Doroach.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Doroach::Doroach()
	: Monster()
	, ColMapImage_(nullptr)
	, Level_(nullptr)
{
}

Doroach::~Doroach()
{
}

void Doroach::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* DoroachRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* DoroachImage = DoroachRenderer->GetImage();
	DoroachImage->CutCount(10, 26);
	DoroachRenderer->CreateAnimation("monster0.bmp", "DoroachIdle", 160, 164, 0.3f, true);
	DoroachRenderer->ChangeAnimation("DoroachIdle");

}


void Doroach::Render()
{
}

void Doroach::Update()
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

bool Doroach::CheckMapCollision()
{
	return true;
}