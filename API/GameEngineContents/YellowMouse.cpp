#include "YellowMouse.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


YellowMouse::YellowMouse()
{
}

YellowMouse::~YellowMouse()
{
}

void YellowMouse::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* YellowMouseRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* YellowMouseImage = YellowMouseRenderer->GetImage();
	YellowMouseImage->CutCount(10, 26);
	YellowMouseRenderer->CreateAnimation("monster0.bmp", "YellowMouseIdel", 17, 21, 0.3f, true);
	YellowMouseRenderer->ChangeAnimation("YellowMouseIdel");

}

void YellowMouse::Render()
{
}

void YellowMouse::Update()
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

bool YellowMouse::CheckMapCollision()
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

		// ����, ������, �������� �̵� ����
		if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50)
		{
			return true;
		}
	}
}