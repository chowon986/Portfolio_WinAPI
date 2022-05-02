#include "Bomb.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include "player.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"
#include "IceAttackEffect.h"


Bomb::Bomb()
	:Obstruction()
	,Collision2_(nullptr)
	, Col_(false)
{
}

Bomb::~Bomb()
{
}

void Bomb::Start()
{
	Obstruction::Start();
	Renderer_ = CreateRenderer("Bomb.bmp");
	Collision_->SetScale(float4(40.0f, 40.0f));

	Collision2_ = CreateCollision("Bomb", float4(70.0f, 20.0f), float4(35.0f, 0.0f));
	Collision2_->Off();
}

void Bomb::Update()
{
	ColUpdate();
}

void Bomb::ColUpdate()
{

	std::vector<GameEngineCollision*> Result;
	if (true == Collision_->CollisionResult("KirbySlideCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			Player* Player_ = dynamic_cast<Player*>(Collision->GetActor());
			if (Player_ != nullptr)
			{
				Collision2_->On();
				ColOn();
			}
		}
	}

	std::vector<GameEngineCollision*> SparkAttColResult;
	if (true == Collision_->CollisionResult("SparkAttackCol", SparkAttColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : SparkAttColResult)
		{
			SparkAttackEffect* SparkAttackEffect_ = dynamic_cast<SparkAttackEffect*>(Collision->GetActor());
			if (SparkAttackEffect_ != nullptr)
			{
				Collision2_->On();
				ColOn();
			}
		}
	}


	std::vector<GameEngineCollision*> FireAttColResult;
	if (true == Collision_->CollisionResult("FireAttackCol", FireAttColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : FireAttColResult)
		{
			FireAttackEffect* FireAttackEffect_ = dynamic_cast<FireAttackEffect*>(Collision->GetActor());
			if (FireAttackEffect_ != nullptr)
			{
				Collision2_->On();
				ColOn();
			}
		}
	}


	std::vector<GameEngineCollision*> IceAttColResult;
	if (true == Collision_->CollisionResult("IceAttackCol", IceAttColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : IceAttColResult)
		{
			IceAttackEffect* IceAttackEffect_ = dynamic_cast<IceAttackEffect*>(Collision->GetActor());
			if (IceAttackEffect_ != nullptr)
			{
				Collision2_->On();
				ColOn();
			}
		}

	}

	if (Col_ == true)
	{
		Death();
		Col_ = false;
	}
}

bool Bomb::ColOn()
{
	if (Col_ == false)
	{
		Col_ = true;
		return true;
	}
	else
	{
		Col_ = false;
		return false;
	}
}
