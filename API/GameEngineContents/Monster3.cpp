#include "Monster3.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>

// 파란색 나는 몬스터

Monster3::Monster3()
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
	if (nullptr != ColMapImage_)
	{
		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y))
		{
			return true;
		}

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y))
		{
			return true;
		}

		// 왼쪽, 오른쪽, 위쪽으로 이동 금지
		if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50) 
		{
			return true;
		}
	}
}