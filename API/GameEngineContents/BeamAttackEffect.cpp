#include "BeamAttackEffect.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

BeamAttackEffect::BeamAttackEffect()
{

}

BeamAttackEffect::~BeamAttackEffect()
{
}

void BeamAttackEffect::Start()
{
	{
	    //CollisionOne_ = CreateCollision(/*"BeamAttackCol"*/, float4(0.0f, 0.0f), float4(0.0f, 0.0f));
		//CollisionTwo_ = CreateCollision(/*"BeamAttackCol"*/, float4(0.0f, 0.0f), float4(0.0f, 0.0f));
		//CollisionThree_ = CreateCollision(/*"BeamAttackCol"*/, float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	}

	{
	//GameEngineLevel* Level = GetLevel();
	//ColMapImage_ = Level->GetColMapImage();
	}

	{
	//SetState(BeamAttackEffectState::None);
	}
}

void BeamAttackEffect::Update()
{
	//StateUpdate();
}

void BeamAttackEffect::Render()
{
}

void BeamAttackEffect::SetState(BeamAttackEffectState _BeamAttackEffectState)
{
	BeamAttackEffectState_ = _BeamAttackEffectState;

	//switch (BeamAttackEffectState_)
	//{
	//case BeamAttackEffectState::BeamRightAttackEffect:
	//case BeamAttackEffectState::BeamLeftAttackEffect:
    //StartPos_ = GetPosition() + float4(/*,*/); // Actor의 위치 + float4 값을 시작 위치로 설정
	//	break;
	//case BeamAttackEffectState::None:
	//	break;
	//}
}

BeamAttackEffectState BeamAttackEffect::GetState()
{
	return BeamAttackEffectState_;
}

void BeamAttackEffect::StateUpdate()
{
	//switch (BeamAttackEffectState_)
	//{
	//  case BeamAttackEffectState::BeamRightAttackEffect:
	//	UpdateBeamRightAttackEffect();
	//	break;
	// 	case BeamAttackEffectState::BeamLeftAttackEffect:
	//	UpdateBeamLeftAttackEffect();
	//	break;
	//  case BeamAttackEffectState::None:
	//	UpdateNone();
	//	break;
	//}
}

void BeamAttackEffect::UpdateBeamRightAttackEffect()
{
// 	CollisionOne_->SetScale(float4(50.0f, 50.0f));
// 	CollisionTwo_->SetScale(float4(50.0f, 50.0f));
// 	CollisionThree_->SetScale(float4(50.0f, 50.0f));


// 오른쪽으로 이동
// RendererTwo_->SetPivot(RendererTwo_->GetPivot() float4::RIGHT * GameEngineTime::GetDeltaTime() * 100);
// 위로 이동
// RendererTwo_->SetPivot(RendererTwo_->GetPivot() float4::UP * GameEngineTime::GetDeltaTime() * 100);

	//float4 Distance = GetPosition() - StartPos();
	//if(Distance.y > -10)
	//{
		// SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 100);
	//}
	// if(Distance.y  -50)
	//{
		// SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 100);
	//}
	// if (Distance.




//std::vector<GameEngineCollision*> BeamResult;
//if (true == CollisionOne_->CollisionResult("BasicMonster", BeamResult, CollisionType::Rect, CollisionType::Rect)
// || true == CollisionTwo_->CollisionResult("BasicMonster", BeamResult, CollisionType::Rect, CollisionType::Rect)
//{
//	for (GameEngineCollision* BeamCollision : BeamResult)
//	{
//		GameEngineActor* BeamColActor = BeamCollision->GetActor();
//		Monster* Monster_ = dynamic_cast<Monster*>(BeamColActor);
//		if (Monster_ != nullptr)
//		{
//			Monster_->RightDirCol_->SetScale(float4(0.0f, 0.0f));
//			Monster_->RightDirCol_->SetPivot(float4(0.0f, 1000.0f));
// 
//			Monster_->LeftDirCol_->SetScale(float4(0.0f, 0.0f));
//			Monster_->LeftDirCol_->SetPivot(float4(0.0f, 1000.0f));
//			Monster_->SetHP(Monster_->GetHP() - 2);
//		}
//	}
//}
}

void BeamAttackEffect::UpdateBeamLeftAttackEffect()
{
	//	RendererOne_->SetAlpha(255);
	//  RendererOne_->SetScale(float4(/*0.0f, 0.0f*/));
	//	RendererOne_->SetPivot(float4(/*0.0f, 0.0f*/));
	// 	CollisionOne_->SetScale(float4(50.0f, 50.0f));

	//	RendererTwo_->SetAlpha(255);
	//  RendererTwo_->SetScale(float4(/*0.0f, 0.0f*/));
	//	RendererTwo_->SetPivot(float4(/*0.0f, 0.0f*/));
	// 	CollisionTwo_->SetScale(float4(50.0f, 50.0f));

//std::vector<GameEngineCollision*> BeamResult;
//if (true == CollisionOne_->CollisionResult("BasicMonster", BeamResult, CollisionType::Rect, CollisionType::Rect)
// || true == CollisionTwo_->CollisionResult("BasicMonster", BeamResult, CollisionType::Rect, CollisionType::Rect)
//{
//	for (GameEngineCollision* BeamCollision : BeamResult)
//	{
//		GameEngineActor* BeamColActor = BeamCollision->GetActor();
//		Monster* Monster_ = dynamic_cast<Monster*>(BeamColActor);
//		if (Monster_ != nullptr)
//		{
// 			// 몬스터 DirCol 삭제
//			Monster_->RightDirCol_->SetScale(float4(0.0f, 0.0f));
//			Monster_->RightDirCol_->SetPivot(float4(0.0f, 1000.0f));
// 
//			Monster_->LeftDirCol_->SetScale(float4(0.0f, 0.0f));
//			Monster_->LeftDirCol_->SetPivot(float4(0.0f, 1000.0f));
//			Monster_->SetHP(Monster_->GetHP() - 2);
//		}
//	}
//}
}


void BeamAttackEffect::UpdateNone()
{

}
