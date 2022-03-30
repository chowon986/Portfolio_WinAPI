#include "WorldMap.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

WorldMap::WorldMap()
{
}

WorldMap::~WorldMap()
{
}


void WorldMap::Loading()
{


}

void WorldMap::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("Level1"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1");
	}

	if (true == GameEngineInput::GetInst()->IsPress("Level2"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level2");
	}

	if (true == GameEngineInput::GetInst()->IsPress("Level3"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level3");
	}

	if (true == GameEngineInput::GetInst()->IsPress("Level4"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level4");
	}

}

void WorldMap::LevelChangeStart()
{
}
