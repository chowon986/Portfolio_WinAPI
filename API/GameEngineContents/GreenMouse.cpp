#include "GreenMouse.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


GreenMouse::GreenMouse()
	: Monster()
	, ColMapImage_(nullptr)
	, Level_(nullptr)
{
}

GreenMouse::~GreenMouse()
{
}

void GreenMouse::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* GreenMouseRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* GreenMouseImage = GreenMouseRenderer->GetImage();
	GreenMouseImage->CutCount(10, 26);
	GreenMouseRenderer->CreateAnimation("monster0.bmp", "GreenMouseIdle", 160, 164, 0.3f, true);
	GreenMouseRenderer->ChangeAnimation("GreenMouseIdle");

}


void GreenMouse::Render()
{
}

void GreenMouse::Update()
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

bool GreenMouse::CheckMapCollision()
{
	return true;
}