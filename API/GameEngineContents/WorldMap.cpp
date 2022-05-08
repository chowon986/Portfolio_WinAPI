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
	, BombRenderer_(nullptr)
	, ChooseLevel1_(nullptr)
	, ChooseLevel2_(nullptr)
	, EffectSoundPlay_(true)
	, ExplainRenderer2_(nullptr)
	, ExplainRenderer3_(nullptr)
	, ExplainRenderer4_(nullptr)
	, ExplainRenderer_(nullptr)
	, LittleStarRenderer(nullptr)
	, LittleStarRenderer2(nullptr)
	, MajorLevel_(1)
	, Player2_(nullptr)
	, PlayerStatus2_(nullptr)
	, PlayerStatus_(nullptr)
	, Player_(nullptr)
	, Star1_(nullptr)
	, WorldMapStarRenderer1(nullptr)
	, WorldMapStarRenderer2(nullptr)
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
	// 첫번째 위치 바닥에 닿으면
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Player_->GetPosition() + float4::DOWN))
	{
		if (MajorLevel_ == 1)
		{
			if (EffectSoundPlay_ == true)
			{
			GameEngineSound::SoundPlayOneShot("Transform.wav", 0);
			EffectSoundPlay_ = false;
			}
			LittleStarRenderer->On();
			LittleStarRenderer2->On();
			WorldMapStarRenderer1->On();
			ChooseLevel1_->On();
			ExplainRenderer3_->On();
			BombRenderer_->On();
		}

		else if (MajorLevel_ == 2)
		{
			if (EffectSoundPlay_ == true)
			{
				GameEngineSound::SoundPlayOneShot("Transform.wav", 0);
				EffectSoundPlay_ = false;
			}
			LittleStarRenderer->On();
			LittleStarRenderer2->On();
			WorldMapStarRenderer1->On();
			WorldMapStarRenderer2->On();
			ChooseLevel1_->On();
			ChooseLevel2_->On();
			ExplainRenderer3_->On();
			ExplainRenderer4_->On();
			BombRenderer_->On();
		}
	}

	// 오른쪽 버튼 누르면 MAJOR_LEVEL +1까지만큼 이동 가능
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Player_->GetPosition() + float4::DOWN))
	{
		if (true == GameEngineInput::GetInst()->IsDown("Right"))
		{
			GameEngineSound::SoundPlayOneShot("Jump.wav", 0);

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
			GameEngineSound::SoundPlayOneShot("Jump.wav", 0);

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
			ExplainRenderer_->ChangeAnimation("Explain1");
			break;
		case 2:
			Player_->SetPosition(float4(382.0f, Player_->GetPosition().y));
			if (MajorLevel_ == 1)
			{
				ExplainRenderer_->ChangeAnimation("Explain2");
			}
			if (MajorLevel_ == 2)
			{
				ExplainRenderer_->ChangeAnimation("Explain3");
			}
			break;
		case 3:
			Player_->SetPosition(float4(617.0f, Player_->GetPosition().y));
			ExplainRenderer_->ChangeAnimation("Explain4");
			break;
		}

		if (3 == Level_ && true == GameEngineInput::GetInst()->IsDown("OpenDoor"))
		{
			GameEngineSound::SoundPlayOneShot("Enter.wav", 0);
			GameEngine::GetInst().ChangeLevel("Level3");
		}

		if (2 == Level_ && true == GameEngineInput::GetInst()->IsDown("OpenDoor"))
		{
			GameEngineSound::SoundPlayOneShot("Enter.wav", 0);
			GameEngine::GetInst().ChangeLevel("Level2");
		}

		if (1 == Level_ && true == GameEngineInput::GetInst()->IsDown("OpenDoor"))
		{
			GameEngineSound::SoundPlayOneShot("Enter.wav", 0);
			GameEngine::GetInst().ChangeLevel("Level1");
		}
	}
}

void WorldMap::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	EffectSoundPlay_ = true;

	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	DelayTime_ = 1.0f;
	BgmPlayer_ = GameEngineSound::SoundPlayControl("SelectStage.mp3");


	SetMapSizeX(768);
	SetMapSizeY(576);

	SetColMapImage("WorldMapCol.bmp");
	ColMapImage_ = GetColMapImage();

	Level_ = GameEngineLevelBase::MAJOR_LEVEL;
	MajorLevel_ = GameEngineLevelBase::MAJOR_LEVEL;
	{
		Background* WorldMap = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WorldMapRenderer = WorldMap->CreateRenderer("WorldMap.bmp");
	}

	{
		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);
		AbandonEffect* AbandonEffect_ = CreateActor<AbandonEffect>((int)ORDER::EFFECT);

		Player_ = CreateActor<Player>((int)ORDER::PLAYER);		
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
		PlayerStatus_->SetPlayer(Player_);
		Player_->SetDelayTime(DelayTime_);
		Player_->GetRenderer()->ChangeAnimation("JumpDownRight");
		//Player_->GetRenderer()->ChangeAnimation("Dance");

		Player_->SetAbandonEffect(AbandonEffect_);
		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
		AbandonEffect_->Off();
		StarAttackEffect_->Off();
		AttackEffect_->Off();
		IceAttackEffect_->Off();
		SparkAttackEffect_->Off();
		RunEffect_->Off();
		FireAttackEffect_->Off();
	}

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

	{
		Background* WorldMap0 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* ChooseLevel0_ = WorldMap0->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-240, 90));
		GameEngineImage* WorldMap0Image = ChooseLevel0_->GetImage();
		WorldMap0Image->CutCount(5, 3);
		ChooseLevel0_->CreateAnimation("WorldMap1.bmp", "ClearLevel", 3, 3, 0.1f, true);
		ChooseLevel0_->ChangeAnimation("ClearLevel");
		if (MajorLevel_ == 1)
		{
			Background* WorldMap1 = CreateActor<Background>((int)ORDER::BACKGROUND);
			ChooseLevel1_ = WorldMap1->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0, 90));
			GameEngineImage* WorldMap1Image = ChooseLevel1_->GetImage();
			WorldMap1Image->CutCount(5, 3);
			ChooseLevel1_->CreateAnimation("WorldMap1.bmp", "NewLevel1", 0, 2, 0.3f, false);
			ChooseLevel1_->ChangeAnimation("NewLevel1");
			ChooseLevel1_->Off();
		}

		else if (MajorLevel_ == 2)
		{
			Background* WorldMap1 = CreateActor<Background>((int)ORDER::BACKGROUND);
			ChooseLevel1_ = WorldMap1->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0, 90));
			GameEngineImage* WorldMap1Image = ChooseLevel1_->GetImage();
			WorldMap1Image->CutCount(5, 3);
			ChooseLevel1_->CreateAnimation("WorldMap1.bmp", "ClearLevel", 3, 3, 0.1f, false);
			ChooseLevel1_->ChangeAnimation("ClearLevel");
			ChooseLevel1_->Off();

			Background* WorldMap2 = CreateActor<Background>((int)ORDER::BACKGROUND);
			ChooseLevel2_ = WorldMap2->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235, 95));
			GameEngineImage* WorldMap2Image = ChooseLevel1_->GetImage();
			WorldMap2Image->CutCount(5, 3);
			ChooseLevel2_->CreateAnimation("WorldMap1.bmp", "BossLevel", 8, 9, 0.1f, false);
			ChooseLevel2_->ChangeAnimation("BossLevel");
			ChooseLevel2_->Off();

		}

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
		WorldMapStarRenderer2 = WorldMapStar2->CreateRenderer("WorldMapStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235, 100));
		GameEngineImage* WorldMapStarImage2 = WorldMapStarRenderer2->GetImage();
		WorldMapStarImage2->CutCount(6, 2);
		WorldMapStarRenderer2->CreateAnimation("WorldMapStar.bmp", "WorldMapStar1", 0, 11, 0.08f, true);
		WorldMapStarRenderer2->ChangeAnimation("WorldMapStar1");
		WorldMapStarRenderer2->Off();

		Background* Explain = CreateActor<Background>((int)ORDER::BACKGROUND);
		ExplainRenderer_ = Explain->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(300, 282));
		GameEngineImage* ExplainImage = ExplainRenderer_->GetImage();
		ExplainImage->CutCount(5, 3);
		ExplainRenderer_->CreateAnimation("WorldMap1.bmp", "Explain1", 4, 4, 0.1f, true);
		ExplainRenderer_->CreateAnimation("WorldMap1.bmp", "Explain2", 5, 5, 0.1f, true);
		ExplainRenderer_->CreateAnimation("WorldMap1.bmp", "Explain3", 6, 6, 0.1f, true);
		ExplainRenderer_->CreateAnimation("WorldMap1.bmp", "Explain4", 7, 7, 0.1f, true);

		Background* Explain2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		ExplainRenderer2_ = Explain2->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-240, 115));
		GameEngineImage* Explain2Image = ExplainRenderer2_->GetImage();
		Explain2Image->CutCount(5, 3);
		ExplainRenderer2_->CreateAnimation("WorldMap1.bmp", "Explain5", 10, 10, 0.1f, true);
		ExplainRenderer2_->ChangeAnimation("Explain5");

		Background* Explain3 = CreateActor<Background>((int)ORDER::BACKGROUND);
		ExplainRenderer3_ = Explain3->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0, 115));
		GameEngineImage* Explain3Image = ExplainRenderer2_->GetImage();
		Explain3Image->CutCount(5, 3);
		ExplainRenderer3_->CreateAnimation("WorldMap1.bmp", "Explain6", 11, 11, 0.1f, true);
		ExplainRenderer3_->ChangeAnimation("Explain6");
		ExplainRenderer3_->Off();

		Background* Explain4 = CreateActor<Background>((int)ORDER::BACKGROUND);
		ExplainRenderer4_ = Explain4->CreateRenderer("WorldMap1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235, 115));
		GameEngineImage* Explain4Image = ExplainRenderer2_->GetImage();
		Explain4Image->CutCount(5, 3);
		ExplainRenderer4_->CreateAnimation("WorldMap1.bmp", "Explain7", 12, 12, 0.1f, true);
		ExplainRenderer4_->ChangeAnimation("Explain7");
		ExplainRenderer4_->Off();



		Background* LittleStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		LittleStarRenderer = LittleStar->CreateRenderer("LittleStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-150, 120));
		LittleStarRenderer2 = LittleStar->CreateRenderer("LittleStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-90, 120));
		LittleStarRenderer->Off();
		LittleStarRenderer2->Off();

		Background* Bomb = CreateActor<Background>((int)ORDER::BACKGROUND);
		BombRenderer_ = Bomb->CreateRenderer("Level.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235, 115));
		GameEngineImage* BombImage = BombRenderer_->GetImage();
		BombImage->CutCount(9, 1);
		BombRenderer_->CreateAnimation("Level.bmp", "Bomb", 0, 8, 0.1f, false);
		BombRenderer_->ChangeAnimation("Bomb");
		BombRenderer_->Off();

		if (Level_ == 1)
		{
			ExplainRenderer_->ChangeAnimation("Explain1");
			BombRenderer_->SetPivot(float4(0, 80));
		}
		else if (Level_ == 2)
		{
			ExplainRenderer_->ChangeAnimation("Explain3");
			BombRenderer_->SetPivot(float4(235, 80));
		}
	}

	{
		Background* WorldMapUI = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WorldMapUIRenderer = WorldMapUI->CreateRenderer("WorldMapUI.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-100, -240));
	}


}

void WorldMap::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	Player_->Death();
	BgmPlayer_.Stop();
	PlayerStatus_->Death();
}
