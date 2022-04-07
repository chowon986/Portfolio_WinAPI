#include "Tomato.h"
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>

Tomato::Tomato()
{
}

Tomato::~Tomato()
{
}

void Tomato::Start()
{
	TomatoRenderer_ = CreateRenderer("Tomato.bmp");
	TomatoCol_ = CreateCollision("Item", float4(40.0f, 40.0f), float4(5.0f, 0.0f));
}

void Tomato::Update()
{
	std::vector <GameEngineCollision*> ColResult;
	if (true == TomatoCol_->CollisionResult("KirbyCol", ColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : ColResult)
		{
			GameEngineActor* Actor = Collision->GetActor();
			Player* Kirby = dynamic_cast<Player*>(Actor);
			if (nullptr != Kirby)
			{
				Kirby->SetHP(9);
				Death();
			}
		}
	}
}
