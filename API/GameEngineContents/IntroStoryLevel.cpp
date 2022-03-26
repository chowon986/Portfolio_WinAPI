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
	CreateActor<IntroBackground>((int)ORDER::BACKGROUND, "Intro"); // ��Ʈ�� ���丮 �߰�

}

void IntroStoryLevel::Update()
{

	//GameEngine::GlobalEngine().ChangeLevel("Story");
}