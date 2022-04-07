#include "BigBox.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

BigBox::BigBox()
{
}

BigBox::~BigBox()
{
}

void BigBox::Start()
{
	BigBoxRenderer_ = CreateRenderer("BigBox.bmp");
	BigBoxCol_ = CreateCollision("Obstruction", float4(80.0f, 80.0f), float4(0.0f, 0.0f));
}

void BigBox::Update()
{
	if (true) // chk : 공격을 받으면
	{
		//Death();
	}
}
