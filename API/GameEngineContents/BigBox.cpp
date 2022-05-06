#include "BigBox.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

BigBox::BigBox()
	:Obstruction()
{
}

BigBox::~BigBox()
{
}

void BigBox::Start()
{
	Obstruction::Start();
	Renderer_ = CreateRenderer("BigBox.bmp");
	Collision_->SetScale(float4(82.0f, 82.0f));
}

void BigBox::DelayUpdate()
{
	ColUpdate();
}
