#include "Box.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::Start()
{
	BoxRenderer_ = CreateRenderer("Box.bmp");
	BoxCol_ = CreateCollision("Obstruction", float4(41.0f,41.0f), float4(0.0f, 0.0f));
	BoxBlockCol_ = CreateCollision("Obstructuin", float4(40.0f, 40.0f), float4(0.0f, 0.0f));
}

void Box::Update()
{
	std::vector<GameEngineCollision*> Result;
	if (true == BoxCol_->CollisionResult("KirbySlideCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			GameEngineActor* ColActor = Collision->GetActor();
			Player* Player_ = dynamic_cast<Player*>(ColActor);
			if (Player_ != nullptr)
			{
				Death();
			}
		}
	}

	std::vector<GameEngineCollision*> ColResult;
	if (true == BoxBlockCol_->CollisionResult("KirbyCol", ColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* BoxCollision : ColResult)
		{
			GameEngineActor* CollisionActor = BoxCollision->GetActor();
			Player* Player_ = dynamic_cast<Player*>(CollisionActor);
			if (Player_ != nullptr)
			{
				float Dir = Player_->GetPosition().x - GetPosition().x;
				if (Dir <= 0)
				{
					Player_->SetPosition(Player_->GetPosition() + float4::LEFT);

				}

				if (Dir > 0)
				{
					Player_->SetPosition(Player_->GetPosition() + float4::RIGHT);

				}
			}
		}
	}
}
