#include "AnimalEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

AnimalEffect::AnimalEffect()
{

}

AnimalEffect::~AnimalEffect()
{
}

void AnimalEffect::Start()
{
//	Collision_ = CreateCollision("AnimalCol", float4(50.0f, 50.0f), float4(50.0f, -25.0f));
//	Renderer_ = CreateRenderer("AnimalAtt.bmp");
//	Image_ = Renderer_->GetImage();
//	Image_->CutCount(6, 2);
//	Renderer_->CreateAnimation("AnimalAtt.bmp", "AttackRight", 0, 1, 0.1f, true);
//	Renderer_->CreateAnimation("AnimalAtt.bmp", "AttackLeft", 6, 7, 0.1f, true);
//	Renderer_->SetAlpha(0);
//
//	GameEngineLevel* Level = GetLevel();
//	ColMapImage_ = Level->GetColMapImage();
}

void AnimalEffect::Update()
{
//	StateUpdate();
}

//
void AnimalEffect::SetState(AnimalEffectState _AnimalEffectState)
{
//	AnimalEffectState_ = _AnimalEffectState;
//
//	switch (AnimalEffectState_)
//	{
//	case AnimalEffectState::AnimalEffectRight:
//		//Renderer_->ChangeAnimation("AttackRight");
//		break;
//	case AnimalEffectState::AnimalEffectLeft:
//		//Renderer_->ChangeAnimation("AttackLeft");
//		break;
//	}
}

AnimalEffectState AnimalEffect::GetState()
{
	return AnimalEffectState_;
}

void AnimalEffect::StateUpdate()
{
//	switch (AnimalEffectState_)
//	{
//	case AnimalEffectState::AnimalEffectRight:
//		UpdateAnimalEffectRight();
//		break;
//	case AnimalEffectState::AnimalEffectLeft:
//		UpdateAnimalEffectLeft();
//		break;
//	case AnimalEffectState::None:
//		UpdateNone();
//		break;
//	}
}

void AnimalEffect::UpdateNone()
{
//	Collision_->Off();
}

void AnimalEffect::UpdateAnimalEffectRight()
{
//	Collision_->SetPivot(float4(100.0f, -25.0f));
//
//	std::vector<GameEngineCollision*> Result;
//	if (true == Collision_->CollisionResult("BasicMonster", Result, CollisionType::Rect, CollisionType::Rect))
//	{
//		for (GameEngineCollision* Collision : Result)
//		{
//			GameEngineActor* ColActor = Collision->GetActor();
//			Monster* Monster_ = dynamic_cast<Monster*>(ColActor);
//			if (Monster_ != nullptr)
//			{
//				Monster_->SetHP(Monster_->GetHP() - 1);
//				Monster_->SetDir(float4::ZERO);
//			}
//		}
//	}
//
//	SetState(AnimalEffectState::None);
}

void AnimalEffect::UpdateAnimalEffectLeft()
{
//	Collision_->SetPivot(float4(-100.0f, -25.0f));
//
//
//	std::vector<GameEngineCollision*> Result;
//	if (true == Collision_->CollisionResult("BasicMonster", Result, CollisionType::Rect, CollisionType::Rect))
//	{
//		for (GameEngineCollision* Collision : Result)
//		{
//			GameEngineActor* ColActor = Collision->GetActor();
//			Monster* Monster_ = dynamic_cast<Monster*>(ColActor);
//			if (Monster_ != nullptr)
//			{
//				Monster_->SetHP(Monster_->GetHP() - 1);
//				Monster_->SetDir(float4::ZERO);
//				Monster_->RightDirCol_->Off();
//				Monster_->LeftDirCol_->Off();
//			}
//		}
//	}
//
//	SetState(AnimalEffectState::None);
}

void AnimalEffect::Render()
{
}