#include "Obstruction.h"
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"

Obstruction::Obstruction()
{
}

Obstruction::~Obstruction()
{
}

void Obstruction::Start()
{
	Renderer_ = CreateRenderer("Box.bmp");
	Collision_ = CreateCollision("Obstruction", float4(41.0f, 41.0f), float4(0.0f, 0.0f));
}

void Obstruction::ColUpdate()
{
	std::vector<GameEngineCollision*> Result;
	if (true == Collision_->CollisionResult("KirbySlideCol", Result, CollisionType::Rect, CollisionType::Rect) ||
		true == Collision_->CollisionResult("AttackCol", Result, CollisionType::Rect, CollisionType::Rect) ||
		true == Collision_->CollisionResult("FireAttackCol", Result, CollisionType::Rect, CollisionType::Rect) ||
		true == Collision_->CollisionResult("IceAttackCol", Result, CollisionType::Rect, CollisionType::Rect) ||
		true == Collision_->CollisionResult("SparkAttackCol", Result, CollisionType::Rect, CollisionType::Rect))
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
}

void Obstruction::Update()
{
	ColUpdate();
}
