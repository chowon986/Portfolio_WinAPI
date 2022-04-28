#include "DieEffect.h"
#include "Monster.h"
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
	SetState(DieEffectState::None);
}

void DieEffect::Update()
{

}

void DieEffect::Render()
{
}

void DieEffect::SetState(DieEffectState _DieEffectState)
{
	DieEffectState_ = _DieEffectState;
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
	Renderer_->ChangeAnimation("None");
}

void DieEffect::UpdateDieEffect()
{
	Renderer_->ChangeAnimation("Die");
}

void DieEffect::UpdateCannonEffect()
{
	Renderer_->ChangeAnimation("Cannon");
}

