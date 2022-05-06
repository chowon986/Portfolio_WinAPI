#include "Sparky.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Monster.h"
#include "Player.h"
#include <vector>


Sparky::Sparky()
	: Monster()
	, AttackRenderer_(nullptr)
	, AttackTime_(1.0f)
{
	SetMonsterClass(MonsterClass::SPARK);
}

Sparky::~Sparky()
{
}

void Sparky::Start()
{
	Monster::Start();
	AttackRenderer_ = CreateRenderer("Monster1.bmp");
	GameEngineImage* AttackImage = AttackRenderer_->GetImage();
	AttackImage->CutCount(10, 52);
	AttackRenderer_->CreateAnimation("Monster1.bmp", "Attack", 118, 119, 0.3f, true);
	AttackRenderer_->ChangeAnimation("Attack");
	AttackRenderer_->SetAlpha(255);
	AttackCol_ = CreateCollision("SparkyAttackCol", float4(150.0f, 150.0f), float4(0.0f, -15.0f));
	AttackRangeCol_ = CreateCollision("AttackRangeCol", float4(100.0f, 50.0f), float4(0.0f, -25.0f));
	AttackCol_->Off();

	Renderer_ = CreateRenderer("Monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 108, 111, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 368, 371, 0.3f, true); // need to chk
	Renderer_->CreateAnimation("Monster1.bmp", "Attack", 112, 113, 0.3f, true); // need to chk
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 120, 121, 0.3f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 379, 380, 0.3f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 121, 121, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 380, 380, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);

	Renderer_->ChangeAnimation("WalkRight");


}


void Sparky::Render()
{
}

void Sparky::DelayUpdate()
{
	UpdateAttack();
	UpdateMove();
	Die();
}

bool Sparky::CanWalk()
{
	if (false == CanMove_)
	{
		return false;
	}

	return Monster::CanWalk();
}

void Sparky::Walk()
{
	Monster::Walk();
	AttackRenderer_->SetAlpha(0);
}

void Sparky::UpdateAttack()
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
				Renderer_->ChangeAnimation("Attack");
				AttackRenderer_->SetAlpha(255);
				AttackCol_->On();
			}
		}
	}

	else
	{
		AttackRenderer_->SetAlpha(0);
		AttackCol_->Off();
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
