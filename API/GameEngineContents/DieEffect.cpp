#include "DieEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

DieEffect::DieEffect()
{

}

DieEffect::~DieEffect()
{
}

void DieEffect::Start()
{
	Renderer_ = CreateRenderer("MonsterDie.bmp");
	Image_ = Renderer_->GetImage();
	Image_->CutCount(10, 3);
	Renderer_->CreateAnimation("MonsterDie.bmp", "Die", 0, 23, 0.03f, true);
	Renderer_->CreateAnimation("MonsterDie.bmp", "Cannon", 14, 23, 0.03f, true);
	Renderer_->CreateAnimation("MonsterDie.bmp", "None", 14, 14, 0.03f, true);

	GameEngineLevel* Level = GetLevel();
	if (Level->GetColMapImage() != nullptr)
	{
	ColMapImage_ = Level->GetColMapImage();
	}
	Renderer_->ChangeAnimation("None");
}

void DieEffect::Update()
{
	StateUpdate();
}

void DieEffect::Render()
{
}

void DieEffect::SetState(DieEffectState _DieEffectState)
{
	DieEffectState_ = _DieEffectState;
	switch (DieEffectState_)
	{
	case DieEffectState::DieEffect:
		Renderer_->ChangeAnimation("Die");
		break;
	case DieEffectState::CannonEffect:
		Renderer_->ChangeAnimation("Cannon");
		break;
	case DieEffectState::None:
		Renderer_->ChangeAnimation("None");
		break;
	}
	StateUpdate();
}

DieEffectState DieEffect::GetState()
{
	return DieEffectState_;
}

void DieEffect::StateUpdate()
{
	switch (DieEffectState_)
	{
	case DieEffectState::DieEffect:
		UpdateDieEffect();
		break;
	case DieEffectState::CannonEffect:
		UpdateCannonEffect();
		break;
	case DieEffectState::None:
		UpdateNone();
		break;
	}
}

void DieEffect::UpdateNone()
{
}

void DieEffect::UpdateDieEffect()
{
	if (Renderer_->IsAnimationName("Die") && Renderer_->IsEndAnimation())
	{
		SetState(DieEffectState::None);
	}
}

void DieEffect::UpdateCannonEffect()
{
	if (Renderer_->IsEndAnimation())
	{
		SetState(DieEffectState::None);
	}
}

