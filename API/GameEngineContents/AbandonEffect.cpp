#include "AbandonEffect.h"
#include "Player.h"
#include "Monster.h"
#include <GameEngine/GameEngineLevel.h>
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
	, MonsterClass_(MonsterClass::NONE)
	, Time_(0.0f)
{

}

AbandonEffect::~AbandonEffect()
{
}

void AbandonEffect::Start()
{
	Collision_ = CreateCollision("AbandonEffect", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	Renderer_ = CreateRenderer("AttackEffect.bmp");
	Renderer_->SetAlpha(0);
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(8, 2);
	Renderer_->CreateAnimation("AttackEffect.bmp", "Idle", 0, 3, 0.1f, true);
	Renderer_->CreateAnimation("AttackEffect.bmp", "Abandon", 4, 14, 0.1f, false);

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
	case AbandonEffectState::Left:
	case AbandonEffectState::Right:
		Renderer_->ChangeAnimation("Idle");
		break;
	case AbandonEffectState::None:
		Renderer_->ChangeAnimation("Abandon");
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
	case AbandonEffectState::Right:
		UpdateAbandonEffectRight();
		break;
	case AbandonEffectState::Left:
		UpdateAbandonEffectLeft();
		break;
	case AbandonEffectState::Eaten:
		UpdateEaten();
		break;
	case AbandonEffectState::None:
		UpdateNone();
		break;
	}
}

void AbandonEffect::UpdateAbandonEffectRight()
{
	Time_ += GameEngineTime::GetDeltaTime();
	Renderer_->SetAlpha(255);
	
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(50.0f, 40.0f));
	Collision_->On();
	Renderer_->On();

	if (Time_ > 5.0f)
	{
		SetState(AbandonEffectState::None);
	}

	/*if (Distance.x > 10 || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			SetState(AbandonEffectState::None);
		}

	}*/
}

void AbandonEffect::UpdateAbandonEffectLeft()
{
	Time_ += GameEngineTime::GetDeltaTime();
	Renderer_->SetAlpha(255);
	SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(50.0f, 40.0f));
	Collision_->On();
	Renderer_->On();

	if (Time_ > 5.0f)
	{
		SetState(AbandonEffectState::None);
	}

	/*if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			SetState(AbandonEffectState::None);
		}
	}*/
}

void AbandonEffect::UpdateEaten()
{
	Time_ = 0;
}

void AbandonEffect::UpdateNone()
{
	if (Time_ > 5.0)
	{
		Collision_->Off();
		Renderer_->ChangeAnimation("Abandon");
		Renderer_->Off();
		Time_ = 0;
	}
}