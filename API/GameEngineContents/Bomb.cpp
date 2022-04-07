#include "Bomb.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

void Bomb::Start()
{
	BombRenderer_ = CreateRenderer("Bomb.bmp");
	BombCol_ = CreateCollision("Obstruction", float4(20.0f, 20.0f), float4(0.0f, 0.0f));
}

void Bomb::Update()
{
	// chk pnt : kirby 공격 col이랑 부딪히면으로 수정 필요
	if (true == BombCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		BombCol_ = CreateCollision("Obstruction", float4(100.0f, 100.0f), float4(0.0f, 0.0f));
		Death();
	}
}
