#include "Ground.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include <GameEngine/GameEngineImage.h>


Ground::Ground()
	: Renderer_(nullptr)
	, Collision_(nullptr)
{
}

Ground::~Ground()
{
}

void Ground::Start()
{
	Collision_ = CreateCollision("Ground", float4(10.0f, 10.0f), float4(0.0f, 0.0f));
	MoveCollision_ = CreateCollision("MoveGround", float4(50.0f, 70.0f), float4(0.0f, 10.0f));
	Renderer_ = CreateRenderer("Ground.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 5);
	Renderer_->CreateAnimation("Ground.bmp", "0", 0, 0, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "1", 1, 1, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "2", 2, 2, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "3", 3, 3, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "4", 4, 4, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "5", 5, 5, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "6", 6, 6, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "7", 7, 7, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "8", 8, 8, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "9", 9, 9, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "10", 10, 10, 0.1f, true);

	Renderer_->CreateAnimation("Ground.bmp", "11", 11, 11, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "12", 12, 12, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "13", 13, 13, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "14", 14, 14, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "15", 15, 15, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "16", 16, 16, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "17", 17, 17, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "18", 18, 18, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "19", 19, 19, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "20", 20, 20, 0.1f, true);

	Renderer_->CreateAnimation("Ground.bmp", "21", 21, 21, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "22", 22, 22, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "23", 23, 23, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "24", 24, 24, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "25", 25, 25, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "26", 26, 26, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "27", 27, 27, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "28", 28, 28, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "29", 29, 29, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "30", 30, 30, 0.1f, true);

	Renderer_->CreateAnimation("Ground.bmp", "31", 31, 31, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "32", 32, 32, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "33", 33, 33, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "34", 34, 34, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "35", 35, 35, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "36", 36, 36, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "37", 37, 37, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "38", 38, 38, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "39", 39, 39, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "40", 40, 40, 0.1f, true);

	Renderer_->CreateAnimation("Ground.bmp", "41", 41, 41, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "42", 42, 42, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "43", 43, 43, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "44", 44, 44, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "45", 45, 45, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "46", 46, 46, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "47", 46, 46, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "48", 46, 46, 0.1f, true);
	Renderer_->CreateAnimation("Ground.bmp", "49", 46, 46, 0.1f, true);

	Renderer_->ChangeAnimation("46");
}

void Ground::Update()
{
	std::vector<GameEngineCollision*> Result;
	if (true == Collision_->CollisionResult("KirbyCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			Player* Player_ = dynamic_cast<Player*>(Collision->GetActor());			
			if (Player_ != nullptr &&
				Player_->GetKirbyClass() == KirbyClass::ANIMAL)
			{
				KirbyState State_ = Player_->GetState();
				if (State_ == KirbyState::DOWN ||
					State_ == KirbyState::UP ||
					State_ == KirbyState::WALK)
				{
					Death();
				}				
			}
		}
	}
}

