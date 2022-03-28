#include "Level4.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

Level4::Level4()
{
}

Level4::~Level4()
{
}


void Level4::Loading()
{

}

void Level4::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Boss");
	}
}