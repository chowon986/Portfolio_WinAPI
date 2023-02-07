#include "GroundStarEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

GroundStarEffect::GroundStarEffect()
	: Renderer_(nullptr)
	, Image_(nullptr)
	, GroundStarEffectState_(GroundStarEffectState::None)
	, ColMapImage_(nullptr)
	, Collision_(nullptr)
{

}

GroundStarEffect::~GroundStarEffect()
{
}

void GroundStarEffect::Start()
{

	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	Renderer_ = CreateRenderer("MonsterDie.bmp");
	GameEngineImage* GroundStarImage = Renderer_->GetImage();
	GroundStarImage->CutCount(10, 4);
	Renderer_->CreateAnimation("MonsterDie.bmp", "GroundStar", 11, 11, 1.0f, true);
	Renderer_->CreateAnimation("MonsterDie.bmp", "None", 24, 24, 0.1f, true);

	Renderer2_ = CreateRenderer("Abandon.bmp");
	GameEngineImage* GroundStarImage2 = Renderer2_->GetImage();
	GroundStarImage2->CutCount(5, 1);
	Renderer2_->CreateAnimation("Abandon.bmp", "None", 0, 4, 0.1f, true);
	Renderer2_->ChangeAnimation("None");
	Renderer2_->Off();

	Renderer_->ChangeAnimation("None");
	SetState(GroundStarEffectState::None);
}

void GroundStarEffect::Update()
{
	StateUpdate();
}


void GroundStarEffect::SetState(GroundStarEffectState _GroundStarEffectState)
{
	GroundStarEffectState_ = _GroundStarEffectState;

	switch (GroundStarEffectState_)
	{
	case GroundStarEffectState::GroundStarEffect:
		Renderer_->ChangeAnimation("GroundStar");
		break;
	case GroundStarEffectState::None:
		Renderer_->ChangeAnimation("None");
		break;
	case GroundStarEffectState::Abandon:
		Renderer2_->On();
		Renderer2_->ChangeAnimation("None");
	}

	StateUpdate();
}

GroundStarEffectState GroundStarEffect::GetState()
{
	return GroundStarEffectState_;
}

void GroundStarEffect::StateUpdate()
{
	switch (GroundStarEffectState_)
	{
	case GroundStarEffectState::GroundStarEffect:
		UpdateGroundStarEffect();
		break;
	case GroundStarEffectState::None:
		UpdateNone();
		break;
	}
}

void GroundStarEffect::UpdateNone()
{
}

void GroundStarEffect::UpdateGroundStarEffect()
{
	Renderer_->SetPivot(float4(0.0f, 10.0f));
	if (true == Renderer_->IsEndAnimation())
	{
		SetState(GroundStarEffectState::Abandon);
	}
}

void GroundStarEffect::UpdateAbandon()
{
	if (true == Renderer2_->IsAnimationName("None") && true == Renderer2_->IsEndAnimation())
	{
		Renderer2_->Off();
	}
}

void GroundStarEffect::Render()
{
}