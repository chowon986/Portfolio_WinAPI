#include "Waddledoo.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Waddledoo::Waddledoo()
{
}

Waddledoo::~Waddledoo()
{
}

void Waddledoo::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* WaddledooRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* WaddledooImage = WaddledooRenderer->GetImage();
	WaddledooImage->CutCount(10, 26);
	WaddledooRenderer->CreateAnimation("monster0.bmp", "WaddledooIdle", 17, 21, 0.3f, true);
	WaddledooRenderer->ChangeAnimation("WaddledooIdle");

}

void Waddledoo::Render()
{
}

void Waddledoo::Update()
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

bool Waddledoo::CheckMapCollision()
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
		if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50) {
			return true;
		}
	}
}