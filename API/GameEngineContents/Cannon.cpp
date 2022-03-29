#include "Cannon.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"

Cannon::Cannon()
{
}

Cannon::~Cannon()
{
}


void Cannon::Loading()
{
	CreateActor<Background>((int)ORDER::BACKGROUND);
}

void Cannon::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("DanceStage");
	}
}