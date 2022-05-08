#include "BombBomb.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImage.h>
#include "Player.h"
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"

BombBomb::BombBomb()
	:Obstruction()
{
}

BombBomb::~BombBomb()
{
}

void BombBomb::Start()
{
	Obstruction::Start();
	Renderer_ = CreateRenderer("BombBomb.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(7, 4);
	Renderer_->CreateAnimation("BombBomb.bmp", "Bomb", 0, 27, 0.05f, false);
	Renderer_->CreateAnimation("BombBomb.bmp", "Idle", 0, 0, 0.1f, true);
	Renderer_->ChangeAnimation("Idle");
	Collision_->SetPivot(float4(-270, 220));
}

void BombBomb::DelayUpdate()
{
	ColUpdate();
}

void BombBomb::ColUpdate()
{

	std::vector<GameEngineCollision*> Result;
	if (true == Collision_->CollisionResult("KirbySlideCol", Result, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("BombBomb.mp3", 0);
		for (GameEngineCollision* Collision : Result)
		{
			Player* Player_ = dynamic_cast<Player*>(Collision->GetActor());
			SetPlayer(Player_);
			if (Player_ != nullptr)
			{
				Collision_->Off();
				Renderer_->ChangeAnimation("Bomb");
			}
		}
	}

	std::vector<GameEngineCollision*> AttColResult;
	if (true == Collision_->CollisionResult("AttackCol", AttColResult, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("BombBomb.mp3", 0);
		for (GameEngineCollision* Collision : AttColResult)
		{
			AttackEffect* AttackEffect_ = dynamic_cast<AttackEffect*>(Collision->GetActor());
			if (AttackEffect_ != nullptr)
			{
				Collision_->Off();
				Renderer_->ChangeAnimation("Bomb");
			}
		}
	}

	std::vector<GameEngineCollision*> SparkAttColResult;
	if (true == Collision_->CollisionResult("SparkAttackCol", SparkAttColResult, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("BombBomb.mp3", 0);
		for (GameEngineCollision* Collision : SparkAttColResult)
		{
			SparkAttackEffect* SparkAttackEffect_ = dynamic_cast<SparkAttackEffect*>(Collision->GetActor());
			if (SparkAttackEffect_ != nullptr)
			{
				Collision_->Off();
				Renderer_->ChangeAnimation("Bomb");
			}
		}
	}


	std::vector<GameEngineCollision*> FireAttColResult;
	if (true == Collision_->CollisionResult("FireAttackCol", FireAttColResult, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("BombBomb.mp3", 0);
		for (GameEngineCollision* Collision : FireAttColResult)
		{
			FireAttackEffect* FireAttackEffect_ = dynamic_cast<FireAttackEffect*>(Collision->GetActor());
			if (FireAttackEffect_ != nullptr)
			{
				Collision_->Off();
				Renderer_->ChangeAnimation("Bomb");
			}
		}
	}


	std::vector<GameEngineCollision*> IceAttColResult;
	if (true == Collision_->CollisionResult("IceAttackCol", IceAttColResult, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("Bomb.mp3", 0);
		for (GameEngineCollision* Collision : IceAttColResult)
		{
			IceAttackEffect* IceAttackEffect_ = dynamic_cast<IceAttackEffect*>(Collision->GetActor());
			if (IceAttackEffect_ != nullptr)
			{
				Collision_->Off();
				Renderer_->ChangeAnimation("Bomb");
			}
		}
	}

}
