#include "GameEngineLevelBase.h"
#include <GameEngineContents/Background.h>
#include <GameEngineContents/ContentsEnum.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>

int GameEngineLevelBase::MAJOR_LEVEL = 1;
GameEngineSoundPlayer GameEngineLevelBase::LEVEL_BGM;

GameEngineLevelBase::GameEngineLevelBase()
	: AlphaRenderer_(nullptr)
	, DelayTime_(0.0f)
	, ElapsedTime_(0.0f)
{
}

GameEngineLevelBase::~GameEngineLevelBase()
{
}

void GameEngineLevelBase::Update()
{
	ElapsedTime_ += GameEngineTime::GetDeltaTime();
	if (ElapsedTime_ < DelayTime_)
	{
		float alpha = ((DelayTime_ - ElapsedTime_) / DelayTime_) * 255;
		AlphaRenderer_->SetAlpha(alpha);
	}
	else
	{
		AlphaRenderer_->SetAlpha(0);
		DelayUpdate();
	}
}

void GameEngineLevelBase::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Background* AlphaBlack = CreateActor<Background>((int)ORDER::ALPHA);
	AlphaRenderer_ = AlphaBlack->CreateRenderer("Black.bmp");
	AlphaRenderer_->SetAlpha(255);
}

void GameEngineLevelBase::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
