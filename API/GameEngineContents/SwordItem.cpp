#include "SwordItem.h"
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>

SwordItem::SwordItem()
{
}

SwordItem::~SwordItem()
{
}

void SwordItem::Start()
{
	SwordItemRenderer_ = CreateRenderer("SwordItem.bmp");
	SwordItemCol_ = CreateCollision("Item", float4(40.0f, 40.0f), float4(0.0f, 0.0f));
}

void SwordItem::Update()
{
	if (true == SwordItemCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		Death();
	}
}
