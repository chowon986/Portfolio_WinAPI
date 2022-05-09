#include "TitleLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineSound.h>

TitleLevel::TitleLevel()
{
	DelayTime_ = 0.0f;
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Loading()
{

}

void TitleLevel::DelayUpdate()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange") || true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		GameEngine::GetInst().ChangeLevel("IntroStory");
	}
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);

	Background* Title = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* TitleRenderer = Title->CreateRenderer("Title.bmp");
	GameEngineImage* Grass1Image = TitleRenderer->GetImage();
	Grass1Image->CutCount(2, 1);
	TitleRenderer->CreateAnimation("Title.bmp", "Title", 0, 1, 0.4f, true);
	TitleRenderer->ChangeAnimation("Title");
}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlayOneShot("Enter.wav");
}