#include "GameOver.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <stdlib.h>


GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}


void GameOver::Loading()
{
	CreateActor<Background>((int)ORDER::BACKGROUND);
}

void GameOver::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("Title");
	}

}

void GameOver::LevelChangeStart()
{
	{
		Background* GameOver = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameOver->CreateRenderer("GameOver.bmp");
	}
}
