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
}

void Box::Update()
{
	// need to chk : collision
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
}
