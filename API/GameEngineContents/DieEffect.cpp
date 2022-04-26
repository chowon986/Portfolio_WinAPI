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
	Collision_ = CreateCollision("DieCol", float4(150.0f, 150.0f), float4(0.0f, -25.0f));

	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

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
	case DieEffectState::None:
		UpdateNone();
		break;
	}
}

void DieEffect::UpdateNone()
{
	Collision_->Off();
}

void DieEffect::UpdateDieEffect()
{
	Collision_->On();

	std::vector<GameEngineCollision*> SparkResult;
	if (true == Collision_->CollisionResult("BasicMonster", SparkResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* SparkCollision : SparkResult)
		{
			GameEngineActor* SparkColActor = SparkCollision->GetActor();
			Monster* Monster_ = dynamic_cast<Monster*>(SparkColActor);
			if (Monster_ != nullptr)
			{
				Monster_->SetDir(float4::ZERO);
				Monster_->RightDirCol_->Off();
				Monster_->LeftDirCol_->Off();
				Monster_->SetHP(Monster_->GetHP() - 1);
			}
		}
	}
}
