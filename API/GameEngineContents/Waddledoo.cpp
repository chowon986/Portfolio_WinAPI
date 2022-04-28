#include "Waddledoo.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Monster.h"
#include "Player.h"
#include <vector>

Waddledoo::Waddledoo()
	: Monster()
	, AttackRenderer_(nullptr)
	, AttackCol_(nullptr)
	, AttackRangeCol_(nullptr)
	, AttackTime_(1.0f)
{
	//SetMonsterClass(MonsterClass::BEAM);
}

Waddledoo::~Waddledoo()
{
}

void Waddledoo::Start()
{
	Monster::Start();

	Renderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("monster1.bmp", "WalkRight", 17, 21, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "WalkLeft", 276, 280, 0.3f, true); 
	Renderer_->CreateAnimation("monster1.bmp", "AttackRight", 22, 25, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "AttackLeft", 281, 284, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "CollisionLeft", 28, 28, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "CollisionRight", 287, 287, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "DieLeft", 30, 31, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "DieRight", 289, 290, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);

	Renderer_->ChangeAnimation("WalkRight");

	AttackRenderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* AttackImage = AttackRenderer_->GetImage();
	AttackImage->CutCount(10, 52);
	AttackRenderer_->CreateAnimation("monster1.bmp", "Attack", 26, 27, 0.3f, true);
	AttackRenderer_->ChangeAnimation("Attack");
	AttackRenderer_->SetAlpha(0);
	AttackCol_ = CreateCollision("AttackCol", float4(20.0f,20.0f), float4(0.0f,0.0f));
	AttackRangeCol_ = CreateCollision("AttackRangeCol", float4(100.0f, 50.0f), float4(0.0f, -25.0f));
	AttackCol_->Off();
}

void Waddledoo::Render()
{
}

void Waddledoo::Update()
{
	UpdateAttack();
	UpdateMove();
	Die();
}

bool Waddledoo::CanWalk()
{
	if (false == CanMove_)
	{
		return false;
	}

	return Monster::CanWalk();
}

void Waddledoo::Walk()
{
	Monster::Walk();
	AttackRenderer_->SetAlpha(0);
}

void Waddledoo::UpdateAttack()
{
	if (true == Collision_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	{
		return;
	}
	std::vector<GameEngineCollision*> Result;
	if (AttackRangeCol_->CollisionResult("KirbyCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			Player* ColPlayer = dynamic_cast<Player*>(Collision->GetActor());
			SetPlayer(ColPlayer);
			if (ColPlayer != nullptr)
			{
				CanMove_ = false;
				float Distance = ColPlayer->GetPosition().x - GetPosition().x;
				if (Distance < 0)
				{
					Dir_ = float4::LEFT;
					Renderer_->ChangeAnimation("AttackLeft");
					AttackRenderer_->SetAlpha(255);
					AttackCol_->On();
					AttackRenderer_->SetPivot(float4(-60.0f, 0.0f));
					AttackCol_->SetPivot(float4(-60.0f, 0.0f));
				}
				else
				{
					Dir_ = float4::RIGHT;
					Renderer_->ChangeAnimation("AttackRight");
					AttackRenderer_->SetAlpha(255);
					AttackCol_->On();
					AttackRenderer_->SetPivot(float4(60.0f, 0.0f));
					AttackCol_->SetPivot(float4(60.0f, 0.0f));
				}
			}
		}
	}

	else
	{
		AttackRenderer_->SetAlpha(0);
		CanMove_ = true;
	}

	std::vector<GameEngineCollision*> AttackResult;
	if (AttackCol_->CollisionResult("KirbyCol", AttackResult, CollisionType::Rect, CollisionType::Rect))
	{
		AttackTime_ += GameEngineTime::GetDeltaTime();
		for (GameEngineCollision* ColResult : AttackResult)
		{
			Player* ColPlayer = dynamic_cast<Player*>(ColResult->GetActor());
			SetPlayer(ColPlayer);
			if (ColPlayer != nullptr)
			{
				if (AttackTime_ > 1.0f)
				{
					AttackTime_ = 0.0f;
					ColPlayer->SetHP(ColPlayer->GetHP() - 1);
				}
			}
		}
	}
}
