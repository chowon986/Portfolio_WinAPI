#include "Monster.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "GameEngineLevelBase.h"
#include "IceAttackEffect.h"
#include "DieEffect.h"
#include "FireAttackEffect.h"
#include "SparkAttackEffect.h"
#include "MonBotUI.h"


Monster::Monster()
	: Pos_(0, 0)
	, MonsterClass_(MonsterClass::DEFAULT)
	, Player_(nullptr)
	, Dir_(float4::RIGHT)
	, Time_(0.0f)
	, Collision_(nullptr)
	, Renderer_(nullptr)
	, LeftDirCol_(nullptr)
	, RightDirCol_(nullptr)
	, EffectRenderer_(nullptr)
	, MonsterState_(MonsterState::WALK)
	, Level_(nullptr)
	, IceEndCol_(nullptr)
	, IceCol_(nullptr)
	, DieEffect_(nullptr)
	, ColMapImage_(nullptr)
{
}

Monster::~Monster()
{
}

void Monster::Walk()
{
	if (true != Renderer_->IsAnimationName("DieRight") &&
		true != Renderer_->IsAnimationName("DieLeft"))
	{
		if (true != Renderer_->IsAnimationName("Ice"))
		{
			if (Dir_.x == 1)
			{
				Renderer_->ChangeAnimation("WalkRight");
			}
			else if (Dir_.x == -1)
			{
				Renderer_->ChangeAnimation("WalkLeft");
			}
		}
		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * GetSpeed());
	}
}

void Monster::SetHP(int _HP)
{
	CharacterBase::SetHP(_HP);

	if (GetHP() <= 0)
	{
		GameEngineLevelBase* Level = dynamic_cast<GameEngineLevelBase*>(GetLevel());
		if (Level != nullptr)
		{
			MonBotUI* MonBotUI = Level->GetMonBotUI();
			if (MonBotUI != nullptr)
			{
				MonBotUI->DelayOff();
			}
		}
		
	}
}

void Monster::Jump()
{
}

bool Monster::IsDie()
{
	if (GetHP() <= 0)
	{
		return true;
	}
	else return false;
}

void Monster::attack()
{
}

void Monster::GetPos(float4 _Pos)
{
}

void Monster::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetHP(2);
	SetSpeed(20);

	Collision_ = CreateCollision("BasicMonster", float4(48.0f, 48.0f), float4(0.0f, -30.0f));
	IceCol_ = CreateCollision("IceCol", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	IceEndCol_ = CreateCollision("IceEndCol", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	RightDirCol_ = CreateCollision("RightDirCol", float4(10.0f, 50.0f), float4(80.0f, -30.0f));
	LeftDirCol_ = CreateCollision("LeftDirCol", float4(10.0f, 50.0f), float4(-80.0f, -30.0f));
	IceCol_->Off();
	IceEndCol_->Off();

	DieRenderer_ = CreateRenderer("MonsterDi.bmp");
	GameEngineImage* DieImage_ = DieRenderer_->GetImage();
	DieImage_->CutCount(12, 2);
	DieRenderer_->CreateAnimation("MonsterDi.bmp", "Die", 0, 23, 0.05f, true);
	DieRenderer_->CreateAnimation("MonsterDi.bmp", "None", 14, 14, 0.03f, true);
	DieRenderer_->ChangeAnimation("None");
	DieRenderer_->SetOrder(7);
}

void Monster::Render()
{
}

void Monster::Die()
{

	if (true == IsDie())
	{
		if (true == Renderer_->IsAnimationName("DieLeft") ||
			true == Renderer_->IsAnimationName("DieRight"))
		{
			if (true == Renderer_->IsEndAnimation())
			{
				Collision_->Off();
				Death();
			}
		}

		if (true != Renderer_->IsAnimationName("DieLeft"))
		{
			if ((Player_ != nullptr && Player_->GetPosition().x - GetPosition().x > 0) ||
				(Fire_ != nullptr && Fire_->GetPosition().x - GetPosition().x > 0) ||
				(Spark_ != nullptr && Spark_->GetPosition().x - GetPosition().x > 0))
			{
				Collision_->Off();
				Dir_ = float4::LEFT;
				Renderer_->ChangeAnimation("DieLeft");
				DieRenderer_->ChangeAnimation("Die");
				DieRenderer_->SetPivot(float4(0.0f, 60.0f));
			}

		}

		if (true != Renderer_->IsAnimationName("DieRight"))
		{
			if (Player_ != nullptr && Player_->GetPosition().x - GetPosition().x <= 0 ||
				(Fire_ != nullptr && Fire_->GetPosition().x - GetPosition().x <= 0) ||
				(Spark_ != nullptr && Spark_->GetPosition().x - GetPosition().x <= 0))
			{
				Dir_ = float4::RIGHT;
				Collision_->Off();
				Renderer_->ChangeAnimation("DieRight");
				DieRenderer_->ChangeAnimation("Die");
				DieRenderer_->SetPivot(float4(0.0f, 60.0f));
			}
		}

		if (DieRenderer_->IsAnimationName("Die") &&
			DieRenderer_->IsEndAnimation())
		{
			DieRenderer_->ChangeAnimation("None");
		}
	}
}

void Monster::UpdateMove()
{

	if (true == IceEndCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect))
	{
		Death();
		//EffectRenderer_->ChangeAnimation("DieEffect");
		//EffectRenderer_->SetAlpha(255);
		//if (EffectRenderer_->IsEndAnimation())
		//{
		//	EffectRenderer_->Death();
		//}
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(20.0f, 0.0f)) || (GetPosition().x > GetLevel()->GetMapSizeX() - 1))
	{
		if (true == Renderer_->IsAnimationName("Ice"))
		{
			Death();
		}
		else
		{
			Dir_ = float4::LEFT;
		}
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-20.0f, 0.0f)) || GetPosition().x < 0)
	{
		if (true == Renderer_->IsAnimationName("Ice"))
		{
			Death();
		}
		else
		{
			Dir_ = float4::RIGHT;
		}
	}

	// 왼쪽 방향 충돌체와 커비가 부딪히면 왼쪽으로 이동
	if (true == CanWalk())
	{
		std::vector<GameEngineCollision*> LeftColResult;
		if (LeftDirCol_->CollisionResult("KirbyCol", LeftColResult, CollisionType::Rect, CollisionType::Rect))
		{
			for (GameEngineCollision* LeftCol : LeftColResult)
			{
				Player* LeftColPlayer = dynamic_cast<Player*>(LeftCol->GetActor());
				SetPlayer(LeftColPlayer);
				if (LeftColPlayer != nullptr)
				{
					Dir_ = float4::LEFT;
				}

			}
		}

		// 오른쪽 방향 충돌체와 커비가 부딪히면 오른쪽으로 이동
		std::vector<GameEngineCollision*> RightColResult;
		if (RightDirCol_->CollisionResult("KirbyCol", RightColResult, CollisionType::Rect, CollisionType::Rect))
		{
			for (GameEngineCollision* RightCol : RightColResult)
			{
				Player* RightColPlayer = dynamic_cast<Player*>(RightCol->GetActor());
				SetPlayer(RightColPlayer);
				if (RightColPlayer != nullptr)
				{
					Dir_ = float4::RIGHT;
				}
			}
		}
	}


	// 커비 먹는 충돌과 부딪히면 움직이지 않음
	if (true == Collision_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	{
		Dir_ = float4::ZERO;
	}

	// 커비와 부딪히는 방향 반대쪽으로 이동
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
					Dir_ = float4::RIGHT;
					if (true != Renderer_->IsAnimationName("Ice"))
					{
						Renderer_->ChangeAnimation("CollisionRight");
						LeftDirCol_->Off();
						RightDirCol_->Off();
					}
				}
				else
				{
					Dir_ = float4::LEFT;
					if (true != Renderer_->IsAnimationName("Ice"))
					{
						Renderer_->ChangeAnimation("CollisionLeft");
						LeftDirCol_->Off();
						RightDirCol_->Off();
					}
				}
			}
		}
	}


	std::vector<GameEngineCollision*> SlideColResult;
	if (true == Collision_->CollisionResult("KirbySlideCol", SlideColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : SlideColResult)
		{
			Player* ColPlayer = dynamic_cast<Player*>(Collision->GetActor());
			SetPlayer(ColPlayer);
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

	std::vector<GameEngineCollision*> FireAttackColResult;
	if (true == Collision_->CollisionResult("FireAttackCol", FireAttackColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : FireAttackColResult)
		{
			FireAttackEffect* FireAttackEffect_ = dynamic_cast<FireAttackEffect*>(Collision->GetActor());
			SetFireEffect(FireAttackEffect_);
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

	std::vector<GameEngineCollision*> AnimalAttackColResult;
	if (true == Collision_->CollisionResult("AnimalCol", AnimalAttackColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : AnimalAttackColResult)
		{
			Player* Player_ = dynamic_cast<Player*>(Collision->GetActor());
			SetPlayer(Player_);
			if (Player_ != nullptr)
			{
				float Direction = Player_->GetPosition().x - GetPosition().x;
				if (Direction <= 0) // 몬스터가 오른쪽
				{
					Renderer_->ChangeAnimation("CollisionRight");
					SetHP(GetHP() - 1);
				}

				else // 몬스터가 왼쪽
				{
					Renderer_->ChangeAnimation("CollisionLeft");
					SetHP(GetHP() - 1);
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
			SetSparkEffect(SparkAttackEffect_);
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
				LeftDirCol_->Off();
				RightDirCol_->Off();
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
			SetPlayer(IceColActor);
			if (IceColActor != nullptr)
			{
				IceCol_->Off();
				IceEndCol_->On();
				float Direction = IceColActor->GetPosition().x - GetPosition().x;
				SetSpeed(500.0f);
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

	if (CanWalk())
	{
		Walk();
	}
}

bool Monster::CanWalk()
{
	if (true == Renderer_->IsAnimationName("DieRight") ||
		true == Renderer_->IsAnimationName("DieLeft"))
	{
		return false;
	}

	if (Renderer_->IsAnimationName("CollisionRight") ||
		Renderer_->IsAnimationName("CollisionLeft"))
	{
		Time_ += GameEngineTime::GetDeltaTime();
		if (Time_ < 1.0f)
		{
			return false;
		}
		else
		{
			Time_ = 0.0f;
			return true;
		}
	}
	return true;
}
