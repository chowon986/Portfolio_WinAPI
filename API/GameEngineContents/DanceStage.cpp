#include "DanceStage.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

DanceStage::DanceStage()
{
}

DanceStage::~DanceStage()
{
}


void DanceStage::Loading()
{


}

void DanceStage::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("WorldMap");
	}
}