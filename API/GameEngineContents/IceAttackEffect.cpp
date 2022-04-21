#include "IceAttackEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

IceAttackEffect::IceAttackEffect()
{

}

IceAttackEffect::~IceAttackEffect()
{
}

void IceAttackEffect::Start()
{
	Collision_ = CreateCollision("IceAttackCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	Renderer_ = CreateRenderer("IceAtt.bmp");
	Renderer_->SetAlpha(0);
	Image_ = Renderer_->GetImage();
	Image_->CutCount(5, 3);
	Renderer_->CreateAnimation("IceAtt.bmp", "AttackRight", 0, 12, 0.03f, true);
	Renderer_->CreateAnimation("IceAtt.bmp", "AttackLeft", 0, 12, 0.03f, true);

	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(IceAttackEffectState::None);
}

void IceAttackEffect::Update()
{
	StateUpdate();
}

void IceAttackEffect::Render()
{
}

void IceAttackEffect::SetState(IceAttackEffectState _IceAttackEffectState)
{
	IceAttackEffectState_ = _IceAttackEffectState;

	switch (IceAttackEffectState_)
	{
	case IceAttackEffectState::IceAttackEffectRight:
		Renderer_->ChangeAnimation("AttackRight");
		StartPos_ = GetPosition();
		break;
	case IceAttackEffectState::IceAttackEffectLeft:
		Renderer_->ChangeAnimation("AttackLeft");
		StartPos_ = GetPosition();
		break;
	}
}

IceAttackEffectState IceAttackEffect::GetState()
{
	return IceAttackEffectState_;
}

void IceAttackEffect::StateUpdate()
{
	switch (IceAttackEffectState_)
	{
	case IceAttackEffectState::IceAttackEffectRight:
		UpdateIceAttackEffectRight();
		break;
	case IceAttackEffectState::IceAttackEffectLeft:
		UpdateIceAttackEffectLeft();
		break;
	case IceAttackEffectState::None:
		UpdateNone();
		break;
	}
}

void IceAttackEffect::UpdateNone()
{
}

void IceAttackEffect::UpdateIceAttackEffectRight()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(40.0f, 0.0f));
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(150.0f, 50.0f));
	Collision_->SetPivot(float4(100.0f, -25.0f));

	float4 Distance = GetPosition() - StartPos_;

	if (Distance.x > 10 || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			Renderer_->SetAlpha(0);
			Collision_->SetScale(float4(0.0f, 0.0f));
			SetState(IceAttackEffectState::None);
		}

	}
}

void IceAttackEffect::UpdateIceAttackEffectLeft()
{
	Renderer_->SetAlpha(255);
	Renderer_->SetPivot(float4(-40.0f, 0.0f));
	SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 100);
	Collision_->SetScale(float4(150.0f, 50.0f));
	Collision_->SetPivot(float4(-70.0f, -25.0f));

	float4 Distance = GetPosition() - StartPos_;

	//std::vector<GameEngineCollision*> Result;
	//if (true == Collision_->CollisionResult("BasicMonster", Result, CollisionType::Rect, CollisionType::Rect))
	//{
	//	for (GameEngineCollision* Collision : Result)
	//	{
	//		GameEngineActor* ColActor = Collision->GetActor();
	//		Monster* Monster_ = dynamic_cast<Monster*>(ColActor);
	//		if (Monster_ != nullptr)
	//		{
	//			Monster_->SetHP(Monster_->GetHP() - 1);
	//		}
	//	}
	//}

	if (Distance.x < 10 || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			Renderer_->SetAlpha(0);
			Collision_->SetScale(float4(0.0f, 0.0f));
			SetState(IceAttackEffectState::None);
		}

	}
}

