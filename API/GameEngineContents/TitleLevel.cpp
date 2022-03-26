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
		// �̶� �빮�ڿ��� �մϴ�.
		GameEngineInput::GetInst()->CreateKey("Enter", VK_RETURN); // ���� �ΰ� �� �۵��ϴ��� Ȯ�� �ʿ�
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