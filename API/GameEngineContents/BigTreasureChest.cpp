#include "BigTreasureChest.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

BigTreasureChest::BigTreasureChest()
{
}

BigTreasureChest::~BigTreasureChest()
{
}

void BigTreasureChest::Start()
{
	BigTreasureChestRenderer_ = CreateRenderer("BigTreasureChest.bmp");
	BigTreasureChestCol_ = CreateCollision("Item", float4(40.0f, 40.0f), float4(0.0f, 0.0f));
}

void BigTreasureChest::DelayUpdate()
{
	if (true == BigTreasureChestCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		//BigTreasureChestCount + 1;
		Death();
	}
}