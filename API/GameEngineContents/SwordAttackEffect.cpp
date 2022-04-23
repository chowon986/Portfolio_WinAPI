#include "SwordAttackEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

SwordAttackEffect::SwordAttackEffect()
{

}

SwordAttackEffect::~SwordAttackEffect()
{
}

void SwordAttackEffect::Start()
{
	//Collision_ = CreateCollision("SwordAttackCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	//Renderer_ = CreateRenderer("SwordAtt.bmp");
	//Renderer_->SetAlpha(0);
	//Image_ = Renderer_->GetImage();
	//Image_->CutCount(, );
	//Renderer_->CreateAnimation("SwordAtt.bmp", "Attack", 0, 12, 0.03f, true);

	//GameEngineLevel* Level = GetLevel();
	//ColMapImage_ = Level->GetColMapImage();

	//SetState(SwordAttackEffectState::None);
}

void SwordAttackEffect::Update()
{
	//StateUpdate();
}

void SwordAttackEffect::Render()
{
}

void SwordAttackEffect::SetState(SwordAttackEffectState _SwordAttackEffectState)
{
	SwordAttackEffectState_ = _SwordAttackEffectState;

	// need to chk
	//switch (SwordAttackEffectState_)
	//{
	//case SwordAttackEffectState::SwordAttackEffect:
	//	Renderer_->ChangeAnimation("Attack");
	//	StartPos_ = GetPosition();
	//	break;
	// 	//case SwordAttackEffectState::SwordJumpAttackEffect:
	//	Renderer_->ChangeAnimation("Attack");
	//	StartPos_ = GetPosition();
	//	break;
	//case SwordAttackEffectState::None:
	//	Renderer_->SetAlpha(0);
	//	Renderer_->SetPivot(float4(0.0f, 0.0f));
	//	break;
	//}
}

SwordAttackEffectState SwordAttackEffect::GetState()
{
	return SwordAttackEffectState_;
}

void SwordAttackEffect::StateUpdate()
{
	//switch (SwordAttackEffectState_)
	//{
	//case SwordAttackEffectState::SwordAttackEffect:
	//	UpdateSwordAttackEffect();
	//	break;
	// 	//case SwordAttackEffectState::SwordJumpAttackEffect:
	//	UpdateSwordJumpAttackEffect();
	//	break;
	//case SwordAttackEffectState::None:
	//	UpdateNone();
	//	break;
	//}
}

void SwordAttackEffect::UpdateNone()
{
}

void SwordAttackEffect::UpdateSwordAttackEffect()
{
	//Renderer_->SetAlpha(255);
	//Renderer_->SetPivot(float4(40.0f, 0.0f));
	//SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 100);
	//Collision_->SetScale(float4(150.0f, 150.0f));
	//Collision_->SetPivot(float4(0.0f, -75.0f));

	//std::vector<GameEngineCollision*> SwordResult;
	//if (true == Collision_->CollisionResult("BasicMonster", SwordResult, CollisionType::Rect, CollisionType::Rect))
	//{
	//	for (GameEngineCollision* SwordCollision : SwordResult)
	//	{
	//		GameEngineActor* SwordColActor = SwordCollision->GetActor();
	//		Monster* Monster_ = dynamic_cast<Monster*>(SwordColActor);
	//		if (Monster_ != nullptr)
	//		{
	//			Monster_->SetDir(float4::ZERO);
	//			Monster_->RightDirCol_->SetScale(float4(0.0f, 0.0f));
	//			Monster_->RightDirCol_->SetPivot(float4(0.0f, 200.0f));
	//			Monster_->LeftDirCol_->SetScale(float4(0.0f, 0.0f));
	//			Monster_->LeftDirCol_->SetPivot(float4(0.0f, 200.0f));
	//			Monster_->SetHP(Monster_->GetHP() - 1);
	//		}
	//	}
	//}
}

void SwordAttackEffect::UpdateSwordJumpAttackEffect()
{
}
