#include "StarAttackEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>
#include "MonBotUI.h"

StarAttackEffect::StarAttackEffect()
	:ColMapImage_(nullptr)
	,Collision_(nullptr)
	,Renderer_(nullptr)
	,StarAttackEffectState_(StarAttackEffectState::None)
{
	
}

StarAttackEffect::~StarAttackEffect()
{
}

void StarAttackEffect::Start()
{
	Collision_ = CreateCollision("AttackCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	Renderer_ = CreateRenderer("AttackEffect.bmp");
	Renderer_->SetAlpha(0);
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(8, 2);
	Renderer_->CreateAnimation("AttackEffect.bmp", "AttackStart", 0, 3, 0.1f, true);
	Renderer_->CreateAnimation("AttackEffect.bmp", "AttackEnd", 4, 14, 0.1f, false);

	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(StarAttackEffectState::None);
}

void StarAttackEffect::Update()
{
	StateUpdate();
}

void StarAttackEffect::Render()
{
}

void StarAttackEffect::SetState(StarAttackEffectState _StarAttackEffectState)
{
	StarAttackEffectState_ = _StarAttackEffectState;
	
	switch (StarAttackEffectState_)
	{
	case StarAttackEffectState::AttackStartRight:
	case StarAttackEffectState::AttackStartLeft:
		Renderer_->ChangeAnimation("AttackStart");
		StartPos_ = GetPosition();
		break;
	case StarAttackEffectState::AttackEndRight:
	case StarAttackEffectState::AttackEndLeft:
		Renderer_->ChangeAnimation("AttackEnd");
		break;
	}
}

StarAttackEffectState StarAttackEffect::GetState()
{
	return StarAttackEffectState_;
}

void StarAttackEffect::StateUpdate()
{
	switch (StarAttackEffectState_)
	{
	case StarAttackEffectState::AttackStartRight:
		UpdateAttackStartRight();
		break;
	case StarAttackEffectState::AttackStartLeft:
		UpdateAttackStartLeft();
		break;
	case StarAttackEffectState::AttackEndRight:
		UpdateAttackEndRight();
		break;
	case StarAttackEffectState::AttackEndLeft:
		UpdateAttackEndLeft();
		break;
	case StarAttackEffectState::None:
		UpdateNone();
		break;
	}
}

void StarAttackEffect::UpdateAttackStartRight()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(20.0f, 0.0f));
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(50.0f,40.0f));
	Collision_->SetPivot(float4(20.0f, -30.0f));

	float4 Distance = GetPosition() - StartPos_;

	if (Distance.x > 230)
	{
		SetState(StarAttackEffectState::AttackEndRight);
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		SetState(StarAttackEffectState::AttackEndRight);
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
				Monster_->GetUI()->On();
				Monster_->SetHP(Monster_->GetHP() - 1);
				SetState(StarAttackEffectState::AttackEndRight);
			}
		}
	}
}

void StarAttackEffect::UpdateAttackStartLeft()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(-20.0f, 0.0f));
	SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(50.0f, 40.0f));
	Collision_->SetPivot(float4(-20.0f, -30.0f));
	
	float4 Distance = GetPosition() - StartPos_;
	if (Distance.x < -230)
	{
		SetState(StarAttackEffectState::AttackEndLeft);
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		SetState(StarAttackEffectState::AttackEndLeft);
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
				Monster_->GetUI()->On();
				Monster_->SetHP(Monster_->GetHP() - 1);
				SetState(StarAttackEffectState::AttackEndRight);
			}
		}
	}

}

void StarAttackEffect::UpdateAttackEndRight()
{
	if (true == Renderer_->IsEndAnimation())
	{
		Renderer_->SetAlpha(0);
		Collision_->SetScale(float4(0.0f, 0.0f));
		SetState(StarAttackEffectState::None);
	}
}

void StarAttackEffect::UpdateAttackEndLeft()
{
	if (true == Renderer_->IsEndAnimation())
	{
		Renderer_->SetAlpha(0);
		Collision_->SetScale(float4(0.0f, 0.0f));
		SetState(StarAttackEffectState::None);
	}
}

void StarAttackEffect::UpdateNone()
{
}
