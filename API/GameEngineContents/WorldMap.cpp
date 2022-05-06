#include "WorldMap.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineEnum.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Background.h"
#include <GameEngineContents/ContentsEnum.h>
#include "BotUI.h"
#include <vector>
#include "StarAttackEffect.h"
#include "AttackEffect.h"
#include "IceAttackEffect.h"
#include "FireAttackEffect.h"
#include "SparkAttackEffect.h"
#include "RunEffect.h"
#include "AbandonEffect.h"

WorldMap::WorldMap()
	: Level_(0)
{
}

WorldMap::~WorldMap()
{
}


void WorldMap::Loading()
{


}

void WorldMap::DelayUpdate()
{
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Player_->GetPosition() + float4::DOWN))
	{
		LittleStarRenderer->On();
		LittleStarRenderer2->On();
		WorldMapStarRenderer1->On();
		ChooseLevel1_->On();
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Player_->GetPosition() + float4::DOWN))
	{
		if (true == GameEngineInput::GetInst()->IsDown("Right"))
		{
			Level_++;
			if (Level_ > GameEngineLevelBase::MAJOR_LEVEL + 1)
			{
				Level_ = GameEngineLevelBase::MAJOR_LEVEL + 1;
				if (Level_ > 3)
				{
					Level_ = 3;
				}
			}
		}

		if (true == GameEngineInput::GetInst()->IsDown("Left"))
		{
			Level_--;
			if (Level_ < 1)
			{
				Level_ = 1;
			}
		}


		switch (Level_)
		{
		case 1:
			Player_->SetPosition(float4(147.0f, Player_->GetPosition().y));
			break;
		case 2:
			Player_->SetPosition(float4(382.0f, Player_->GetPosition().y));
			break;
		case 3:
			Player_->SetPosition(float4(617.0f, Player_->GetPosition().y));
			break;
		}

		if (3 == Level_ && true == GameEngineInput::GetInst()->IsDown("OpenDoor"))
		{
			GameEngine::GetInst().ChangeLevel("Boss");
		}

		if (2 == Level_ && true == GameEngineInput::GetInst()->IsDown("OpenDoor"))
		{
			GameEngine::GetInst().ChangeLevel("Level2");
		}

		if (1 == Level_ && true == GameEngineInput::GetInst()->IsDown("OpenDoor"))
		{
			GameEngine::GetInst().ChangeLevel("Level1");
		}
	}
}

void WorldMap::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	DelayTime_ = 1.0f;
	BgmPlayer_ = GameEngineSound::SoundPlayControl("SelectStage.mp3");

	SetMapSizeX(768);
	SetMapSizeY(576);

	SetColMapImage("WorldMapCol.bmp");
	ColMapImage_ = GetColMapImage();

	{
		Background* WorldMap = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WorldMapRenderer = WorldMap->CreateRenderer("WorldMap.bmp");
	}

	{

		Player_ = CreateActor<Player>((int)ORDER::PLAYER);		
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
		PlayerStatus_->SetPlayer(Player_);
		Player_->GetRenderer()->ChangeAnimation("Dance");
		Player_->SetDelayTime(DelayTime_);

		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);
		AbandonEffect* AbandonEffect_ = CreateActor<AbandonEffect>((int)ORDER::EFFECT);
		Player_->SetAbandonEffect(AbandonEffect_);
		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
	}

	{
		Background* WorldMap0 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* ChooseLevel0_ = WorldMap0->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-240, 90));
		GameEngineImage* WorldMap0Image = ChooseLevel0_->GetImage();
		WorldMap0Image->CutCount(5, 3);
		ChooseLevel0_->CreateAnimation("WorldMap1.bmp", "ClearLevel", 3, 3, 0.1f, true);
		ChooseLevel0_->ChangeAnimation("ClearLevel");

		Background* WorldMap1 = CreateActor<Background>((int)ORDER::BACKGROUND);
		ChooseLevel1_ = WorldMap1->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0, 90));
		GameEngineImage* WorldMap1Image = ChooseLevel1_->GetImage();
		WorldMap1Image->CutCount(5, 3);
		ChooseLevel1_->CreateAnimation("WorldMap1.bmp", "NewLevel1", 0, 2, 0.3f, false);
		ChooseLevel1_->ChangeAnimation("NewLevel1");
		ChooseLevel1_->Off();

		//Background* WorldMap1 = CreateActor<Background>((int)ORDER::BACKGROUND);
		//GameEngineRenderer* ChooseLevel1_ = WorldMap1->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0, 100));
		//GameEngineImage* WorldMap1Image = ChooseLevel1_->GetImage();
		//WorldMap1Image->CutCount(5, 3);
		//ChooseLevel1_->CreateAnimation("WorldMap1.bmp", "NewLevel1", 0, 2, 0.1f, false);
		//ChooseLevel1_->CreateAnimation("WorldMap1.bmp", "ClearLevel1", 3, 3, 0.1f, false);
		//ChooseLevel1_->ChangeAnimation("ClearLevel1");


		//Background* WorldMap2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		//GameEngineRenderer* ChooseLevel2_ = WorldMap2->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(240, 100));
		//GameEngineImage* WorldMap2Image = ChooseLevel2_->GetImage();
		//WorldMap2Image->CutCount(5, 3);

		//ChooseLevel2_->CreateAnimation("WorldMap1.bmp", "BossLevel", 8, 9, 0.1f, false);
		//ChooseLevel2_->ChangeAnimation("BossLevel");
	}

	{
		Background* WorldMapStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WorldMapStarRenderer = WorldMapStar->CreateRenderer("WorldMapStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-240, 100));
		GameEngineImage* WorldMapStarImage = WorldMapStarRenderer->GetImage();
		WorldMapStarImage->CutCount(6, 2);
		WorldMapStarRenderer->CreateAnimation("WorldMapStar.bmp", "WorldMapStar0", 0, 11, 0.08f, true);
		WorldMapStarRenderer->ChangeAnimation("WorldMapStar0");
		Star1_ = WorldMapStar->CreateCollision("Star", float4(50.0f, 10.0f), float4(-240.0f, 100.0f));

		Background* WorldMapStar1 = CreateActor<Background>((int)ORDER::BACKGROUND);
		WorldMapStarRenderer1 = WorldMapStar1->CreateRenderer("WorldMapStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0, 100));
		GameEngineImage* WorldMapStarImage1 = WorldMapStarRenderer1->GetImage();
		WorldMapStarImage1->CutCount(6, 2);
		WorldMapStarRenderer1->CreateAnimation("WorldMapStar.bmp", "WorldMapStar1", 0, 11, 0.08f, true);
		WorldMapStarRenderer1->ChangeAnimation("WorldMapStar1");
		WorldMapStarRenderer1->Off();

		Background* WorldMapStar2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WorldMapStarRenderer2 = WorldMapStar2->CreateRenderer("WorldMapStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(240, 100));
		GameEngineImage* WorldMapStarImage2 = WorldMapStarRenderer2->GetImage();
		WorldMapStarImage2->CutCount(6, 2);
		WorldMapStarRenderer2->CreateAnimation("WorldMapStar.bmp", "WorldMapStar1", 0, 11, 0.08f, true);
		WorldMapStarRenderer2->ChangeAnimation("WorldMapStar1");
		WorldMapStarRenderer2->Off();

		Background* Explain = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* ExplainRenderer = Explain->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(300, 282));
		GameEngineImage* ExplainImage = ExplainRenderer->GetImage();
		ExplainImage->CutCount(5, 3);
		ExplainRenderer->CreateAnimation("WorldMap1.bmp", "1", 4, 4, 0.1f, true);
		ExplainRenderer->CreateAnimation("WorldMap1.bmp", "2", 5, 5, 0.1f, true);
		ExplainRenderer->CreateAnimation("WorldMap1.bmp", "3", 6, 6, 0.1f, true);
		ExplainRenderer->CreateAnimation("WorldMap1.bmp", "4", 7, 7, 0.1f, true);
		ExplainRenderer->ChangeAnimation("1");

		Background* LittleStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		LittleStarRenderer = LittleStar->CreateRenderer("LittleStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-150, 120));
		LittleStarRenderer2 = LittleStar->CreateRenderer("LittleStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-90, 120));
		LittleStarRenderer->Off();
		LittleStarRenderer2->Off();
	}

	{
		Background* WorldMapUI = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WorldMapUIRenderer = WorldMapUI->CreateRenderer("WorldMapUI.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-100, -240));
	}

	GameEngineLevelBase::MAJOR_LEVEL = 1;
	Level_ = GameEngineLevelBase::MAJOR_LEVEL;
	switch (Level_)
	{
	case 1:
		Player_->SetPosition(float4(147.0f, 100.0f));
		break;
	case 2:
		Player_->SetPosition(float4(382.0f, 100.0f));
		break;
	case 3:
		Player_->SetPosition(float4(617.0f, 100.0f));
		break;
	}
}

void WorldMap::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	BgmPlayer_.Stop();
}
