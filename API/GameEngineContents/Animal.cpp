#include "Animal.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "FireAttackEffect.h"
#include "IceAttackEffect.h"
#include "SparkAttackEffect.h"
#include "Player.h"

Animal::Animal()
	: Monster()
{
	SetMonsterClass(MonsterClass::ANIMAL);
}

Animal::~Animal()
{
}


void Animal::DelayUpdate()
{
	UpdateMove();
	Die();
}

void Animal::Start()
{
	Monster::Start();

	Renderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("Monster1.bmp", "IdleRight", 40, 43, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "IdleLeft", 299, 302, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 81, 82, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 81, 81, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 340, 341, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 340, 340, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);
	Renderer_->ChangeAnimation("IdleLeft");

	Dir_ = float4::ZERO;
}

void Animal::UpdateMove()
{
	std::vector<GameEngineCollision*> CenterColResult;
	if (Collision_->CollisionResult("KirbyCol", CenterColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* CenterCol : CenterColResult)
		{
			Player* ColPlayer = dynamic_cast<Player*>(CenterCol->GetActor());
			SetPlayer(ColPlayer);
			if (ColPlayer != nullptr)
			{
				float MoveDir = ColPlayer->GetPosition().x - GetPosition().x;
				if (MoveDir <= 0) // 몬스터가 오른쪽
				{
					if (true != Renderer_->IsAnimationName("Ice"))
					{
						Renderer_->ChangeAnimation("CollisionRight");
					}
				}
				else
				{
					if (true != Renderer_->IsAnimationName("Ice"))
					{
						Renderer_->ChangeAnimation("CollisionLeft");
					}
				}
			}
		}
	}

	if (true == IceEndCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect))
	{
		Death();
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(10.0f, 0.0f)) || (GetPosition().x > GetLevel()->GetMapSizeX() - 1))
	{
		if (true == Renderer_->IsAnimationName("Ice"))
		{
			Death();
		}
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-10.0f, 0.0f)) || GetPosition().x < 0)
	{
		if (true == Renderer_->IsAnimationName("Ice"))
		{
			Death();
		}
	}

	std::vector<GameEngineCollision*> SlideColResult;
	if (true == Collision_->CollisionResult("KirbySlideCol", SlideColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : SlideColResult)
		{
			Player* ColPlayer = dynamic_cast<Player*>(Collision->GetActor());
			if (ColPlayer != nullptr)
			{
				float Direction = ColPlayer->GetPosition().x - GetPosition().x;
				if (Direction <= 0) // 몬스터가 오른쪽
				{
					Renderer_->ChangeAnimation("CollisionRight");
				}

				else // 몬스터가 왼쪽
				{
					Renderer_->ChangeAnimation("CollisionLeft");
				}
			}
		}
	}

	if (Renderer_->IsAnimationName("CollisionRight"))
	{
		if(true == Renderer_->IsEndAnimation())
		{
			Renderer_->ChangeAnimation("IdleLeft");
		}
	}

	if (Renderer_->IsAnimationName("CollisionLeft"))
	{
		if (true == Renderer_->IsEndAnimation())
		{
			Renderer_->ChangeAnimation("IdleRight");
		}
	}

	std::vector<GameEngineCollision*> FireAttackColResult;
	if (true == Collision_->CollisionResult("FireAttackCol", FireAttackColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : FireAttackColResult)
		{
			FireAttackEffect* FireAttackEffect_ = dynamic_cast<FireAttackEffect*>(Collision->GetActor());
			if (FireAttackEffect_ != nullptr)
			{
				float Direction = FireAttackEffect_->GetPosition().x - GetPosition().x;
				if (Direction <= 0) // 몬스터가 오른쪽
				{
					Renderer_->ChangeAnimation("CollisionRight");
				}

				else // 몬스터가 왼쪽
				{
					Renderer_->ChangeAnimation("CollisionLeft");
				}
			}
		}
	}

	std::vector<GameEngineCollision*> SparkAttackColResult;
	if (true == Collision_->CollisionResult("SparkAttackCol", SparkAttackColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : SparkAttackColResult)
		{
			SparkAttackEffect* SparkAttackEffect_ = dynamic_cast<SparkAttackEffect*>(Collision->GetActor());
			if (SparkAttackEffect_ != nullptr)
			{
				float Direction = SparkAttackEffect_->GetPosition().x - GetPosition().x;
				if (Direction <= 0) // 몬스터가 오른쪽
				{
					Renderer_->ChangeAnimation("CollisionRight");
				}

				else // 몬스터가 왼쪽
				{
					Renderer_->ChangeAnimation("CollisionLeft");
				}
			}
		}
	}

	std::vector<GameEngineCollision*> IceAttackResult;
	if (true == Collision_->CollisionResult("IceAttackCol", IceAttackResult, CollisionType::Rect, CollisionType::Rect) && false == Renderer_->IsAnimationName("Ice"))
	{
		for (GameEngineCollision* Collision : IceAttackResult)
		{
			IceAttackEffect* IceAttackEffect_ = dynamic_cast<IceAttackEffect*>(Collision->GetActor());
			if (IceAttackEffect_ != nullptr)
			{
				Dir_ = float4::ZERO;
				Renderer_->ChangeAnimation("Ice");
				Collision_->Off();
				IceCol_->On();
			}
		}
	}

	std::vector<GameEngineCollision*> IceResult;
	if (true == IceCol_->CollisionResult("KirbyCol", IceResult, CollisionType::Rect, CollisionType::Rect) && true == Renderer_->IsAnimationName("Ice"))
	{
		for (GameEngineCollision* Collision : IceResult)
		{
			GameEngineActor* ColActor = Collision->GetActor();
			Player* IceColActor = dynamic_cast<Player*>(ColActor);
			if (IceColActor != nullptr)
			{
				IceCol_->Off();
				IceEndCol_->On();
				float Direction = IceColActor->GetPosition().x - GetPosition().x;
				SetSpeed(250.0f);
				if (Direction <= 0) // 몬스터가 오른쪽
				{
					Dir_ = float4::RIGHT;
				}

				if (Direction > 0) // 몬스터가 왼쪽
				{
					Dir_ = float4::LEFT;
				}
			}
		}
	}

	SetMove(Dir_* GameEngineTime::GetDeltaTime()* GetSpeed());
}
