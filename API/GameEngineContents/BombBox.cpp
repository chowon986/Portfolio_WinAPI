#include "BombBox.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

BombBox::BombBox()
{
}

BombBox::~BombBox()
{
}

void BombBox::Start()
{
	BombBoxRenderer_ = CreateRenderer("BombBox.bmp");
	BombBoxCol_ = CreateCollision("BombBox", float4(10.0f, 10.0f), float4(0.0f, 0.0f));
}

void BombBox::Update()
{
	if (true == BombBoxCol_->CollisionCheck("Obstruction", CollisionType::Rect, CollisionType::Rect))
	{
		Death(1.0);
	}
}
