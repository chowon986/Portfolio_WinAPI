#include "WorldMap.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineEnum.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include <GameEngineContents/ContentsEnum.h>
#include "BotUI.h"

WorldMap::WorldMap()
{
}

WorldMap::~WorldMap()
{
}


void WorldMap::Loading()
{


}

void WorldMap::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("Level1"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1");
	}

	if (true == GameEngineInput::GetInst()->IsPress("Level2"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level2");
	}

	if (true == GameEngineInput::GetInst()->IsPress("Level3"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level3");
	}

	if (true == GameEngineInput::GetInst()->IsPress("Level4"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level4");
	}

}

void WorldMap::LevelChangeStart()
{
	{
		Background* WorldMap = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WorldMapRenderer = WorldMap->CreateRenderer("WorldMap.bmp");
	}

	{
		Background* WorldMapStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WorldMapStarRenderer = WorldMapStar->CreateRenderer("WorldMapStar.bmp", RenderPivot::CENTER, float4(-100,100));
		GameEngineImage* WorldMapStarImage = WorldMapStarRenderer->GetImage();
		WorldMapStarImage->CutCount(6, 2);
		WorldMapStarRenderer->CreateAnimation("WorldMapStar.bmp", "WorldMapStar", 0, 11, 0.08f, true);
		WorldMapStarRenderer->ChangeAnimation("WorldMapStar");
	}

	{
		Background* WorldMapUI = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WorldMapUIRenderer = WorldMapUI->CreateRenderer("WorldMapUI.bmp", RenderPivot::CENTER, float4(-100,-240));
	}

	{
		// UI 이미지들을 애니메이션처럼 []에 넣고 꺼내 쓸 수 없을까?
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}
}
