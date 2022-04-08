#include "Monster1.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Monster1::Monster1()
{
}

Monster1::~Monster1()
{
}

void Monster1::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* Monster1Renderer = CreateRenderer("monster0.bmp");
	GameEngineImage* Monster1Image = Monster1Renderer->GetImage();
	Monster1Image->CutCount(10, 26);
	Monster1Renderer->CreateAnimation("monster0.bmp", "WaddlediIdle", 216, 219, 0.3f, true);
	Monster1Renderer->ChangeAnimation("WaddlediIdle");

	GameEngineCollision* Monster1Col = CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
}


void Monster1::Render()
{
}

void Monster1::Update()
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

bool Monster1::CheckMapCollision()
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