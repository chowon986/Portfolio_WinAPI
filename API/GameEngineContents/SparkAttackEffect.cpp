#include "SparkAttackEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>
#include "MonBotUI.h"
#include <GameEngineContents/GameEngineLevelBase.h>

SparkAttackEffect::SparkAttackEffect()
{

}

SparkAttackEffect::~SparkAttackEffect()
{
}

void SparkAttackEffect::Start()
{
	Collision_ = CreateCollision("SparkAttackCol", float4(150.0f, 150.0f), float4(0.0f, -25.0f));

	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(SparkAttackEffectState::None);
}

void SparkAttackEffect::Update()
{
	StateUpdate();
}

void SparkAttackEffect::Render()
{
}

void SparkAttackEffect::SetState(SparkAttackEffectState _SparkAttackEffectState)
{
	SparkAttackEffectState_ = _SparkAttackEffectState;
}

SparkAttackEffectState SparkAttackEffect::GetState()
{
	return SparkAttackEffectState_;
}

void SparkAttackEffect::StateUpdate()
{
	switch (SparkAttackEffectState_)
	{
	case SparkAttackEffectState::SparkAttackEffect:
		UpdateSparkAttackEffect();
		break;
	case SparkAttackEffectState::None:
		UpdateNone();
		break;
	}
}

void SparkAttackEffect::UpdateNone()
{
	Collision_->Off();
}

void SparkAttackEffect::UpdateSparkAttackEffect()
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
				Monster_->SetHP(Monster_->GetHP() - 1);
				if (Monster_->GetHP() > 0)
				{
					GameEngineLevelBase* Level = dynamic_cast<GameEngineLevelBase*>(GetLevel());
					if (Level != nullptr)
					{
						MonBotUI* MonBotUI = Level->GetMonBotUI();
						MonBotUI->On();
						MonBotUI->SetMonster(Monster_);
					}
				}
			}
		}
	}
}
