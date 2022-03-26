#include "IntroStoryLevel.h"
#include "GameEngine/GameEngine.h"
#include "GameEngineContents/IntroBackground.h"
#include "GameEngineContents/IntroCharacter.h"
#include <GameEngineBase/GameEngineInput.h>

enum class ORDER
{
	BACKGROUND,
};

IntroStoryLevel::IntroStoryLevel()
{
}

IntroStoryLevel::~IntroStoryLevel()
{
}

void IntroStoryLevel::Loading()
{
}

void IntroStoryLevel::LevelChangeStart()
{
	CreateActor<IntroBackground>((int)ORDER::BACKGROUND, "Intro"); // 인트로 스토리 추가

}

void IntroStoryLevel::Update()
{

	//GameEngine::GlobalEngine().ChangeLevel("Story");
}