#include "DanceStage.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "GameEngineBase/GameEngineWindow.h"
#include "GameEngine/GameEngineImage.h"
#include <GameEngine/GameEngineRenderer.h>
#include "StarAttackEffect.h"
#include "AttackEffect.h"
#include "IceAttackEffect.h"
#include "FireAttackEffect.h"
#include "SparkAttackEffect.h"
#include "RunEffect.h"
#include "GameEngineBase/GameEngineSound.h"



DanceStage::DanceStage()
	:DanceKirbyRenderer(nullptr)
	,PlayerRenderer_(nullptr)
	,Player_(nullptr)
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
	BgmPlayer_ = GameEngineSound::SoundPlayControl("ClearWzTreasure.mp3");
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
		BasicRenderer_ = Player_->GetRenderer();
		BasicRenderer_->GetActor()->Off();
		BasicRenderer_->SetAlpha(0);
		DanceKirbyRenderer = Player_->CreateRenderer("Test2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(245.0f, 250.0f));
		GameEngineImage* DanceKirbyImage = DanceKirbyRenderer->GetImage();
		DanceKirbyImage->CutCount(10, 6);
		DanceKirbyRenderer->CreateAnimation("Test2.bmp", "DanceStart", 0, 0, 0.1f, false);
		DanceKirbyRenderer->CreateAnimation("Test2.bmp", "Dance", 0, 56, 0.08f, false);
		DanceKirbyRenderer->ChangeAnimation("DanceStart");
		DanceKirbyRenderer->SetPivot(float4(384.0f, 0.0f));
		DanceKirbyRenderer->GetActor()->On();

		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);

		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
	}
}

void DanceStage::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	BgmPlayer_.Stop();
}
