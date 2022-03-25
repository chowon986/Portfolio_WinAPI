#include "IntroLevel.h"
#include "GameEngine/GameEngine.h"
#include "GameEngineContents/IntroBackground.h"

enum class ORDER
{
	Intro,
};

IntroLevel::IntroLevel()
{
}

IntroLevel::~IntroLevel()
{
}

void IntroLevel::Loading()
{
}

void IntroLevel::LevelChangeStart()
{
	CreateActor<IntroBackground>("Intro", 0);
}

void IntroLevel::Update()
{
	// GameEngine::GlobalEngine().ChangeLevel("Play");
}