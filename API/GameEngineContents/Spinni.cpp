#include "Spinni.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Spinni::Spinni()
	: Monster()
	, Level_(nullptr)
	, ColMapImage_(nullptr)
{
}

Spinni::~Spinni()
{
}

void Spinni::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* SpinniRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* SpinniImage = SpinniRenderer->GetImage();
	SpinniImage->CutCount(10, 26);
	SpinniRenderer->CreateAnimation("monster0.bmp", "SpinniIdle", 108, 111, 0.3f, true);
	SpinniRenderer->ChangeAnimation("SpinniIdle");
}


void Spinni::Render()
{
}

void Spinni::Update()
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

bool Spinni::CheckMapCollision()
{
	return true;
}