#include "TreasureChest.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

TreasureChest::TreasureChest()
{
}

TreasureChest::~TreasureChest()
{
}

void TreasureChest::Start()
{
	TreasureChestRenderer_ = CreateRenderer("TreasureChest.bmp");
	TreasureChestCol_ = CreateCollision("Item", float4(40.0f, 40.0f), float4(0.0f, 0.0f));
}

void TreasureChest::Update()
{
	if (true == TreasureChestCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		//TreasureChestCount + 1;
		Death();
	}
}