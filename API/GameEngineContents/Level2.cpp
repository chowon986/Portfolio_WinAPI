#include "Level2.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

Level2::Level2()
{
}

Level2::~Level2()
{
}


void Level2::Loading()
{

}

void Level2::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Cannon");
	}
}