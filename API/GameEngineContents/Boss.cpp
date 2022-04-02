#include "Boss.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}


void Boss::Loading()
{
	CreateActor<Background>((int)ORDER::BACKGROUND);
}

void Boss::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("EndingStory");
	}
}

void Boss::LevelChangeStart()
{
}
