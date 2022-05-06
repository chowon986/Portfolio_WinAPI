#include "TitleLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

TitleLevel::TitleLevel()
{
	DelayTime_ = 0.0f;
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Loading()
{
	Background* Title = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* TitleRenderer = Title->CreateRenderer("Title.bmp");
	GameEngineImage* Grass1Image = TitleRenderer->GetImage();
	Grass1Image->CutCount(2, 1);
	TitleRenderer->CreateAnimation("Title.bmp", "Title", 0, 1, 0.4f, true);
	TitleRenderer->ChangeAnimation("Title");
}

void TitleLevel::DelayUpdate()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("IntroStory");
	}
}