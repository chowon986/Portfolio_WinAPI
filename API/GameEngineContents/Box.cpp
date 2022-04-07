#include "Box.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Box::Box()
{
}

Box::~Box()
{
}

void Box::Start()
{

	BoxRenderer_ = CreateRenderer("Box.bmp");
	BoxCol_ = CreateCollision("Obstruction", float4(40.0f, 40.0f), float4(0.0f, 0.0f));
}

void Box::Update()
{
	if (true == BoxCol_->CollisionCheck("KirbyCol",CollisionType::Rect,CollisionType::Rect)) // chk : 공격을 받으면
	{
		Death();
	}
}
