#include "Storo.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Storo::Storo()
	: Monster() // need to chk
	, Level_(nullptr)
	, ColMapImage_(nullptr)
{
}

Storo::~Storo()
{
}

void Storo::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* StoroRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* StoroImage = StoroRenderer->GetImage();
	StoroImage->CutCount(10, 26);
	StoroRenderer->CreateAnimation("monster0.bmp", "StoroIdle", 108, 111, 0.3f, true);
	StoroRenderer->ChangeAnimation("StoroIdle");
}


void Storo::Render()
{
}

void Storo::Update()
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

bool Storo::CheckMapCollision()
{
	return true;
}