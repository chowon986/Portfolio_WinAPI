#include "AttackEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>
#include "MonBotUI.h"
#include <GameEngineContents/GameEngineLevelBase.h>

AttackEffect::AttackEffect()
	: Collision_(nullptr)
	, AttackEffectState_(AttackEffectState::None)
	, ColMapImage_(nullptr)
	, Image_(nullptr)
	, Renderer_(nullptr)
{

}

AttackEffect::~AttackEffect()
{
}

void AttackEffect::Start()
{
	Collision_ = CreateCollision("AttackCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	Renderer_ = CreateRenderer("Attack.bmp");
	Image_ = Renderer_->GetImage();
	Image_->CutCount(10, 4);
	Renderer_->CreateAnimation("Attack.bmp", "AttackRight", 0, 12, 0.03f, true);
	Renderer_->CreateAnimation("Attack.bmp", "AttackLeft", 20, 32, 0.03f, true);
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(AttackEffectState::None);
}

void AttackEffect::Update()
{
	StateUpdate();
}

void AttackEffect::Render()
{
}

void AttackEffect::SetState(AttackEffectState _AttackEffectState)
{
	AttackEffectState_ = _AttackEffectState;

	switch (AttackEffectState_)
	{
	case AttackEffectState::AttackEffectRight:
		Renderer_->ChangeAnimation("AttackRight");
		StartPos_ = GetPosition();
		break;
	case AttackEffectState::AttackEffectLeft:
		Renderer_->ChangeAnimation("AttackLeft");
		StartPos_ = GetPosition();
		break;
	}
}

AttackEffectState AttackEffect::GetState()
{
	return AttackEffectState_;
}

void AttackEffect::StateUpdate()
{
	switch (AttackEffectState_)
	{
	case AttackEffectState::AttackEffectRight:
		UpdateAttackEffectRight();
		break;
	case AttackEffectState::AttackEffectLeft:
		UpdateAttackEffectLeft();
		break;
	case AttackEffectState::None:
		UpdateNone();
		break;
	}
}

void AttackEffect::UpdateAttackEffectRight()
{
	Time_ += GameEngineTime::GetDeltaTime();
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(40.0f, 0.0f));
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(90.0f, 50.0f));
	Collision_->SetPivot(float4(90.0f, -25.0f));
	Collision_->On();

	float4 Distance = GetPosition() - StartPos_;

	std::vector<GameEngineCollision*> Result;
	if (true == Collision_->CollisionResult("BasicMonster", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			GameEngineActor* ColActor = Collision->GetActor();
			Monster* Monster_ = dynamic_cast<Monster*>(ColActor);
			if (Monster_ != nullptr)
			{
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

	if (Distance.x > 10 || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			SetState(AttackEffectState::None);
		}

	}
}

void AttackEffect::UpdateAttackEffectLeft()
{
	Time_ += GameEngineTime::GetDeltaTime();
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(-150.0f, 0.0f));
	SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(90.0f, 50.0f));
	Collision_->SetPivot(float4(-90.0f, -25.0f));
	Collision_->On();

	float4 Distance = GetPosition() - StartPos_;

	std::vector<GameEngineCollision*> Result;
	if (true == Collision_->CollisionResult("BasicMonster", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			GameEngineActor* ColActor = Collision->GetActor();
			Monster* Monster_ = dynamic_cast<Monster*>(ColActor);
			if (Monster_ != nullptr)
			{
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

	if (Distance.x < -10 || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			SetState(AttackEffectState::None);
		}
	}
}

void AttackEffect::UpdateNone()
{
	Renderer_->SetAlpha(0);
	Collision_->Off();
}