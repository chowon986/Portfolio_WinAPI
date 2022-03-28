#include "TitleLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "IntroBackground.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Loading()
{

}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("IntroStory");
	}
}