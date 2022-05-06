#include "Sword.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Monster.h"
#include "Player.h"
#include <vector>


Sword::Sword()
	: Monster()
	, AttackCol_(nullptr)
	, AttackRangeCol_(nullptr)
	, AttackTime_(1.0f)

{
	SetMonsterClass(MonsterClass::SWORD);
}

Sword::~Sword()
{
}

void Sword::Start()
{
	Monster::Start();

	Renderer_ = CreateRenderer("Monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);

	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 181, 186, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 440, 445, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "AttackRight", 187, 193, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "AttackLeft", 446, 472, 0.3f, true);

	Renderer_->CreateAnimation("monster1.bmp", "CollisionLeft", 194, 194, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "CollisionRight", 473, 473, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "DieLeft", 194, 195, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "DieRight", 473, 474, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);

	Renderer_->ChangeAnimation("WalkRight");

	AttackCol_ = CreateCollision("AttackCol", float4(20.0f, 20.0f), float4(0.0f, 0.0f));
	AttackRangeCol_ = CreateCollision("AttackRangeCol", float4(100.0f, 50.0f), float4(0.0f, -25.0f));
	AttackCol_->Off();
}

void Sword::Render()
{
}

void Sword::DelayUpdate	()
{
	UpdateAttack();
	UpdateMove();
	Die();
}

bool Sword::CanWalk()
{
	if (false == CanMove_)
	{
		return false;
	}

	return Monster::CanWalk();
}

void Sword::Walk()
{
	Monster::Walk();
}

void Sword::UpdateAttack()
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
					AttackCol_->On();
					AttackCol_->SetPivot(float4(-60.0f, 0.0f));
				}
				else
				{
					Dir_ = float4::RIGHT;
					Renderer_->ChangeAnimation("AttackRight");
					AttackCol_->On();
					AttackCol_->SetPivot(float4(60.0f, 0.0f));
				}
			}
		}
	}

	else
	{
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
