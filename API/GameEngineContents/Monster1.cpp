#include "Monster1.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"

Monster1::Monster1()
	: Monster()
{
}

Monster1::~Monster1()
{
}

void Monster1::Start()
{
	Monster::Start();

	Renderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 216, 219, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 475, 478, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "EatRight", 220, 232, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "EatLeft", 479, 491, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 233, 233, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 492, 492, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 233, 234, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 492, 493, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);

	Renderer_->ChangeAnimation("WalkRight");
	EatCol_ = CreateCollision("EatCol", float4(50.0f, 50.0f), float4(0.0f, 0.0f));
	AttackRangeCol_ = CreateCollision("AttackRangeCol", float4(100.0f, 50.0f), float4(0.0f, -25.0f));
	EatCol_->Off();
}

void Monster1::Render()
{
}

void Monster1::Update()
{
	UpdateAttack();
	UpdateMove();
	Die();
}

bool Monster1::CanWalk()
{
	if (false == CanMove_)
	{
		return false;
	}

	return Monster::CanWalk();
}

void Monster1::Walk()
{
	Monster::Walk();
	//AttackRenderer_->SetAlpha(0);
}

void Monster1::UpdateAttack()
{
	//if (Dir_.x == 1)
	//{
	//	EatCol_->On();
	//	EatCol_->SetScale(float4(100.0f, 50.0f));
	//	EatCol_->SetPivot(float4(50.0f, -20.0f));
	//}

	//if (Dir_ == "Left")
	//{
	//	KirbyEatCol_->On();
	//	KirbyEatCol_->SetScale(float4(100.0f, 50.0f));
	//	KirbyEatCol_->SetPivot(float4(-50.0f, -20.0f));
	//}

	//std::vector <GameEngineCollision*> ColResult;
	//if (true == KirbyEatCol_->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
	//{
	//	for (GameEngineCollision* Collision : ColResult)
	//	{
	//		GameEngineActor* Actor = Collision->GetActor();
	//		Monster_ = dynamic_cast<Monster*>(Actor);
	//		if (nullptr != Monster_)
	//		{
	//			float4 MonPos = GetPosition() - Monster_->GetPosition();
	//			if (MonPos.x > 0) // 내가 오른쪽
	//			{
	//				Monster_->SetMove(MonPos * GameEngineTime::GetDeltaTime() * 5);
	//			}
	//			if (MonPos.x < 0) // 내가 왼쪽 
	//			{
	//				Monster_->SetMove(MonPos * GameEngineTime::GetDeltaTime() * 5);
	//			}
	//		}
	//	}
	//}




	//if (true == Collision_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	//{
	//	return;
	//}

	//std::vector<GameEngineCollision*> Result;
	//if (AttackRangeCol_->CollisionResult("KirbyCol", Result, CollisionType::Rect, CollisionType::Rect))
	//{
	//	for (GameEngineCollision* Collision : Result)
	//	{
	//		Player* ColPlayer = dynamic_cast<Player*>(Collision->GetActor());
	//		SetPlayer(ColPlayer);
	//		if (ColPlayer != nullptr)
	//		{
	//			CanMove_ = false;
	//			float Distance = ColPlayer->GetPosition().x - GetPosition().x;
	//			if (Distance < 0)
	//			{
	//				Dir_ = float4::LEFT;
	//				Renderer_->ChangeAnimation("EatLeft");
	//				AttackCol_->On();
	//				AttackRenderer_->SetPivot(float4(-50.0f, 0.0f));
	//				AttackCol_->SetPivot(float4(-50.0f, 0.0f));
	//			}
	//			else
	//			{
	//				Dir_ = float4::RIGHT;
	//				Renderer_->ChangeAnimation("EatRight");
	//				AttackRenderer_->SetAlpha(255);
	//				AttackCol_->On();
	//				AttackRenderer_->SetPivot(float4(50.0f, 0.0f));
	//				AttackCol_->SetPivot(float4(50.0f, 0.0f));
	//			}
	//		}
	//	}
	//}

	//else
	//{
	//	AttackRenderer_->SetAlpha(0);
	//	CanMove_ = true;
	//}

	//std::vector<GameEngineCollision*> AttackResult;
	//if (AttackCol_->CollisionResult("KirbyCol", AttackResult, CollisionType::Rect, CollisionType::Rect))
	//{
	//	AttackTime_ += GameEngineTime::GetDeltaTime();
	//	for (GameEngineCollision* ColResult : AttackResult)
	//	{
	//		Player* ColPlayer = dynamic_cast<Player*>(ColResult->GetActor());
	//		SetPlayer(ColPlayer);
	//		if (ColPlayer != nullptr)
	//		{
	//			if (AttackTime_ > 1.0f)
	//			{
	//				AttackTime_ = 0.0f;
	//				ColPlayer->SetHP(ColPlayer->GetHP() - 1);
	//			}
	//		}
	//	}
	//}
}
