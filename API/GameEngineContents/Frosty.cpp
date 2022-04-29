#include "Frosty.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Frosty::Frosty()
	: Monster()
	, ColMapImage_(nullptr)
	, Level_(nullptr)
{
	SetMonsterClass(MonsterClass::ICE);
}

Frosty::~Frosty()
{
}

void Frosty::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* FrostyRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* FrostyImage = FrostyRenderer->GetImage();
	FrostyImage->CutCount(10, 26);
	FrostyRenderer->CreateAnimation("monster0.bmp", "FrostyIdle", 160, 164, 0.3f, true);
	FrostyRenderer->ChangeAnimation("FrostyIdle");

}


void Frosty::Render()
{
}

void Frosty::Update()
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

bool Frosty::CheckMapCollision()
{
	return true;
}