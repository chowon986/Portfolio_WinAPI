#include "BombBox.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"

BombBox::BombBox()
	:Obstruction()
	, Collision_(nullptr)
	, Renderer_(nullptr)
{
}

BombBox::~BombBox()
{
}

void BombBox::Start()
{
	Obstruction::Start();
	Renderer_ = CreateRenderer("BombBox.bmp");
	Collision_ = CreateCollision("Obstruction", float4(10.0f, 50.0f), float4(0.0f, -15.0f));
	Collision2_ = CreateCollision("Obstruction", float4(50.0f, 10.0f), float4(25.0f, 0.0f));

}

void BombBox::Update()
{
	ColUpdate();
	std::vector<GameEngineCollision*> Result;
	if (true == Collision2_->CollisionResult("KirbySlideCol", Result, CollisionType::Rect, CollisionType::Rect) ||
		true == Collision2_->CollisionResult("AttackCol", Result, CollisionType::Rect, CollisionType::Rect) ||
		true == Collision2_->CollisionResult("FireAttackCol", Result, CollisionType::Rect, CollisionType::Rect) ||
		true == Collision2_->CollisionResult("IceAttackCol", Result, CollisionType::Rect, CollisionType::Rect) ||
		true == Collision2_->CollisionResult("SparkAttackCol", Result, CollisionType::Rect, CollisionType::Rect))
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
