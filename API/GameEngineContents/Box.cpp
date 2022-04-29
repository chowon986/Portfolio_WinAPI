#include "Box.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"

Box::Box()
	:Obstruction()
	, Collision_(nullptr)
	, Renderer_(nullptr)
{
}

Box::~Box()
{
}

void Box::Start()
{
	Obstruction::Start();
}

void Box::Update()
{
	ColUpdate();
}

