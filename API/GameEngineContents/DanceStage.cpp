#include "DanceStage.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"

DanceStage::DanceStage()
{
}

DanceStage::~DanceStage()
{
}


void DanceStage::Loading()
{
	CreateActor<Background>((int)ORDER::BACKGROUND);

}

void DanceStage::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("WorldMap");
	}
}