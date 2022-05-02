#include "Fire.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"

Fire::Fire()
	: Monster()
	, AttackCol_(nullptr)
	, AttackRangeCol_(nullptr)
	, AttackRenderer_(nullptr)
	, AttackTime_(0.0f)
	, CanMove_(false)
{
	SetMonsterClass(MonsterClass::FIRE);
}

Fire::~Fire()
{
}

void Fire::Start()
{
	Monster::Start();

	Renderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 160, 163, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 419, 422, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "AttackRight", 165, 167, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "AttackLeft", 424, 426, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 179, 179, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 438, 438, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 179, 180, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 438, 439, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);

	Renderer_->ChangeAnimation("WalkRight");

	AttackRenderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* AttackImage = AttackRenderer_->GetImage();
	AttackImage->CutCount(10, 52);
	AttackRenderer_->CreateAnimation("monster1.bmp", "Attack", 168, 178, 0.3f, true);
	AttackRenderer_->ChangeAnimation("Attack");
	AttackRenderer_->SetAlpha(0);
	AttackCol_ = CreateCollision("AttackCol", float4(20.0f, 20.0f), float4(0.0f, 0.0f));
	AttackRangeCol_ = CreateCollision("AttackRangeCol", float4(100.0f, 50.0f), float4(0.0f, -25.0f));
	AttackCol_->Off();
}

void Fire::Render()
{
}

void Fire::Update()
{
	UpdateAttack();
	UpdateMove();
	Die();
}

bool Fire::CanWalk()
{
	if (false == CanMove_)
	{
		return false;
	}

	return Monster::CanWalk();
}

void Fire::Walk()
{
	Monster::Walk();
	AttackRenderer_->SetAlpha(0);
}

void Fire::UpdateAttack()
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
