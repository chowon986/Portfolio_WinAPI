#include "AttackEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

AttackEffect::AttackEffect()
{

}

AttackEffect::~AttackEffect()
{
}

void AttackEffect::Start()
{
	Collision_ = CreateCollision("AttackCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	Renderer_ = CreateRenderer("Attack.bmp");
	Renderer_->SetAlpha(0);
	Image_ = Renderer_->GetImage();
	Image_->CutCount(7, 2);
	Renderer_->CreateAnimation("Attack.bmp", "AttackRight", 0, 12, 0.03f, true);
	Renderer_->CreateAnimation("Attack.bmp", "AttackLeft", 0, 12, 0.03f, true);

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

void AttackEffect::UpdateNone()
{
}

void AttackEffect::UpdateAttackEffectRight()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(40.0f, 0.0f));
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(70.0f, 50.0f));
	Collision_->SetPivot(float4(20.0f, -25.0f));

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
			}
		}
	}

	if (Distance.x > 10 || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			Renderer_->SetAlpha(0);
			Collision_->SetScale(float4(0.0f, 0.0f));
			SetState(AttackEffectState::None);
		}

	}
}

void AttackEffect::UpdateAttackEffectLeft()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(40.0f, 0.0f));
	SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(70.0f, 50.0f));
	Collision_->SetPivot(float4(20.0f, -25.0f));

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
			}
		}
	}

	if (Distance.x < 10 || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			Renderer_->SetAlpha(0);
			Collision_->SetScale(float4(0.0f, 0.0f));
			SetState(AttackEffectState::None);
		}

	}
}

 