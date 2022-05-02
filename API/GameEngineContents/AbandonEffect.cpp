#include "AbandonEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

AbandonEffect::AbandonEffect()
	: AbandonEffectState_(AbandonEffectState::None)
	, StartPos_()
	, ColMapImage_(nullptr)
	, Renderer_(nullptr)
	, Collision_(nullptr)
	, Image_(nullptr)
{

}

AbandonEffect::~AbandonEffect()
{
}

void AbandonEffect::Start()
{
	Collision_ = CreateCollision("AbandonEffect", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	Renderer_ = CreateRenderer("Attack.bmp");
	Image_ = Renderer_->GetImage();
	Image_->CutCount(10, 4);
	Renderer_->CreateAnimation("Attack.bmp", "AttackRight", 0, 12, 0.03f, true);
	Renderer_->CreateAnimation("Attack.bmp", "AttackLeft", 20, 32, 0.03f, true);
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(AbandonEffectState::None);
}

void AbandonEffect::Update()
{
	StateUpdate();
}

void AbandonEffect::Render()
{
}

void AbandonEffect::SetState(AbandonEffectState _AbandonEffectState)
{
	AbandonEffectState_ = _AbandonEffectState;

	switch (AbandonEffectState_)
	{
	case AbandonEffectState::Abandon:
		Renderer_->ChangeAnimation("Abandon");
		StartPos_ = GetPosition();
		break;
	case AbandonEffectState::None:
		break;
	}
}

AbandonEffectState AbandonEffect::GetState()
{
	return AbandonEffectState_;
}

void AbandonEffect::StateUpdate()
{
	switch (AbandonEffectState_)
	{
	case AbandonEffectState::Abandon:
		UpdateAbandonEffectRight();
		break;
	case AbandonEffectState::None:
		UpdateNone();
		break;
	}
}

void AbandonEffect::UpdateAbandonEffectRight()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(-40.0f, 0.0f));
	// 위로 갔다가 부딪히면 아래로
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(70.0f, 50.0f));
	Collision_->SetPivot(float4(20.0f, -25.0f));
	Collision_->On();

	float4 Distance = GetPosition() - StartPos_;

	// need to chk
	std::vector<GameEngineCollision*> Result;
	if (true == Collision_->CollisionResult("KirbyEatCol", Result, CollisionType::Rect, CollisionType::Rect))
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
			SetState(AbandonEffectState::None);
		}

	}
}

void AbandonEffect::UpdateAbandonEffectLeft()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(-150.0f, 0.0f));
	SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(70.0f, 50.0f));
	Collision_->SetPivot(float4(-20.0f, -25.0f));
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
			}
		}
	}

	if (Distance.x < -10 || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			SetState(AbandonEffectState::None);
		}
	}
}

void AbandonEffect::UpdateNone()
{
	Renderer_->SetAlpha(0);
	Collision_->Off();
}