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
	if (true == DanceKirbyRenderer->IsAnimationName("Dance") && true == DanceKirbyRenderer->IsEndAnimation())
	{
		GameEngine::GetInst().ChangeLevel("WorldMap");
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Player_->GetPosition() + float4::DOWN) && false != DanceKirbyRenderer->IsAnimationName("DanceStart"))
	{
		DanceKirbyRenderer->ChangeAnimation("Dance");
	}
}

void DanceStage::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetMapSizeX(768);
	SetMapSizeY(576);

	SetColMapImage("DanceStageColMap.bmp");
	ColMapImage_ = GetColMapImage();

	{
		Background* DanceStage = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DanceStageRenderer = DanceStage->CreateRenderer("DanceStage.bmp");
	}

	{

		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		DanceKirbyRenderer = Player_->CreateRenderer("Test2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(245.0f, 150.0f));
		GameEngineImage* DanceKirbyImage = DanceKirbyRenderer->GetImage();
		DanceKirbyImage->CutCount(10, 6);
		DanceKirbyRenderer->CreateAnimation("Test2.bmp", "DanceStart", 0, 0, 0.1f, false);
		DanceKirbyRenderer->CreateAnimation("Test2.bmp", "Dance", 0, 56, 0.1f, false);
		DanceKirbyRenderer->ChangeAnimation("DanceStart");
		DanceKirbyRenderer->SetPivot(float4(384.0f, 0.0f));
	}
}
