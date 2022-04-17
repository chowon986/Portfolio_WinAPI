#include "Brontobert.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Brontobert::Brontobert()
	: Monster()
{
}

Brontobert::~Brontobert()
{
}

void Brontobert::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* BrontobertRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* BrontobertImage = BrontobertRenderer->GetImage();
	BrontobertImage->CutCount(10, 26);
	BrontobertRenderer->CreateAnimation("monster0.bmp", "BrontobertIdle", 33, 34, 0.3f, true);
	BrontobertRenderer->ChangeAnimation("BrontobertIdle");
}


void Brontobert::Render()
{
}

void Brontobert::Update()
{
	PrevPos_ = GetPosition();

	float4 NewPos;

	NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	NewPos.y = GetPosition().y + GameEngineTime::GetDeltaTime() * GetSpeed();
	SetPosition(NewPos);

	if (true == CheckMapCollision())
	{
		SetPosition(PrevPos_);
	}
}

bool Brontobert::CheckMapCollision()
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