#include "RunEffect.h"
#include "Monster.h"
#include "AbandonEffect.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

RunEffect::RunEffect()
	: RunEffectState_(RunEffectState::None)
	, Renderer_(nullptr)
	, Image_(nullptr)
	, ColMapImage_(nullptr)
	, Collision_(nullptr)
{

}

RunEffect::~RunEffect()
{
}

void RunEffect::Start()
{

	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	Renderer_ = CreateRenderer("RunEffect.bmp");
	GameEngineImage* RunImage = Renderer_->GetImage();
	RunImage->CutCount(10, 4);
	Renderer_->CreateAnimation("RunEffect.bmp", "RunRight", 0, 18, 0.1f, true);
	Renderer_->CreateAnimation("RunEffect.bmp", "RunLeft", 19, 37, 0.1f, true);
	Renderer_->CreateAnimation("RunEffect.bmp", "None", 38, 38, 0.1f, true);

	Renderer_->ChangeAnimation("None");
}

void RunEffect::Update()
{
	StateUpdate();
}


void RunEffect::SetState(RunEffectState _RunEffectState)
{
	RunEffectState_ = _RunEffectState;

	switch (RunEffectState_)
	{
	case RunEffectState::RunEffectRight:
		Renderer_->ChangeAnimation("RunLeft");
		break;
	case RunEffectState::RunEffectLeft:
		Renderer_->ChangeAnimation("RunRight");
		break;
	case RunEffectState::None:
		Renderer_->ChangeAnimation("None");
		break;
	}

	StateUpdate();
}

RunEffectState RunEffect::GetState()
{
	return RunEffectState_;
}

void RunEffect::StateUpdate()
{
	switch (RunEffectState_)
	{
	case RunEffectState::RunEffectRight:
		UpdateRunEffectRight();
		break;
	case RunEffectState::RunEffectLeft:
		UpdateRunEffectLeft();
		break;
	case RunEffectState::None:
		UpdateNone();
		break;
	}
}

void RunEffect::UpdateNone()
{
}

void RunEffect::UpdateRunEffectRight()
{
	Renderer_->SetPivot(float4(-50.0f, 0.0f));
	if (true == Renderer_->IsEndAnimation())
	{
		SetState(RunEffectState::None);
	}
}

void RunEffect::UpdateRunEffectLeft()
{
	Renderer_->SetPivot(float4(50.0f, 0.0f));
	if (true == Renderer_->IsEndAnimation())
	{
		SetState(RunEffectState::None);
	}
}

void RunEffect::Render()
{
}