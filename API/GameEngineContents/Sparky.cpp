#include "Sparky.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Monster.h"
#include "Player.h"
#include <vector>


Sparky::Sparky()
	: Monster()
	, SparkyRenderer_(nullptr)
	, SparkyCol_(nullptr)
	, Player_(nullptr)
	, Level_(nullptr)
	, DirectionCol_(nullptr)
	, ColMapImage_(nullptr)
	, AttackRenderer_(nullptr)
	, AttackRangeCol_(nullptr)
{
	SetMonsterClass(MonsterClass::SPARK);
}

Sparky::~Sparky()
{
}

void Sparky::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SparkyRenderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* SparkyImage = SparkyRenderer_->GetImage();
	SparkyImage->CutCount(10, 52);
	SparkyRenderer_->CreateAnimation("monster1.bmp", "WalkRight", 108, 111, 0.3f, true);
	SparkyRenderer_->CreateAnimation("monster1.bmp", "WalkLeft", 368, 371, 0.3f, true); // need to chk
	SparkyRenderer_->CreateAnimation("monster1.bmp", "Attack", 112, 113, 0.3f, true); // need to chk
	SparkyRenderer_->CreateAnimation("Monster1.bmp", "DieRight", 120, 121, 0.3f, false);
	SparkyRenderer_->CreateAnimation("Monster1.bmp", "DieLeft", 379, 380, 0.3f, false);
	SparkyRenderer_->ChangeAnimation("WalkRight");
	SparkyCol_ = CreateCollision("BasicMonster", float4(/*50.0f, 50.0f*/0.0f, 0.0f), float4(0.0f, -30.0f));
	DirectionCol_ = CreateCollision("DirectionCol", float4(/*200.0f, 50.0f*/0.0f, 0.0f), float4(0.0f, -30.0f));
	AttackRangeCol_ = CreateCollision("AttackRangeCol", float4(180.0f, 50.0f), float4(0.0f, -15.0f));
	AttackCol_ = CreateCollision("AttackCol", float4(150.0f, 50.0f), float4(30.0f, -15.0f));

	AttackRenderer_ = CreateRenderer("Monster1.bmp");
	GameEngineImage* AttackEffectImage = AttackRenderer_->GetImage();
	AttackEffectImage->CutCount(10, 52);
	AttackRenderer_->CreateAnimation("Monster1.bmp", "Attack", 118, 119, 0.3f, true);
	AttackRenderer_->ChangeAnimation("Attack");
	AttackRenderer_->SetAlpha(0);
	AttackRenderer_->SetScale(float4(0.0f, 0.0f));
}


void Sparky::Render()
{
}
void Sparky::Update()
{
	UpdateMove();
	UpdateAttack();
	IsDie();
	Die();
}
void Sparky::UpdateMove()
{
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(20.0f, 0.0f)))
	{
		Dir_ = float4::LEFT;
		SparkyRenderer_->ChangeAnimation("WalkLeft");
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-20.0f, 0.0f)))
	{
		Dir_ = float4::RIGHT;
		SparkyRenderer_->ChangeAnimation("WalkRight");
	}

	// 벽에 부딪혔을때
	if (GetPosition().x < 0)
	{
		Dir_ = float4::RIGHT;
		SparkyRenderer_->ChangeAnimation("WalkRight");
	}

	if (GetPosition().x > GetLevel()->GetMapSizeX())
	{
		Dir_ = float4::LEFT;
		SparkyRenderer_->ChangeAnimation("WalkLeft");
	}

	//vector 생성 std::vector<자료형>변수이름;
	std::vector<GameEngineCollision*> ColResult;
	if (DirectionCol_->CollisionResult("KirbyCol", ColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : ColResult)
		{
			Player* ColPlayer = dynamic_cast<Player*>(Collision->GetActor()); // 부딪힌 액터 꺼내기
			if (ColPlayer != nullptr)
			{
				float Distance = ColPlayer->GetPosition().x - GetPosition().x;
				if (Distance < 0)
				{
					Dir_ = float4::LEFT;
					SparkyRenderer_->ChangeAnimation("WalkLeft");
				}

				else if (Distance > 0)
				{
					Dir_ = float4::RIGHT;
					SparkyRenderer_->ChangeAnimation("WalkRight");
				}

				else if (Distance == 0)
				{
					ColPlayer->SetHP(ColPlayer->GetHP() - 1);
				}
			}
		}

		// 더이상 안 부딪히면 다시 walk 모드로
	}


	if (Dir_.x == float4::ZERO.x &&
		true != SparkyCol_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	{
		Dir_ = float4::RIGHT;
		SparkyRenderer_->ChangeAnimation("WalkRight");
	}
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 15);

}

void Sparky::UpdateAttack()
{
	std::vector<GameEngineCollision*> Result;
	std::vector<GameEngineCollision*> AttResult;
	if (AttackRangeCol_->CollisionResult("KirbyCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			Player* ColPlayer = dynamic_cast<Player*>(Collision->GetActor());
			if (ColPlayer != nullptr)
			{
				float Distance = ColPlayer->GetPosition().x - GetPosition().x;
				if (Distance < 0) // 몬스터가 오른쪽
				{
					Dir_ = float4::LEFT;
					SparkyRenderer_->ChangeAnimation("Attack");
					AttackCol_->SetScale(float4(20.0f, 20.0f));
					if (AttackCol_->CollisionResult("KirbyCol", AttResult, CollisionType::Rect, CollisionType::Rect))
					{
						for (GameEngineCollision* AttCollision : AttResult)
						{
							Dir_ = float4::ZERO;
							Player* ColPlayer = dynamic_cast<Player*>(AttCollision->GetActor());
							if (ColPlayer != nullptr)
							{
								AttackRenderer_->SetAlpha(255);
								AttackRenderer_->ChangeAnimation("Attack");
								AttackRenderer_->SetScale(float4(20.0f, 20.0f));
								ColPlayer->SetHP(ColPlayer->GetHP() - 1);

								if (AttackRenderer_->IsEndAnimation())
								{
									AttackRenderer_->SetScale(float4(0.0f, 0.0f));
									AttackCol_->SetScale(float4(0.0f, 0.0f));
								}
							}
						}
					}

				}

				else if (Distance > 0) // 몬스터가 왼쪽
				{
					Dir_ = float4::RIGHT;
					SparkyRenderer_->ChangeAnimation("Attack");
					Dir_ = float4::ZERO;
					AttackRenderer_->SetAlpha(255);
					AttackRenderer_->ChangeAnimation("Attack");
					AttackRenderer_->SetScale(float4(20.0f, 20.0f));
					AttackCol_->SetScale(float4(20.0f, 20.0f));
					if (AttackCol_->CollisionResult("KirbyCol", AttResult, CollisionType::Rect, CollisionType::Rect))
					{
						for (GameEngineCollision* AttCollision : AttResult)
						{
							Dir_ = float4::ZERO;
							Player* ColPlayer = dynamic_cast<Player*>(AttCollision->GetActor());
							if (ColPlayer != nullptr)
							{
								ColPlayer->SetHP(ColPlayer->GetHP() - 1);

								if (SparkyRenderer_->IsEndAnimation())
								{
									AttackRenderer_->SetPivot(float4(0.0f, 0.0f));
									AttackCol_->SetScale(float4(0.0f, 0.0f));
								}
							}
						}
					}

				}

				else if (Distance == 0) // 같은 위치
				{
					ColPlayer->SetHP(ColPlayer->GetHP() - 1);
				}
			}
		}
	}


}

bool Sparky::IsDie()
{
	if (GetHP() <= 0)
	{
		return true;
	}
	else return false;
}

void Sparky::Die()
{
	if (true == IsDie())
	{
		Death();
	}
}