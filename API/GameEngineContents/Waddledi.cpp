#include "Waddledi.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"


Waddledi::Waddledi()
{
}

Waddledi::~Waddledi()
{
}

void Waddledi::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();
	SetHP(1);
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
	//SetMove(Direction_ * GameEngineTime::GetDeltaTime() * GetSpeed());

	//if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(RightWalk))
	//{
	//	SetPosition(RightWalk);
	//}

	//if (0 > Player_->GetPosition().x - GetPosition().x)
	//{
	//	SetMove(RightWalk);
	//}

	//if (0 < Player_->GetPosition().x - GetPosition().x)
	//{
	//	SetMove(LeftWalk);
	//}
	// 
	// 커비의 공격에만 체력 감소함 -> 커비 공격 구현 이후 변경 필요
	if (true == WaddlediCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		SetHP(GetHP() - 1);
		if (0 == GetHP())
		{
			WaddlediRenderer_->ChangeAnimation("WaddlediDie");
			Death(1.0f);
		}
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
		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(20.0f, 0.0f)))
		{
			return true;
		}

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() - float4(20.0f, 0.0f)))
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
