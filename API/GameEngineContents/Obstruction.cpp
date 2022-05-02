#include "Obstruction.h"
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"

Obstruction::Obstruction()
	:Player_(nullptr)
	,Renderer_(nullptr)
	,Collision_(nullptr)
{
}

Obstruction::~Obstruction()
{
}

void Obstruction::Start()
{
	Collision_ = CreateCollision("Obstruction", float4(41.0f, 41.0f), float4(0.0f, 0.0f));
}

void Obstruction::ColUpdate()
{
	std::vector<GameEngineCollision*> Result;
	if (true == Collision_->CollisionResult("KirbySlideCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			Player* Player_ = dynamic_cast<Player*>(Collision->GetActor());
			SetPlayer(Player_);
			if (Player_ != nullptr)
			{
				Death();
			}
		}
	}

	std::vector<GameEngineCollision*> SparkAttColResult;
	if (true == Collision_->CollisionResult("SparkAttackCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			SparkAttackEffect* SparkAttackEffect_ = dynamic_cast<SparkAttackEffect*>(Collision->GetActor());
			if (SparkAttackEffect_ != nullptr)
			{
				Death();
			}
		}
	}


	std::vector<GameEngineCollision*> FireAttColResult;
	if (true == Collision_->CollisionResult("FireAttackCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			FireAttackEffect* FireAttackEffect_ = dynamic_cast<FireAttackEffect*>(Collision->GetActor());
			if (FireAttackEffect_ != nullptr)
			{
				Death();
			}
		}
	}


	std::vector<GameEngineCollision*> IceAttColResult;
	if (true == Collision_->CollisionResult("IceAttackCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			IceAttackEffect* IceAttackEffect_ = dynamic_cast<IceAttackEffect*>(Collision->GetActor());
			if (IceAttackEffect_ != nullptr)
			{
				Death();
			}
		}
	}


	//std::vector<GameEngineCollision*> SparkAttColResult;
	//if (true == Collision_->CollisionResult("AttackCol", Result, CollisionType::Rect, CollisionType::Rect))
	//{
	//	for (GameEngineCollision* Collision : Result)
	//	{
	//		SparkAttackEffect* SparkAttackEffect_ = dynamic_cast<SparkAttackEffect*>(Collision->GetActor());
	//		if (SparkAttackEffect_ != nullptr)
	//		{
	//			Death();
	//		}
	//	}
	//}
}

void Obstruction::Update()
{
	ColUpdate();
}
