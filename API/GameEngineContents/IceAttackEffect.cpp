#include "IceAttackEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

IceAttackEffect::IceAttackEffect()
{

}

IceAttackEffect::~IceAttackEffect()
{
}

void IceAttackEffect::Start()
{
	Collision_ = CreateCollision("IceAttackCol", float4(150.0f, 50.0f), float4(100.0f, -25.0f));
	Renderer_ = CreateRenderer("IceAtt.bmp");
	Image_ = Renderer_->GetImage();
	Image_->CutCount(5, 6);
	Renderer_->CreateAnimation("IceAtt.bmp", "AttackRight", 0, 12, 0.03f, true);
	Renderer_->CreateAnimation("IceAtt.bmp", "AttackLeft", 15, 27, 0.03f, true);

	GameEngineLevel* Level = GetLevel();

	if (nullptr != Level->GetColMapImage())
	{
	ColMapImage_ = Level->GetColMapImage();
	}
	UpdateNone();
}

void IceAttackEffect::Update()
{
	StateUpdate();
}


void IceAttackEffect::SetState(IceAttackEffectState _IceAttackEffectState)
{
	IceAttackEffectState_ = _IceAttackEffectState;

	switch (IceAttackEffectState_)
	{
	case IceAttackEffectState::IceAttackEffectRight:
		Renderer_->ChangeAnimation("AttackRight");
		break;
	case IceAttackEffectState::IceAttackEffectLeft:
		Renderer_->ChangeAnimation("AttackLeft");
		break;
	}
}

IceAttackEffectState IceAttackEffect::GetState()
{
	return IceAttackEffectState_;
}

void IceAttackEffect::StateUpdate()
{
	switch (IceAttackEffectState_)
	{
	case IceAttackEffectState::IceAttackEffectRight:
		UpdateIceAttackEffectRight();
		break;
	case IceAttackEffectState::IceAttackEffectLeft:
		UpdateIceAttackEffectLeft();
		break;
	case IceAttackEffectState::None:
		UpdateNone();
		break;
	}
}

void IceAttackEffect::UpdateNone()
{
	Collision_->Off();
}

void IceAttackEffect::UpdateIceAttackEffectRight()
{
	Collision_->On();
	Renderer_->SetPivot(float4(40.0f, 0.0f));
	Collision_->SetPivot(float4(100.0f, -25.0f));

	if (true == Renderer_->IsEndAnimation())
	{
		SetState(IceAttackEffectState::None);
	}
}

void IceAttackEffect::UpdateIceAttackEffectLeft()
{
	Collision_->On();
	Renderer_->SetPivot(float4(-200.0f, 0.0f));
	Collision_->SetPivot(float4(-100.0f, -25.0f));

	if (true == Renderer_->IsEndAnimation())
	{
		SetState(IceAttackEffectState::None);
	}
}

void IceAttackEffect::Render()
{
}