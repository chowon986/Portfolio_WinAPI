#include "IntroStory.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

IntroStory::IntroStory()
{
}

IntroStory::~IntroStory()
{
}


void IntroStory::Loading()
{

}

void IntroStory::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1");
	}
}