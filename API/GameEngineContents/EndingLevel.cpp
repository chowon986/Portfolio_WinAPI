#include "EndingLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}


void EndingLevel::Loading()
{

}

void EndingLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		//GameEngine::GlobalEngine().ChangeLevel("DanceStage");
	}
}