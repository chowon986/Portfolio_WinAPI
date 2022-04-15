#include "Sparky.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Sparky::Sparky()
{
}

Sparky::~Sparky()
{
}

void Sparky::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* SparkyRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* SparkyImage = SparkyRenderer->GetImage();
	SparkyImage->CutCount(10, 26);
	SparkyRenderer->CreateAnimation("monster0.bmp", "SparkyIdle", 108, 111, 0.3f, true);
	SparkyRenderer->ChangeAnimation("SparkyIdle");
}


void Sparky::Render()
{
}

void Sparky::Update()
{
	void UpdeteMove();

	if (true == CheckMapCollision())
	{
		SetPosition(PrevPos_);
	}
}

void Sparky::UpdateMove()
{
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(20.0f, 0.0f)))
	{
		Dir_ = float4::RIGHT;
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-20.0f, 0.0f)))
	{
		Dir_ = float4::LEFT;
	}

	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 15);
}

bool Sparky::CheckMapCollision()
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