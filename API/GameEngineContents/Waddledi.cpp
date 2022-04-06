#include "Waddledi.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Waddledi::Waddledi()
	: HP_(1)
{
}

Waddledi::~Waddledi()
{
}

void Waddledi::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(CharacterState::WALK);
	WaddlediRenderer_ = CreateRenderer("monster0.bmp");
	GameEngineImage* WaddlediImage = WaddlediRenderer_->GetImage();
	WaddlediImage->CutCount(10, 26);
	WaddlediRenderer_->CreateAnimation("monster0.bmp", "WaddlediIdel", 7, 14, 0.3f, true);
	WaddlediRenderer_->CreateAnimation("monster0.bmp", "WaddlediDie", 15, 16, 0.3f, true);
	WaddlediRenderer_->ChangeAnimation("WaddlediIdel");

	WaddlediCol_ = CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
}

void Waddledi::Render()
{
}

void Waddledi::Update()
{
	PrevPos_ = GetPosition();

	float4 NewPos;
	NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	NewPos.y = GetPosition().y;
	SetPosition(NewPos);

	// 커비의 공격에만 체력 감소함 -> 커비 공격 구현 이후 변경 필요
	if (true == WaddlediCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		SetHP(GetHP() - 1);
		WaddlediRenderer_->ChangeAnimation("WaddlediDie");
		//WaddlediCol_->Death();
		WaddlediRenderer_->Death();
	}

	if (true == CheckMapCollision())
	{
		SetPosition(PrevPos_);
	}

}

bool Waddledi::CheckMapCollision()
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
