#include "Cannon.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

Cannon::Cannon()
{
}

Cannon::~Cannon()
{
}


void Cannon::Loading()
{

}

void Cannon::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("DanceStage");
	}
}