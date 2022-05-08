#include "Monster1.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"

Monster1::Monster1()
	: Monster()
	, EatTime_(2.0f)
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
	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 216, 219, 0.2f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 475, 478, 0.2f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "EatStartRight", 220, 221, 0.1f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "EatStartLeft", 479, 480, 0.1f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "EatRight", 222, 232, 0.1f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "EatLeft", 479, 491, 0.1f, true);

	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 233, 233, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 492, 492, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 233, 234, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 492, 493, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);

	Renderer_->ChangeAnimation("WalkRight");
	EatRangeCol_ = CreateCollision("EatRangeCol", float4(100.0f, 50.0f), float4(0.0f, 0.0f));
	EatCol_ = CreateCollision("EatCol", float4(30.0f, 50.0f), float4(0.0f, -30.0f));
	EatRangeCol_->Off();

}

void Monster1::Render()
{
}

void Monster1::DelayUpdate()
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
}

void Monster1::UpdateAttack()
{
	EatTime_ += GameEngineTime::GetDeltaTime();
	if (true == Collision_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	{
		return;
	}


	if (Dir_.x == 1 && true != Renderer_->IsAnimationName("EatRight"))
	{
		EatRangeCol_->On();
		EatRangeCol_->SetPivot(float4(50.0f, -20.0f));
		if (true == Renderer_->IsAnimationName("EatStartRight") && Player_->GetKirbyClass() == KirbyClass::DEFAULT)
		{
			Player_->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * GetSpeed() * 10);
		}
	}

	if (Dir_.x == -1 && true != Renderer_->IsAnimationName("EatLeft"))
	{
		EatRangeCol_->On();
		EatRangeCol_->SetPivot(float4(-50.0f, -20.0f));
		if (true == Renderer_->IsAnimationName("EatStartLeft") && Player_->GetKirbyClass() == KirbyClass::DEFAULT)
		{
			Player_->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * GetSpeed() * 10);
		}
	}

	if ((true == Renderer_->IsAnimationName("EatRight") ||
		true == Renderer_->IsAnimationName("EatLeft")) &&
		true == Renderer_->IsEndAnimation())
	{
		EatTime_ = 0.0f;
		Player_->SetState(KirbyState::IDLE);
		CanMove_ = true;
	}

	if (EatTime_ < 1.0f)
	{
		if (Player_->GetState() != KirbyState::DIE)
		{
			if (Dir_.x == 1)
			{
				Player_->SetMove(float4::LEFT* GameEngineTime::GetDeltaTime() * 50);
				EatRangeCol_->Off();
			}
			else
			{
				Player_->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 50);
				EatRangeCol_->Off();
			}
		}
	}

	std::vector <GameEngineCollision*> EatColResult;
	std::vector <GameEngineCollision*> ColResult;
	if (true == EatCol_->CollisionResult("KirbyCol", EatColResult, CollisionType::Rect, CollisionType::Rect) &&
		EatTime_ > 2.0f)
	{
		for (GameEngineCollision* Collision : EatColResult)
		{
			GameEngineActor* Actor = Collision->GetActor();
			Player* ColPlayer = dynamic_cast<Player*>(Actor);
			SetPlayer(ColPlayer);
			if (nullptr != ColPlayer)
			{
				ColPlayer->SetState(KirbyState::EATEN);
				if (Dir_.x == 1)
				{
					Renderer_->ChangeAnimation("EatRight");
					CanMove_ = false;
				}
				else
				{
					Renderer_->ChangeAnimation("EatLeft");
					CanMove_ = false;
				}
			}
		}
	}

	else if (true == EatRangeCol_->CollisionResult("KirbyCol", ColResult, CollisionType::Rect, CollisionType::Rect) &&
			 EatTime_ > 2.0f)
	{
		for (GameEngineCollision* Collision : ColResult)
		{
			GameEngineActor* Actor = Collision->GetActor();
			Player* ColPlayer = dynamic_cast<Player*>(Actor);
			SetPlayer(ColPlayer);
			if (nullptr != ColPlayer)
			{
				float4 MonPos = ColPlayer->GetPosition() - GetPosition();
				if (MonPos.x < 0 && ColPlayer->GetKirbyClass() == KirbyClass::DEFAULT)
				{
					Renderer_->ChangeAnimation("EatStartLeft");
					CanMove_ = false;
					Collision_->Off();
				}
				else if (MonPos.x > 0 && ColPlayer->GetKirbyClass() == KirbyClass::DEFAULT)
				{
					Renderer_->ChangeAnimation("EatStartRight");
					CanMove_ = false;
					Collision_->Off();
				}
				else
				{
					return;
				}
			}
		}
	}

	else
	{
		CanMove_ = true;
		Collision_->On();
	}
}

void Monster1::UpdateMove()
{
	Monster::UpdateMove();

	std::vector<GameEngineCollision*> ColResult;
	while (true == Collision_->CollisionResult("Obstruction", ColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* BoxCollision : ColResult)
		{
			GameEngineActor* CollisionActor = BoxCollision->GetActor();
			if (CollisionActor != nullptr)
			{
				float XDir = CollisionActor->GetPosition().x - GetPosition().x;
				float YDir = CollisionActor->GetPosition().y - GetPosition().y;

				if (YDir > 0)
				{
					SetMove(float4::UP);
				}
				else if (XDir <= 0)
				{
					SetMove(float4::RIGHT);
					Dir_ = float4::RIGHT;
				}

				else if (XDir > 0)
				{
					SetMove(float4::LEFT);
					Dir_ = float4::LEFT;
				}

				else if (YDir <= 0)
				{
					SetMove(float4::DOWN);
				}
			}
		}
	}
}

