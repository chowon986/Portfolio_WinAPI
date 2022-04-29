#include "TreasureChest.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

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
}