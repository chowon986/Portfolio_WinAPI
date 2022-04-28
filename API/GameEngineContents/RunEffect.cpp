#include "RunEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

RunEffect::RunEffect()
{

}

RunEffect::~RunEffect()
{
}

void RunEffect::Start()
{
	Renderer_ = CreateRenderer("RunEffect.bmp");
	GameEngineImage* RunImage = Renderer_->GetImage();
	RunImage->CutCount(10, 4);
	Renderer_->CreateAnimation("RunEffect.bmp", "RunRight", 0, 18, 0.1f, true);
	Renderer_->CreateAnimation("RunEffect.bmp", "RunLeft", 19, 37, 0.1f, true);
	Renderer_->CreateAnimation("RunEffect.bmp", "Idle", 38, 38, 0.1f, true);

	Renderer_->ChangeAnimation("Idle");

	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(RunEffectState::None);
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
		Renderer_->ChangeAnimation("RunRight");
		break;
	case RunEffectState::RunEffectLeft:
		Renderer_->ChangeAnimation("RunLeft");
		break;
	}
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
	Renderer_->ChangeAnimation("Idle");
	Renderer_->SetAlpha(0);
}

void RunEffect::UpdateRunEffectRight()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(-10.0f, 0.0f));
	//if (true == Renderer_->IsEndAnimation())
	//{
	//	SetState(RunEffectState::None);
	//}
}

void RunEffect::UpdateRunEffectLeft()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(10.0f, 0.0f));
	//if (true == Renderer_->IsEndAnimation())
	//{
	//	SetState(RunEffectState::None);
	//}
}

void RunEffect::Render()
{
}