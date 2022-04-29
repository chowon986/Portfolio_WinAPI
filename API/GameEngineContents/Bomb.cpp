#include "Bomb.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

Bomb::Bomb()
	:Obstruction()
	, Collision_(nullptr)
	, Renderer_(nullptr)
{
}

Bomb::~Bomb()
{
}

void Bomb::Start()
{
	Obstruction::Start();
	Renderer_ = CreateRenderer("Bomb.bmp");
	Collision_ = CreateCollision("Obstruction", float4(20.0f, 20.0f), float4(0.0f, 0.0f));
}

void Bomb::Update()
{
	ColUpdate();
}
