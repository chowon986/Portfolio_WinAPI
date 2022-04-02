#include "Cannon.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

Cannon::Cannon()
{
}

Cannon::~Cannon()
{
}


void Cannon::Loading()
{
	CreateActor<Background>((int)ORDER::BACKGROUND);
}

void Cannon::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("DanceStage");
	}
}

void Cannon::LevelChangeStart()
{
	{
		Background* Cannon = CreateActor<Background>((int)ORDER::BACKGROUND);
		Cannon->CreateRenderer("Cannon.bmp");
	}

	{
		Background* Can = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* CanRenderer = Can->CreateRenderer("can.bmp",RenderPivot::CENTER, float4(0.0f, 60.0f));
		GameEngineImage* CanImage = CanRenderer->GetImage();
		CanImage->CutCount(4, 2);
		CanRenderer->CreateAnimation("can.bmp", "Can", 0, 7, 0.1f, true);
		CanRenderer->ChangeAnimation("Can");
	}

}
