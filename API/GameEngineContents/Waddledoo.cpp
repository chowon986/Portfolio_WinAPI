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
	, Dir_(float4::ZERO)
	, Player_(nullptr)
	, Level_(nullptr)
	, ColMapImage_(nullptr)
	, Renderer_(nullptr) 
	, AttackRenderer_(nullptr)
	, AttackCol_(nullptr)
	, Collision_(nullptr)
		, AttackRangeCol_(nullptr)
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

	Renderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 26);
	Renderer_->CreateAnimation("monster1.bmp", "WalkRight", 17, 21, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "WalkLeft", 276, 280, 0.3f, true); 
	Renderer_->CreateAnimation("monster1.bmp", "AttackStartRight", 22, 24, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "AttackStartLeft", 281, 283, 0.3f, true);
	Renderer_->CreateAnimation("monster1.bmp", "AttackRight", 25, 25, 0.3f, false);
	Renderer_->CreateAnimation("monster1.bmp", "AttackLeft", 284, 284, 0.3f, true);
	Renderer_->ChangeAnimation("WalkRight");

	AttackRenderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* AttackImage = AttackRenderer_->GetImage();
	AttackImage->CutCount(10, 26);
	AttackRenderer_->CreateAnimation("monster1.bmp", "AttackRight", 26, 27, 0.3f, true);
	AttackRenderer_->CreateAnimation("monster1.bmp", "AttackLeft", 26, 27, 0.3f, true);
	AttackRenderer_->SetAlpha(0);

	Collision_ = CreateCollision("BasicMonster", float4(50.0f, 50.0), float4(0.0f, -30.0f));
	//RightDirCol_ = CreateCollision("RightDirCol", float4(10.0f, 50.0f), float4(80.0f, -30.0f));
	//LeftDirCol_ = CreateCollision("LeftDirCol", float4(10.0f, 50.0f), float4(-80.0f, -30.0f));
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
		Renderer_->ChangeAnimation("WalkLeft");
	}

	if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-20.0f, 0.0f)))
	{
		Dir_ = float4::RIGHT;
		Renderer_->ChangeAnimation("WalkRight");
	}

	// 벽에 부딪혔을때
	if (GetPosition().x < 0)
	{
		Dir_ = float4::RIGHT;
		Renderer_->ChangeAnimation("WalkRight");
	}

	if (GetPosition().x > GetLevel()->GetMapSizeX())
	{
		Dir_ = float4::LEFT;
		Renderer_->ChangeAnimation("WalkLeft");
	}

	//std::vector<GameEngineCollision*> LeftColResult;
	//if (LeftDirCol_->CollisionResult("KirbyCol", LeftColResult, CollisionType::Rect, CollisionType::Rect))
	//{
	//	for (GameEngineCollision* LeftCol : LeftColResult)
	//	{
	//		Player* LeftColPlayer = dynamic_cast<Player*>(LeftCol->GetActor());
	//		if (LeftColPlayer != nullptr)
	//		{
	//			Dir_ = float4::LEFT;
	//			Renderer_->ChangeAnimation("WalkLeft");
	//		}

	//	}
	//}

	//std::vector<GameEngineCollision*> RightColResult;
	//if (RightDirCol_->CollisionResult("KirbyCol", RightColResult, CollisionType::Rect, CollisionType::Rect))
	//{
	//	for (GameEngineCollision* RightCol : RightColResult)
	//	{
	//		Player* RightColPlayer = dynamic_cast<Player*>(RightCol->GetActor());
	//		if (RightColPlayer != nullptr)
	//		{
	//			Dir_ = float4::RIGHT;
	//			Renderer_->ChangeAnimation("WalkRight");
	//		}
	//	}
	//}

	//if (Dir_.x == float4::ZERO.x &&
	//	true != Collision_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	//{
	//	Dir_ = float4::RIGHT;
	//	Renderer_->ChangeAnimation("WalkRight");
	//}

	if (false == Renderer_->IsAnimationName("AttackRight") && false == Renderer_->IsAnimationName("AttackLeft"))
	{
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 15);
	}
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
					Renderer_->ChangeAnimation("AttackStartLeft");
					if (Renderer_->IsEndAnimation())
					{
						Dir_ = float4::ZERO;
						Renderer_->ChangeAnimation("AttackLeft");
						AttackRenderer_->SetAlpha(255);
						AttackRenderer_->ChangeAnimation("AttackLeft");
						AttackRenderer_->SetPivot(float4(60.0f, 0.0f));
						AttackCol_->SetScale(float4(20.0f, 0.0f));
						SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 15);
						if (AttackCol_->CollisionResult("KirbyCol", AttResult, CollisionType::Rect, CollisionType::Rect))
						{
							for (GameEngineCollision* AttCollision : AttResult)
							{
								Player* ColPlayer = dynamic_cast<Player*>(AttCollision->GetActor());
								if (ColPlayer != nullptr)
								{
									ColPlayer->SetHP(ColPlayer->GetHP() - 1);

									if (Renderer_->IsEndAnimation())
									{
										AttackRenderer_->SetPivot(float4(0.0f, 0.0f));
										Renderer_->ChangeAnimation("WalkLeft");
										Dir_ = float4::LEFT;
									}
								}
							}
						}
					}
				}

				else if (Distance > 0) // 몬스터가 왼쪽
				{
					Dir_ = float4::RIGHT;
					Renderer_->ChangeAnimation("AttackStartRight");
					if (Renderer_->IsEndAnimation())
					{
						Renderer_->ChangeAnimation("AttackRight");
						AttackRenderer_->SetAlpha(255);
						AttackRenderer_->ChangeAnimation("AttackRight");
						AttackRenderer_->SetPivot(float4(60.0f, 0.0f));
						float4 Move = AttackRenderer_->GetPivot() + float4::RIGHT * GameEngineTime::GetDeltaTime() * 100;
						AttackRenderer_->SetPivot(Move);
					
						AttackCol_->SetScale(float4(40.0f, 0.0f));
						if (AttackCol_->CollisionResult("KirbyCol", AttResult, CollisionType::Rect, CollisionType::Rect))
						{
							for (GameEngineCollision* AttCollision : AttResult)
							{
								Dir_ = float4::ZERO;
								Player* ColPlayer = dynamic_cast<Player*>(AttCollision->GetActor());
								if (ColPlayer != nullptr)
								{
									ColPlayer->SetHP(ColPlayer->GetHP() - 1);

									if (Renderer_->IsEndAnimation())
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