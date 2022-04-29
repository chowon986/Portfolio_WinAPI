#include "Monster2.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>

// 파란색 나는 몬스터

Monster2::Monster2()
	: Monster()
	, ColMapImage_(nullptr)
	, Level_(nullptr)
{
}

Monster2::~Monster2()
{
}

void Monster2::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* Monster2Renderer = CreateRenderer("monster0.bmp");
	GameEngineImage* Monster2Image = Monster2Renderer->GetImage();
	Monster2Image->CutCount(10, 26);
	Monster2Renderer->CreateAnimation("monster0.bmp", "Monster2Idle", 241, 250, 0.3f, true);
	Monster2Renderer->ChangeAnimation("Monster2Idle");
}


void Monster2::Render()
{
}

void Monster2::Update()
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

bool Monster2::CheckMapCollision()
{
	return true;
}