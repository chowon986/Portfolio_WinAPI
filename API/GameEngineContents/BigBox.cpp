#include "BigBox.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

BigBox::BigBox()
	:Obstruction()
	, Collision_(nullptr)
	, Renderer_(nullptr)
{
}

BigBox::~BigBox()
{
}

void BigBox::Start()
{
	Obstruction::Start();
	Renderer_ = CreateRenderer("BigBox.bmp");
	Collision_ = CreateCollision("Obstruction", float4(81.0f, 81.0f), float4(0.0f, 0.0f));
}

void BigBox::Update()
{

}
