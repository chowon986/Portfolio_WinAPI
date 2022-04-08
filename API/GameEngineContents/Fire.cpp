#include "Fire.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Fire::Fire()
{
}

Fire::~Fire()
{
}

void Fire::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	FireRenderer_ = CreateRenderer("monster0.bmp");
	FireImage_ = FireRenderer_->GetImage();
	FireImage_->CutCount(10, 26);
	FireRenderer_->CreateAnimation("monster0.bmp", "FireIdle", 160, 164, 0.3f, true);
	FireRenderer_->ChangeAnimation("FireIdle");

	FireCol_ = CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));

}


void Fire::Render()
{
}

void Fire::Update()
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

bool Fire::CheckMapCollision()
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