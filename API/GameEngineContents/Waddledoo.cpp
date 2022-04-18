#include "Waddledoo.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Monster.h"
#include "Player.h"
#include <vector>

Waddledoo::Waddledoo()
	: Monster()
{
	//SetMonsterClass(MonsterClass::BEAM);
}

Waddledoo::~Waddledoo()
{
}

void Waddledoo::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

    WaddledooRenderer_ = CreateRenderer("monster0.bmp");
	GameEngineImage* WaddledooImage = WaddledooRenderer_->GetImage();
	WaddledooImage->CutCount(10, 26);
	WaddledooRenderer_->CreateAnimation("monster0.bmp", "WalkRight", 17, 21, 0.3f, true);
	WaddledooRenderer_->CreateAnimation("monster0.bmp", "WalkLeft", 17, 21, 0.3f, true); // need to # chng
	WaddledooRenderer_->CreateAnimation("monster0.bmp", "AttackStartRight", 22, 24, 0.3f, true);
	WaddledooRenderer_->CreateAnimation("monster0.bmp", "AttackStartLeft", 17, 21, 0.3f, true);// need to # chng
	WaddledooRenderer_->CreateAnimation("monster0.bmp", "AttackRight", 25, 25, 0.3f, false);
	WaddledooRenderer_->CreateAnimation("monster0.bmp", "AttackLeft", 17, 21, 0.3f, true);// need to # chng
	WaddledooRenderer_->ChangeAnimation("WalkRight");

	AttackRenderer_ = CreateRenderer("monster0.bmp");
	GameEngineImage* AttackImage = AttackRenderer_->GetImage();
	AttackImage->CutCount(10, 26);
	AttackRenderer_->CreateAnimation("monster0.bmp", "AttackRight", 26, 27, 0.3f, true);
	AttackRenderer_->CreateAnimation("monster0.bmp", "AttackLeft", 26, 27, 0.3f, true);
	AttackRenderer_->SetAlpha(0);

	WaddledooCol_ = CreateCollision("BasicMonster", float4(/*50.0f, 50.0f*/0.0f,0.0f), float4(0.0f, -30.0f));
	DirectionCol_ = CreateCollision("DirectionCol", float4(/*200.0f, 50.0f*/0.0f,0.0f), float4(0.0f, -30.0f));
	AttackRangeCol_ = CreateCollision("AttackRangeCol_", float4(180.0f, 50.0f), float4(0.0f, -15.0f));
	AttackCol_ = CreateCollision("AttackCol_", float4(150.0f, 50.0f), float4(30.0f, -15.0f));
}

void Waddledoo::Render()
{
}

void Waddledoo::Update()
{
	UpdateMove();
	UpdateAttack();
	IsDie();
	Die();
}
void Waddledoo::UpdateMove()
{
	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(20.0f, 0.0f)))
	{
		Dir_ = float4::LEFT;
		WaddledooRenderer_->ChangeAnimation("WalkLeft");
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-20.0f, 0.0f)))
	{
		Dir_ = float4::RIGHT;
		WaddledooRenderer_->ChangeAnimation("WalkRight");
	}

	// 벽에 부딪혔을때
	if (GetPosition().x < 0)
	{
		Dir_ = float4::RIGHT;
		WaddledooRenderer_->ChangeAnimation("WalkRight");
	}

	if (GetPosition().x > GetLevel()->GetMapSizeX())
	{
		Dir_ = float4::LEFT;
		WaddledooRenderer_->ChangeAnimation("WalkLeft");
	}

	//vector 생성 std::vector<자료형>변수이름;
	std::vector<GameEngineCollision*> Result;
	if (DirectionCol_->CollisionResult("KirbyCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			Player* ColPlayer = dynamic_cast<Player*>(Collision->GetActor()); // 부딪힌 액터 꺼내기
			if (ColPlayer != nullptr)
			{
				float Distance = ColPlayer->GetPosition().x - GetPosition().x;
				if (Distance < 0)
				{
					Dir_ = float4::LEFT;
					WaddledooRenderer_->ChangeAnimation("WalkLeft");
				}

				else if (Distance > 0)
				{
					Dir_ = float4::RIGHT;
					WaddledooRenderer_->ChangeAnimation("WalkRight");
				}

				else if (Distance == 0)
				{
					ColPlayer->SetHP(ColPlayer->GetHP() - 1);
				}
			}
		}
	}


	if (Dir_.x == float4::ZERO.x &&
		true != WaddledooCol_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	{
		Dir_ = float4::RIGHT;
		WaddledooRenderer_->ChangeAnimation("WalkRight");
	}
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 15);

}

void Waddledoo::UpdateAttack()
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
					WaddledooRenderer_->ChangeAnimation("AttackStartLeft");
					if (WaddledooRenderer_->IsEndAnimation())
					{
						WaddledooRenderer_->ChangeAnimation("AttackLeft");
						AttackRenderer_->SetAlpha(255);
						AttackRenderer_->ChangeAnimation("AttackLeft");
						AttackRenderer_->SetPivot(float4(-20.0f, 0.0f));
						AttackCol_->SetScale(float4(20.0f, 0.0f));
						if (AttackCol_->CollisionResult("KirbyCol", AttResult, CollisionType::Rect, CollisionType::Rect))
						{
							for (GameEngineCollision* AttCollision : AttResult)
							{
								Dir_ = float4::ZERO;
								Player* ColPlayer = dynamic_cast<Player*>(AttCollision->GetActor());
								if (ColPlayer != nullptr)
								{
									ColPlayer->SetHP(ColPlayer->GetHP() - 1);

									if (WaddledooRenderer_->IsEndAnimation())
									{
										AttackRenderer_->SetPivot(float4(0.0f, 0.0f));
									}
								}
							}
						}
					}
				}

				else if (Distance > 0) // 몬스터가 왼쪽
				{
					Dir_ = float4::RIGHT;
					WaddledooRenderer_->ChangeAnimation("AttackStartRight");
					if (WaddledooRenderer_->IsEndAnimation())
					{
						WaddledooRenderer_->ChangeAnimation("AttackRight");
						Dir_ = float4::ZERO;
						AttackRenderer_->SetAlpha(255);
						AttackRenderer_->ChangeAnimation("AttackRight");
						AttackRenderer_->SetPivot(float4(-20.0f, 0.0f));
						float4 Move = AttackRenderer_->GetPivot() + float4::RIGHT * GameEngineTime::GetDeltaTime() * 100;
						AttackRenderer_->SetPivot(Move);
					
						AttackCol_->SetScale(float4(20.0f, 0.0f));
						if (AttackCol_->CollisionResult("KirbyCol", AttResult, CollisionType::Rect, CollisionType::Rect))
						{
							for (GameEngineCollision* AttCollision : AttResult)
							{
								Dir_ = float4::ZERO;
								Player* ColPlayer = dynamic_cast<Player*>(AttCollision->GetActor());
								if (ColPlayer != nullptr)
								{
									ColPlayer->SetHP(ColPlayer->GetHP() - 1);

									if (WaddledooRenderer_->IsEndAnimation())
									{
										AttackRenderer_->SetPivot(float4(0.0f, 0.0f));
									}
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

bool Waddledoo::IsDie()
{
	if (GetHP() <= 0)
	{
		return true;
	}
	else return false;
}

void Waddledoo::Die()
{
	if (true == IsDie())
	{
		Death();
	}
}