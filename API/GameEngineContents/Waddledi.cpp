#include "Waddledi.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Monster.h"
#include "Player.h"
#include <vector>


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
	DirectionCol_ = CreateCollision("DirectionCol", float4(200.0f, 50.0f), float4(0.0f, -30.0f));
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

}

void Waddledi::UpdateMove()
{
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(20.0f, 0.0f)))
	{
		Dir_ = float4::LEFT;
		WaddlediRenderer_->ChangeAnimation("WaddlediWalkLeft");
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-20.0f, 0.0f)))
	{
		Dir_ = float4::RIGHT;
		WaddlediRenderer_->ChangeAnimation("WaddlediWalkRight");
	}

	// 벽에 부딪혔을때
	if (GetPosition().x < 0)
	{
		Dir_ = float4::RIGHT;
		WaddlediRenderer_->ChangeAnimation("WaddlediWalkRight");
	}

	if (GetPosition().x > GetLevel()->GetMapSizeX())
	{
		Dir_ = float4::LEFT;
		WaddlediRenderer_->ChangeAnimation("WaddlediWalkLeft");
	}

	//vector 생성 std::vector<자료형>변수이름;
	std::vector<GameEngineCollision*> Result;
	if (DirectionCol_->CollisionResult("KirbyCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			Player* ColPlayer = dynamic_cast<Player*>(Collision->GetActor()); // 부딪힌 액터 꺼내기
			if (ColPlayer != nullptr)
			{
				float Distance = ColPlayer->GetPosition().x - GetPosition().x;
				if (Distance < 0)
				{
					Dir_ = float4::LEFT;
					WaddlediRenderer_->ChangeAnimation("WaddlediWalkLeft");
				}

				else if (Distance > 0)
				{
					Dir_ = float4::RIGHT;
					WaddlediRenderer_->ChangeAnimation("WaddlediWalkRight");
				}
			}
		}
	}

	if (true == WaddlediCol_->CollisionCheck("EatCol", CollisionType::Rect, CollisionType::Rect))
	{
		Dir_ = float4::ZERO;
	}

	if (Dir_.x == float4::ZERO.x &&
		 true != WaddlediCol_->CollisionCheck("EatCol", CollisionType::Rect, CollisionType::Rect))
	{
		Dir_ = float4::RIGHT;
		WaddlediRenderer_->ChangeAnimation("WaddlediWalkRight");
	}
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 15);

}
