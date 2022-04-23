#include "Waddledi.h"
#include "Player.h"
#include "Monster.h"
#include "IceAttackEffect.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <vector>

Waddledi::Waddledi() 
	: Monster()
	, ColMapImage_(nullptr)
	, Level_(nullptr)
	, Player_(nullptr)
	, WaddlediCol_(nullptr)
	, Renderer_(nullptr)
	, Dir_(float4::ZERO)
	, LeftDirCol_(nullptr)
	, RightDirCol_(nullptr)
	, EffectRenderer_(nullptr)
{
}

Waddledi::~Waddledi()
{
}

void Waddledi::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetHP(2);
	Dir_ = float4::RIGHT;

	Renderer_ = CreateRenderer("Monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 7, 14, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 266, 273, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 15, 15, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 274, 274, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 15, 16, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 274, 275, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);
	Renderer_->ChangeAnimation("WalkRight");

	EffectRenderer_ = CreateRenderer("MonsterDie.bmp");
	GameEngineImage* EffectImage = EffectRenderer_->GetImage();
	EffectImage->CutCount(10, 3);
	EffectRenderer_->CreateAnimation("MonsterDie.bmp", "DieEffect", 0, 24, 0.05f, true);
	EffectRenderer_->ChangeAnimation("DieEffect");
	EffectRenderer_->SetAlpha(0);

	WaddlediCol_ = CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	RightDirCol_ = CreateCollision("RightDirCol", float4(10.0f, 50.0f), float4(80.0f, -30.0f));
	LeftDirCol_ = CreateCollision("LeftDirCol", float4(10.0f, 50.0f), float4(-80.0f, -30.0f));
}

void Waddledi::Render()
{
}


void Waddledi::Update()
{
	UpdateMove();
	IsDie();
	Die();
}

void Waddledi::UpdateMove()
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

	if (GetPosition().x < 0)
	{
		Dir_ = float4::RIGHT;
		Renderer_->ChangeAnimation("WalkRight");
	}

	if (GetPosition().x > GetLevel()->GetMapSizeX()-1)
	{
		Dir_ = float4::LEFT;
		Renderer_->ChangeAnimation("WalkLeft");
	}

	std::vector<GameEngineCollision*> LeftColResult;
	if (LeftDirCol_->CollisionResult("KirbyCol", LeftColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* LeftCol : LeftColResult)
		{
			Player* LeftColPlayer = dynamic_cast<Player*>(LeftCol->GetActor());
			if (LeftColPlayer != nullptr)
			{
				Dir_ = float4::LEFT;
				Renderer_->ChangeAnimation("WalkLeft");
			}

		}
	}

	std::vector<GameEngineCollision*> RightColResult;
	if (RightDirCol_->CollisionResult("KirbyCol", RightColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* RightCol : RightColResult)
		{
			Player* RightColPlayer = dynamic_cast<Player*>(RightCol->GetActor());
			if (RightColPlayer != nullptr)
			{
				Dir_ = float4::RIGHT;
				Renderer_->ChangeAnimation("WalkRight");
			}
		}
	}


	if (true == WaddlediCol_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	{
		Dir_ = float4::ZERO;
	}

	//if (Dir_.x == float4::ZERO.x &&
	//	true != WaddlediCol_->CollisionCheck("KirbyEatCol", CollisionType::Rect, CollisionType::Rect))
	//{
	//	Dir_ = float4::RIGHT;
	//	Renderer_->ChangeAnimation("WalkRight");
	//}

	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 15);

	std::vector<GameEngineCollision*> ColResult;
	if (WaddlediCol_->CollisionResult("KirbyCol", ColResult, CollisionType::Rect, CollisionType::Rect))
	{
		float4 StartPos = GetPosition();
		for (GameEngineCollision* CenterCol : ColResult)
		{
			Player* CenterColPlayer = dynamic_cast<Player*>(CenterCol->GetActor());
			if (CenterColPlayer != nullptr)
			{
				float MoveDir = CenterColPlayer->GetPosition().x - GetPosition().x;
				if (MoveDir <= 0)
				{
					if (StartPos.x - GetPosition().x > -20 && true != Renderer_->IsAnimationName("Ice"))
					{
						Renderer_->ChangeAnimation("CollisionRight");
						Dir_ = float4::RIGHT;
						float4 Move = Dir_ * GameEngineTime::GetDeltaTime() * 20;
						SetMove(Move);
					}
				}
				if (MoveDir > 0)
				{
					if (StartPos.x - GetPosition().x < 20 && true != Renderer_->IsAnimationName("Ice"))
					{
						Renderer_->ChangeAnimation("CollisionLeft");
						Dir_ = float4::LEFT;
						float4 Move = Dir_ * GameEngineTime::GetDeltaTime() * 20;
						SetMove(Move);
					}
				}
			}
		}
	}

	std::vector<GameEngineCollision*> Result;
	if (true == WaddlediCol_->CollisionResult("KirbySlideCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : Result)
		{
			GameEngineActor* ColActor = Collision->GetActor();
			Player* Player_ = dynamic_cast<Player*>(ColActor);
			if (Player_ != nullptr)
			{
				float Direction = Player_->GetPosition().x - GetPosition().x;
				float4 StartPos = GetPosition();
				SetHP(GetHP() - 1);
				if (Direction <= 0)
				{
					Dir_ = float4::LEFT;
					if (StartPos.x - GetPosition().x < -20)
					{
						Renderer_->ChangeAnimation("CollisionRight");
						SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 20);
					}
				}

				if (Direction > 0)
				{
					Dir_ = float4::LEFT;
					if (StartPos.x - GetPosition().x < 20)
					{
						Renderer_->ChangeAnimation("CollisionLeft");
						SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 20);

					}
				}
			}
		}
	}


	if (true == WaddlediCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect) && true == Renderer_->IsAnimationName("Ice"))
	{
		float4 StartPos = GetPosition();
		// need to chk : Player°¡ nullptr
		float MoveDir = Player_->GetPosition().x - GetPosition().x;
		if (MoveDir <= 0)
		{
			if (StartPos.x - GetPosition().x > -20)
			{
				Dir_ = float4::RIGHT;
				float4 Move = Dir_ * GameEngineTime::GetDeltaTime() * 20;
				SetMove(Move);
				if (true == WaddlediCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect) || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(20.0f, 0.0f)))
				{
					Death();
					EffectRenderer_->ChangeAnimation("DieEffect");
					EffectRenderer_->SetAlpha(255);
					if (EffectRenderer_->IsEndAnimation())
					{
						EffectRenderer_->SetAlpha(0);
					}
				}
			}
		}
		if (MoveDir > 0)
		{
			if (StartPos.x - GetPosition().x < 20)
			{
				Dir_ = float4::LEFT;
				float4 Move = Dir_ * GameEngineTime::GetDeltaTime() * 20;
				SetMove(Move);
				if (true == WaddlediCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect) || RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4(-20.0f, 0.0f)))
				{
					Death();
					EffectRenderer_->ChangeAnimation("DieEffect");
					EffectRenderer_->SetAlpha(255);
					if (EffectRenderer_->IsEndAnimation())
					{
						EffectRenderer_->SetAlpha(0);
					}
				}
			}
		}
	}
}

bool Waddledi::IsDie()
{
	//	if (GetHP() <= 0)
	//	{
	//		return true;
	//	}
	//	else return false;
	return false;
}
//

void Waddledi::Die()
{
//	if (true == IsDie())
//	{
//		if (Player_->GetPosition().x - GetPosition().x >= 0)
//		{
//			Renderer_->ChangeAnimation("DieLeft");
//			if (Renderer_->IsEndAnimation())
//			{
//				Death();
//
//				EffectRenderer_->SetAlpha(255);
//				EffectRenderer_->ChangeAnimation("DieEffect");
//				if (EffectRenderer_->IsEndAnimation())
//				{
//					EffectRenderer_->SetAlpha(0);
//				}
//			}
//		}
//
//		if (Player_->GetPosition().x - GetPosition().x < 0)
//		{
//			Renderer_->ChangeAnimation("DieRight");
//			if (Renderer_->IsEndAnimation())
//			{
//				Death();
//				EffectRenderer_->SetAlpha(255);
//				EffectRenderer_->ChangeAnimation("DieEffect");
//				if (EffectRenderer_->IsEndAnimation())
//				{
//					EffectRenderer_->SetAlpha(0);
//				}
//			}
//		}
//	}
}