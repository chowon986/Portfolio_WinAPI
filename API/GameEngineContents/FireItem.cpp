#include "FireItem.h"
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>

FireItem::FireItem()
{
}

FireItem::~FireItem()
{
}

void FireItem::Start()
{
	FireItemRenderer_ = CreateRenderer("FireItem.bmp");
	FireItemCol_ = CreateCollision("Item", float4(40.0f, 40.0f), float4(0.0f, 0.0f));
}

void FireItem::Update()
{
	if (true == FireItemCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		Death();
	}
}
