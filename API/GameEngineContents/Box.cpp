#include "Box.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"


Box::Box()
	:Obstruction()
{
}

Box::~Box()
{
}

void Box::Start()
{
	Obstruction::Start();
	Renderer_ = CreateRenderer("Box.bmp");
}

void Box::Update()
{
	ColUpdate();
}

