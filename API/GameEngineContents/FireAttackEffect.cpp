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
	Collision_ = CreateCollision("FireAttackCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	Renderer_ = CreateRenderer("FireAtt.bmp");
	Renderer_->SetAlpha(0);
	Image_ = Renderer_->GetImage();
	Image_->CutCount(5, 3);
	Renderer_->CreateAnimation("FireAtt.bmp", "AttackRight", 0, 12, 0.03f, true);
	Renderer_->CreateAnimation("FireAtt.bmp", "AttackLeft", 0, 12, 0.03f, true);

	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(FireAttackEffectState::None);
}

void FireAttackEffect::Update()
{
	StateUpdate();
}

void FireAttackEffect::Render()
{
}

void FireAttackEffect::SetState(FireAttackEffectState _FireAttackEffectState)
{
	FireAttackEffectState_ = _FireAttackEffectState;

	switch (FireAttackEffectState_)
	{
	case FireAttackEffectState::FireAttackEffectRight:
		Renderer_->ChangeAnimation("AttackRight");
		StartPos_ = GetPosition();
		break;
	case FireAttackEffectState::FireAttackEffectLeft:
		Renderer_->ChangeAnimation("AttackLeft");
		StartPos_ = GetPosition();
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
}

void FireAttackEffect::UpdateFireAttackEffectRight()
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
			SetState(FireAttackEffectState::None);
		}

	}
}

void FireAttackEffect::UpdateFireAttackEffectLeft()
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
			SetState(FireAttackEffectState::None);
		}

	}

	std::vector<GameEngineCollision*> FireResult;
	if (true == Collision_->CollisionResult("BasicMonster", FireResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* FireCollision : FireResult)
		{
			GameEngineActor* FireColActor = FireCollision->GetActor();
			Monster* Monster_ = dynamic_cast<Monster*>(FireColActor);
			if (Monster_ != nullptr)
			{
				Renderer_->ChangeAnimation("Fire");
				Monster_->SetDir(float4::ZERO);
				Monster_->RightDirCol_->SetScale(float4(0.0f, 0.0f));
				Monster_->RightDirCol_->SetPivot(float4(0.0f, 200.0f));
				Monster_->LeftDirCol_->SetScale(float4(0.0f, 0.0f));
				Monster_->LeftDirCol_->SetPivot(float4(0.0f, 200.0f));
				Monster_->SetHP(Monster_->GetHP() - 1);
			}
		}
	}
}

