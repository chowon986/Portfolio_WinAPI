#include "Waddledi.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Monster.h"
#include "Player.h"


Waddledi::Waddledi()
	: ColMapImage_(nullptr)
	, Level_(nullptr)
	, Player_(nullptr)
	, WaddlediCol_(nullptr)
	, WaddlediRenderer_(nullptr)
	, Dir_(float4::ZERO)

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
	WaddlediRenderer_ = CreateRenderer("monster0.bmp");
	GameEngineImage* WaddlediImage = WaddlediRenderer_->GetImage();
	WaddlediImage->CutCount(10, 26);
	WaddlediRenderer_->CreateAnimation("monster0.bmp", "WaddlediWalkRight", 7, 14, 0.3f, true);
	WaddlediRenderer_->CreateAnimation("monster0.bmp", "WaddlediWalkLeft", 7, 14, 0.3f, true);
	WaddlediRenderer_->CreateAnimation("monster0.bmp", "WaddlediDie", 15, 16, 0.3f, true);
	WaddlediRenderer_->ChangeAnimation("WaddlediWalkRight");
	Dir_ = float4::RIGHT;
	WaddlediCol_ = CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
}

void Waddledi::Render()
{
}

void Waddledi::UpdateWalk()
{
}

void Waddledi::Update()
{
	UpdateMove();
 
	//if (/*true == 커비공격col->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect)))*/)
	{
	}
	// 커비의 공격에만 체력 감소함 -> 커비 공격 구현 이후 변경 필요

	//if (true == CheckMapCollision())
	//{
	//	SetPosition(PrevPos_);
	//}

}

void Waddledi::UpdateMove()
{
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(20.0f, 0.0f)))
	{
		Dir_ = float4::RIGHT;
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-20.0f, 0.0f)))
	{
		Dir_ = float4::LEFT;
	}

	if (true == WaddlediCol_->CollisionCheck("EatCol", CollisionType::Rect, CollisionType::Rect))
	{
		Dir_ = float4::ZERO;
	}

	if (// Dir_ == ZERO고,
		 true != WaddlediCol_->CollisionCheck("EatCol", CollisionType::Rect, CollisionType::Rect))
	{
		Dir_ = float4::RIGHT;
	}
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 15);
}
