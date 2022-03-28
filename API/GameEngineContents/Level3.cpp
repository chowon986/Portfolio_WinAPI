#include "Level3.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

Level3::Level3()
{
}

Level3::~Level3()
{
}


void Level3::Loading()
{

}

void Level3::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Cannon");
	}
}