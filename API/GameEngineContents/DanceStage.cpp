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
#include "AbandonEffect.h"
#include "AnimationKirby.h"
#include "GameEngineBase/GameEngineSound.h"



DanceStage::DanceStage()
	:AnimationKirby_(nullptr)
{
}

DanceStage::~DanceStage()
{
}


void DanceStage::Loading()
{
}

void DanceStage::DelayUpdate()
{
}

void DanceStage::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	SetMapSizeX(768);
	SetMapSizeY(576);

	SetColMapImage("DanceStageColMap.bmp");
	ColMapImage_ = GetColMapImage();

	{
		Background* DanceStage = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DanceStageRenderer = DanceStage->CreateRenderer("DanceStage.bmp");
	}

	{
		AnimationKirby_ = CreateActor<AnimationKirby>((int)ORDER::ANIMATION);
		AnimationKirby_->SetPosition(float4(384.0f, 390.0f));
		AnimationKirby_->SetAnimationKirbyClass(AnimationKirbyClass::DANCE);
	}

	Background* AlphaBlack = CreateActor<Background>((int)ORDER::ALPHA);
	AlphaRenderer_ = AlphaBlack->CreateRenderer("Black.bmp");
	AlphaRenderer_->SetAlpha(0);
}

void DanceStage::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}
