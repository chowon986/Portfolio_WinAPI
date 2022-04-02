#include "DanceStage.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "GameEngineBase/GameEngineWindow.h"
#include "GameEngine/GameEngineImage.h"
#include <GameEngine/GameEngineRenderer.h>

DanceStage::DanceStage()
{
}

DanceStage::~DanceStage()
{
}


void DanceStage::Loading()
{
	CreateActor<Background>((int)ORDER::BACKGROUND);

}

void DanceStage::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("WorldMap");
	}
}

void DanceStage::LevelChangeStart()
{
	{
		Background* DanceStage = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DanceStageRenderer = DanceStage->CreateRenderer("DanceStage.bmp");
	}

	{
		//NEED TO RECHK KIRBY DANCE
		Player* DanceKirby = CreateActor<Player>((int)ORDER::PLAYER);
		GameEngineRenderer* DanceKirbyRenderer = DanceKirby->CreateRenderer("DanceKirby.bmp", RenderPivot::CENTER, float4(245.0f, 150.0f));
		GameEngineImage* DanceKirbyImage = DanceKirbyRenderer->GetImage();
		DanceKirbyImage->CutCount(10, 6);
		DanceKirbyRenderer->CreateAnimation("DanceKirby.bmp", "DanceKirby", 0, 58, 0.1f, true);
		DanceKirbyRenderer->ChangeAnimation("DanceKirby");
	}
}
