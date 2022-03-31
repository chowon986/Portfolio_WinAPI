#include "TitleLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Loading()
{
	Background* Title = CreateActor<Background>((int)ORDER::BACKGROUND);
	Title->CreateRenderer("Title.bmp");
}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1");
	}
}