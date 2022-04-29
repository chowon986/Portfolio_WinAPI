#include "Monster3.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>

// 파란색 나는 몬스터

Monster3::Monster3()
	: Monster()
	, ColMapImage_(nullptr)
	, Level_(nullptr)
{
}

Monster3::~Monster3()
{
}

void Monster3::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* Monster3Renderer = CreateRenderer("monster0.bmp");
	GameEngineImage* Monster3Image = Monster3Renderer->GetImage();
	Monster3Image->CutCount(10, 26);
	Monster3Renderer->CreateAnimation("monster0.bmp", "Monster3Idle", 241, 250, 0.3f, true);
	Monster3Renderer->ChangeAnimation("Monster3Idle");
}


void Monster3::Render()
{
}

void Monster3::Update()
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

bool Monster3::CheckMapCollision()
{
	return true;
}