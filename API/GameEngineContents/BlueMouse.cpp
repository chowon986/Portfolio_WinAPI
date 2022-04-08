#include "BlueMouse.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


BlueMouse::BlueMouse()
{
}

BlueMouse::~BlueMouse()
{
}

void BlueMouse::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* BlueMouseRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* BlueMouseImage = BlueMouseRenderer->GetImage();
	BlueMouseImage->CutCount(10, 26);
	BlueMouseRenderer->CreateAnimation("monster0.bmp", "BlueMouseIdle", 216, 219, 0.3f, true);
	BlueMouseRenderer->ChangeAnimation("BlueMouseIdle");
}


void BlueMouse::Render()
{
}

void BlueMouse::Update()
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

bool BlueMouse::CheckMapCollision()
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
		if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50) {
			return true;
		}
	}
}