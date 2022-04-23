#include "SparkAttackEffect.h"
#include "Monster.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <vector>

SparkAttackEffect::SparkAttackEffect()
{

}

SparkAttackEffect::~SparkAttackEffect()
{
}

void SparkAttackEffect::Start()
{
	//Collision_ = CreateCollision("SparkAttackCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	//Renderer_ = CreateRenderer("SparkAtt.bmp");
	//Renderer_->SetAlpha(0);
	//Image_ = Renderer_->GetImage();
	//Image_->CutCount(, );
	//Renderer_->CreateAnimation("SparkAtt.bmp", "Attack", 0, 12, 0.03f, true);

	//GameEngineLevel* Level = GetLevel();
	//ColMapImage_ = Level->GetColMapImage();

	//SetState(SparkAttackEffectState::None);
}

void SparkAttackEffect::Update()
{
	//StateUpdate();
}

void SparkAttackEffect::Render()
{
}

void SparkAttackEffect::SetState(SparkAttackEffectState _SparkAttackEffectState)
{
	SparkAttackEffectState_ = _SparkAttackEffectState;

	//switch (SparkAttackEffectState_)
	//{
	//case SparkAttackEffectState::SparkAttackEffect:
	//	Renderer_->ChangeAnimation("Attack");
	//	StartPos_ = GetPosition();
	//	break;
	//case SparkAttackEffectState::None:
	//	Renderer_->SetAlpha(0);
	//	Renderer_->SetPivot(float4(0.0f, 0.0f));
	//	break;
	//}
}

SparkAttackEffectState SparkAttackEffect::GetState()
{
	return SparkAttackEffectState_;
}

void SparkAttackEffect::StateUpdate()
{
	//switch (SparkAttackEffectState_)
	//{
	//case SparkAttackEffectState::SparkAttackEffect:
	//	UpdateSparkAttackEffect();
	//	break;
	//case SparkAttackEffectState::None:
	//	UpdateNone();
	//	break;
	//}
}

void SparkAttackEffect::UpdateNone()
{
}

void SparkAttackEffect::UpdateSparkAttackEffect()
{
	//Renderer_->SetAlpha(255);
	//Renderer_->SetPivot(float4(40.0f, 0.0f));
	//SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 100);
	//Collision_->SetScale(float4(150.0f, 150.0f));
	//Collision_->SetPivot(float4(0.0f, -75.0f));

	//std::vector<GameEngineCollision*> SparkResult;
	//if (true == Collision_->CollisionResult("BasicMonster", SparkResult, CollisionType::Rect, CollisionType::Rect))
	//{
	//	for (GameEngineCollision* SparkCollision : SparkResult)
	//	{
	//		GameEngineActor* SparkColActor = SparkCollision->GetActor();
	//		Monster* Monster_ = dynamic_cast<Monster*>(SparkColActor);
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
