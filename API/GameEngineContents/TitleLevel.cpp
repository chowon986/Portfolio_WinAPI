#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "GameEngineContents/IntroBackground.h"
#include "GameEngineContents/IntroCharacter.h"
#include <GameEngineBase/GameEngineInput.h>

enum class ORDER
{
	BACKGROUND,
	CHARACTER
};

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
}

void TitleLevel::LevelChangeStart()
{
	//CreateActor<IntroBackground>((int)ORDER::BACKGROUND, "Intro");
	if (false == GameEngineInput::GetInst()->IsKey("Enter"))
	{
		// 이때 대문자여야 합니다.
		GameEngineInput::GetInst()->CreateKey("Enter", VK_RETURN); // 엔터 두개 다 작동하는지 확인 필요
	}
}

void TitleLevel::LevelChangeEnd()
{
}

void TitleLevel::Update()
{
	if (GameEngineInput::GetInst()->IsPress("Enter"))
	{
		GameEngine::GlobalEngine().ChangeLevel("IntroStory");
	}
}