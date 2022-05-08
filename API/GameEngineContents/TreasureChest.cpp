#include "TreasureChest.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"
#include <GameEngineBase/GameEngineSound.h>

TreasureChest::TreasureChest()
	:Monster()
{
}

TreasureChest::~TreasureChest()
{
}

void TreasureChest::Start()
{
	Renderer_ = CreateRenderer("TreasureChest.bmp");
	Collision_ = CreateCollision("Item", float4(40.0f, 40.0f), float4(0.0f, 0.0f));
}

void TreasureChest::Update()
{
	std::vector <GameEngineCollision*> ColResult;
	if (true == Collision_->CollisionResult("KirbyCol", ColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : ColResult)
		{
			GameEngineActor* Actor = Collision->GetActor();
			Player* Kirby = dynamic_cast<Player*>(Actor);
			if (nullptr != Kirby)
			{
				GameEngineSound::SoundPlayOneShot("EatItem.wav", 0);
				Death();
			}
		}
	}
}