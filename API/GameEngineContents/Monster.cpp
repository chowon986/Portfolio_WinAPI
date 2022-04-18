#include "Monster.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

Monster::Monster()
	: Pos_(0, 0)
	, Speed_(10)
	, MonsterClass_(MonsterClass::DEFAULT)
{
	SetHP(1);
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
	if (GetHP() <= 0)
	{
		return true;
	}
	else return false;
}

void Monster::attack()
{
}

void Monster::GetPos(float4 _Pos)
{
}

void Monster::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();
}

void Monster::Update()
{

}

void Monster::Render()
{
}

void Monster::Die()
{
	if (true == IsDie())
	{
		Death();
	}
}
