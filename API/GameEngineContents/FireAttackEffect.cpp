#include "FireAttackEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

FireAttackEffect::FireAttackEffect()
{

}

FireAttackEffect::~FireAttackEffect()
{
}

void FireAttackEffect::Start()
{
	Collision_ = CreateCollision("FireAttackCol", float4(150.0f, 50.0f), float4(100.0f, -25.0f));
	Renderer_ = CreateRenderer("FireAtt.bmp");
	Image_ = Renderer_->GetImage();
	Image_->CutCount(7, 4);
	Renderer_->CreateAnimation("FireAtt.bmp", "AttackRight", 0, 13, 0.03f, true);
	Renderer_->CreateAnimation("FireAtt.bmp", "AttackLeft", 14, 27, 0.03f, true);

	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(FireAttackEffectState::None);
}

void FireAttackEffect::Update()
{
	StateUpdate();
}


void FireAttackEffect::SetState(FireAttackEffectState _FireAttackEffectState)
{
	FireAttackEffectState_ = _FireAttackEffectState;

	switch (FireAttackEffectState_)
	{
	case FireAttackEffectState::FireAttackEffectRight:
		Renderer_->ChangeAnimation("AttackRight");
		break;
	case FireAttackEffectState::FireAttackEffectLeft:
		Renderer_->ChangeAnimation("AttackLeft");
		break;
	}
}

FireAttackEffectState FireAttackEffect::GetState()
{
	return FireAttackEffectState_;
}

void FireAttackEffect::StateUpdate()
{
	switch (FireAttackEffectState_)
	{
	case FireAttackEffectState::FireAttackEffectRight:
		UpdateFireAttackEffectRight();
		break;
	case FireAttackEffectState::FireAttackEffectLeft:
		UpdateFireAttackEffectLeft();
		break;
	case FireAttackEffectState::None:
		UpdateNone();
		break;
	}
}

void FireAttackEffect::UpdateNone()
{
	Collision_->Off();
}

void FireAttackEffect::UpdateFireAttackEffectRight()
{
	Renderer_->SetPivot(float4(40.0f, 0.0f));
	Collision_->SetPivot(float4(100.0f, -25.0f));

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
				Monster_->SetDir(float4::ZERO);
				Monster_->RightDirCol_->Off();
				Monster_->LeftDirCol_->Off();
			}
		}
	}

	if (true == Renderer_->IsEndAnimation())
	{
		SetState(FireAttackEffectState::None);
	}
}

void FireAttackEffect::UpdateFireAttackEffectLeft()
{
	Renderer_->SetPivot(float4(-200.0f, 0.0f));
	Collision_->SetPivot(float4(-100.0f, -25.0f));

	if (true == Renderer_->IsEndAnimation())
	{
		SetState(FireAttackEffectState::None);
	}

	std::vector<GameEngineCollision*> Result;
	if (true == Collision_->CollisionResult("BasicMonster", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			GameEngineActor* ColActor = Collision->GetActor();
			Monster* Monster_ = dynamic_cast<Monster*>(ColActor);
			if (Monster_ != nullptr)
			{
				Monster_->SetHP(Monster_->GetHP() - 2);
				Monster_->SetDir(float4::ZERO);
				Monster_->RightDirCol_->Off();
				Monster_->LeftDirCol_->Off();
			}
		}
	}
}

void FireAttackEffect::Render()
{
}