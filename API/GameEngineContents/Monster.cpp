#include "Monster.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include "Player.h"
#include <GameEngine/GameEngineCollision.h>
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
	, Speed_(20.0f)
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
		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
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
}

void Monster::Render()
{
}

void Monster::Die()
{
	//if (Player_ == nullptr)
	//{
	//	return;
	//}

	if (true == IsDie())
	{
		if (true == Renderer_->IsAnimationName("DieLeft") ||
			true == Renderer_->IsAnimationName("DieRight"))
		{
			if (true == Renderer_->IsEndAnimation())
			{
				GetUI()->Off();
				Collision_->Off();
				Death();

				//if (DieEffect_ != nullptr)
				//{
				//	DieEffect_->SetState(DieEffectState::DieEffect);
				//	DieEffect_->SetPosition(GetPosition());
				//}
				//EffectRenderer_->SetAlpha(255);
				//EffectRenderer_->ChangeAnimation("DieEffect");
				//if (EffectRenderer_->IsEndAnimation())
				//{
				//	EffectRenderer_->SetAlpha(0);
				//}
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
			}
		}
	}
}

void Monster::UpdateMove()
{

	if (true == IceEndCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect))
	{
		GetUI()->Off();
		Collision_->Off();
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
			GetUI()->Off();
			Collision_->Off();
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
			GetUI()->Off();
			Collision_->Off();
			Death();
		}
		else
		{
			Dir_ = float4::RIGHT;
		}
	}

	// ���� ���� �浹ü�� Ŀ�� �ε����� �������� �̵�
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

		// ������ ���� �浹ü�� Ŀ�� �ε����� ���������� �̵�
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


	// Ŀ�� �Դ� �浹�� �ε����� �������� ����
	if (true == Collision_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	{
		Dir_ = float4::ZERO;
	}

	// Ŀ��� �ε����� ���� �ݴ������� �̵�
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
				if (MoveDir <= 0) // ���Ͱ� ������
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
				if (Direction <= 0) // ���Ͱ� ������
				{
					Renderer_->ChangeAnimation("CollisionRight");
				}

				else // ���Ͱ� ����
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
				if (Direction <= 0) // ���Ͱ� ������
				{
					Renderer_->ChangeAnimation("CollisionRight");
				}

				else // ���Ͱ� ����
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
			SetSparkEffect(SparkAttackEffect_);
			if (SparkAttackEffect_ != nullptr)
			{
				float Direction = SparkAttackEffect_->GetPosition().x - GetPosition().x;
				if (Direction <= 0) // ���Ͱ� ������
				{
					Renderer_->ChangeAnimation("CollisionRight");
				}

				else // ���Ͱ� ����
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
				Speed_ = 250.0f;
				if (Direction <= 0) // ���Ͱ� ������
				{
					Dir_ = float4::RIGHT;
				}

				if (Direction > 0) // ���Ͱ� ����
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
