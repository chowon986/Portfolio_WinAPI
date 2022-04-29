#include "Sword.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Sword::Sword()
	: Monster()
	, ColMapImage_(nullptr)
	, Level_(nullptr)
{
	SetMonsterClass(MonsterClass::SWORD);
}

Sword::~Sword()
{
}

void Sword::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* SwordRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* SwordImage = SwordRenderer->GetImage();
	SwordImage->CutCount(10, 26);
	SwordRenderer->CreateAnimation("monster0.bmp", "SwordIdle", 181, 186, 0.3f, true);
	SwordRenderer->ChangeAnimation("SwordIdle");
}


void Sword::Render()
{
}

void Sword::Update()
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

bool Sword::CheckMapCollision()
{
	return true;
}