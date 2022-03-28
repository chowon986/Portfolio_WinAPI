#include "Boss.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}


void Boss::Loading()
{

}

void Boss::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("EndingStory");
	}
}