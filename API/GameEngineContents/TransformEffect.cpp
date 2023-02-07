#include "TransformEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

TransformEffect::TransformEffect()
	: ColMapImage_(nullptr)
	, Image_(nullptr)
	, Renderer_(nullptr)
	, TransformEffectState_(TransformEffectState::None)
{

}

TransformEffect::~TransformEffect()
{
}

void TransformEffect::Start()
{
	Renderer_ = CreateRenderer("Transform.bmp");
	Image_ = Renderer_->GetImage();
	Image_->CutCount(10, 2);
	Renderer_->CreateAnimation("Transform.bmp", "Transform", 0, 13, 0.07f, true);
	Renderer_->CreateAnimation("Transform.bmp", "None", 14, 14, 0.03f, true);

	GameEngineLevel* Level = GetLevel();
	if (Level->GetColMapImage() != nullptr)
	{
		ColMapImage_ = Level->GetColMapImage();
	}
	Renderer_->ChangeAnimation("None");
}

void TransformEffect::Update()
{
	StateUpdate();
}

void TransformEffect::Render()
{
}

void TransformEffect::SetState(TransformEffectState _TransformEffectState)
{
	TransformEffectState_ = _TransformEffectState;
	switch (TransformEffectState_)
	{
	case TransformEffectState::TransformEffect:
		Renderer_->ChangeAnimation("Transform");
		break;
	case TransformEffectState::None:
		Renderer_->ChangeAnimation("None");
		break;
	}
	StateUpdate();
}

TransformEffectState TransformEffect::GetState()
{
	return TransformEffectState_;
}

void TransformEffect::StateUpdate()
{
	switch (TransformEffectState_)
	{
	case TransformEffectState::TransformEffect:
		UpdateTransformEffect();
		break;
	case TransformEffectState::None:
		UpdateNone();
		break;
	}
}

void TransformEffect::UpdateNone()
{
}

void TransformEffect::UpdateTransformEffect()
{
	Renderer_->SetPivot(float4(0.0f, 10.0f));
	if (Renderer_->IsAnimationName("Transform") && Renderer_->IsEndAnimation())
	{
		SetState(TransformEffectState::None);
	}
}

