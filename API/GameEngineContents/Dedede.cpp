#include "Dedede.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "IceAttackEffect.h"

Dedede::Dedede()
	: Monster()
	, Time_(0.0f)
	, AttTime_(5.0f)
	, FlyAttackTime_(0.0f)
	, FlyUpTime_(0.0f)
	, JumpTime_(0.0f)
	, DededeState_(DededeState::IDLE)
{
	SetMonsterClass(MonsterClass::BOSS);
}

Dedede::~Dedede()
{
}

void Dedede::Start()
{
	Monster::Start();

	Renderer_ = CreateRenderer("KingDedede.bmp", 2147483646, RenderPivot::CENTER, float4(0, -120));
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("KingDedede.bmp", "IdleRight", 0, 3, 0.2f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "IdleLeft", 32, 35, 0.2f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "WalkRight", 4, 7, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "WalkLeft", 36, 39, 0.1f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "JumpRight", 8, 8, 0.6f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "JumpLeft", 40, 40, 0.6f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "JumpDownRight", 9, 10, 0.6f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "JumpDownLeft", 41, 42, 0.6f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "AttackRight", 11, 20, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "AttackLeft", 43, 52, 0.1f, true);

	// HP가 어느 이상 줄면
	Renderer_->CreateAnimation("KingDedede.bmp", "YellRight", 21, 24, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "YellLeft", 53, 56, 0.1f, true);


	Renderer_->CreateAnimation("KingDedede.bmp", "FlyUpRight", 25, 25, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "FlyUpLeft", 57, 57, 0.1f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "FlyRight", 26, 27, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "FlyLeft", 58, 59, 0.1f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "FlyDownRight", 9, 9, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "FlyDownLeft", 41, 41, 0.1f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "FlyDownAttackRight", 10, 10, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "FlyDownAttackLeft", 42, 42, 0.1f, true);


	Renderer_->CreateAnimation("KingDedede.bmp", "DieRight", 29, 31, 0.3f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "DieLeft", 61, 63, 0.3f, true);
	Renderer_->ChangeAnimation("WalkRight");

	SetHP(13);
	SetSpeed(100.f);

	Collision_->SetScale(float4(150.0f, 180.0f));
	Collision_->SetPivot(float4(0, -85));
	//EffectRenderer_ = CreateRenderer("MonsterDie.bmp");
	//GameEngineImage* EffectImage = EffectRenderer_->GetImage();
	//EffectImage->CutCount(10, 3);
	//EffectRenderer_->CreateAnimation("MonsterDie.bmp", "DieEffect", 0, 24, 0.05f, true);
	//EffectRenderer_->ChangeAnimation("DieEffect");
	//EffectRenderer_->SetAlpha(0);

	Dir_ = float4::LEFT;
	Direction_ = "Left";
}


void Dedede::DelayUpdate()
{
	Time_ += GameEngineTime::GetDeltaTime();
	AttTime_ += GameEngineTime::GetDeltaTime();
	Die();
	UpdateMove();
	StateUpdate();
}

void Dedede::UpdateMove()
{
	if (IsDie())
	{
		if (GetState() != DededeState::DIE)
		{
			SetState(DededeState::DIE);
		}
		
		if (Renderer_->IsEndAnimation())
		{
			//GameEngine::GetInst().ChangeLevel("EndingStory");
		}
		return;
	}

	// 3초에 한 번씩
	if (Time_ > 3.0f)
	{
		PlayerPos_ = Player_->GetPosition();
		Time_ = 0.0f;
	}

	if (PlayerPos_.x - GetPosition().x > 0)
	{
		Dir_ = float4::RIGHT;
		Direction_ = "Right";
	}
	else
	{
		Dir_ = float4::LEFT;
		Direction_ = "Left";
	}

	if (GetState() == DededeState::JUMP &&
		JumpTime_ > 1.0f)
	{
		SetState(DededeState::JUMPDOWN);
	}
	if (GetState() == DededeState::FLYDOWNATTACK &&
		FlyAttackTime_ > 1.0f)
	{
		SetState(DededeState::IDLE);
	}
	else if (GetState() == DededeState::FLYUP &&
		FlyUpTime_ > 0.5f)
	{
		SetState(DededeState::FLY);
	}
	else if (PlayerPos_.y < 100 &&
		PlayerPos_.y != 0 &&
		GetState() != DededeState::FLYUP && 
		GetState() != DededeState::FLY &&
		GetState() != DededeState::FLYDOWN &&
		GetState() != DededeState::JUMP &&
		GetState() != DededeState::JUMPDOWN &&
		GetState() != DededeState::ATTACK)
	{
		PlayerFlyPos_ = PlayerPos_;
		SetState(DededeState::FLYUP);
	}
	else if (PlayerPos_.x - GetPosition().x < -150 &&
		GetState() != DededeState::FLYUP &&
		GetState() != DededeState::FLY &&
		GetState() != DededeState::FLYDOWN &&
		GetState() != DededeState::JUMP &&
		GetState() != DededeState::JUMPDOWN &&
		GetState() != DededeState::ATTACK)
	{
		SetState(DededeState::WALK);
	}
	else if (PlayerPos_.x - GetPosition().x > 150 &&
		GetState() != DededeState::FLYUP &&
		GetState() != DededeState::FLY &&
		GetState() != DededeState::FLYDOWN &&
		GetState() != DededeState::JUMP &&
		GetState() != DededeState::JUMPDOWN &&
		GetState() != DededeState::ATTACK)
	{
		SetState(DededeState::WALK);
	}
	else
	{
		if (GetState() != DededeState::FLYUP &&
			GetState() != DededeState::FLY &&
			GetState() != DededeState::FLYDOWN &&
			GetState() != DededeState::FLYDOWNATTACK &&
			GetState() != DededeState::ATTACK &&
			GetState() != DededeState::JUMPDOWN &&
			AttTime_ > 5.0f )
		{
			AttTime_ = 0.0f;
			JumpTime_ = 0;
			SetState(DededeState::JUMP);
		}
		else if (GetState() != DededeState::FLYUP &&
			GetState() != DededeState::FLY &&
			GetState() != DededeState::FLYDOWN &&
			GetState() != DededeState::JUMP &&
			GetState() != DededeState::JUMPDOWN &&
			GetState() != DededeState::ATTACK)
		{
			SetState(DededeState::ATTACK);
		}
	}

	if (GetState() == DededeState::ATTACK && Renderer_->IsEndAnimation())
	{
		SetState(DededeState::IDLE);
	}
	else if (GetState() == DededeState::JUMPDOWN && Renderer_->IsEndAnimation())
	{
		SetState(DededeState::IDLE);
	}
}

void Dedede::SetState(DededeState _DededeState)
{
	DededeState_ = _DededeState;
	switch (DededeState_)
	{
	case DededeState::IDLE:
		Renderer_->ChangeAnimation("Idle" + Direction_);
		break;
	case DededeState::WALK:
		Renderer_->ChangeAnimation("Walk" + Direction_);
		break;
	case DededeState::ATTACK:
		Renderer_->ChangeAnimation("Attack" + Direction_);
		break;
	case DededeState::DIE:
		Renderer_->ChangeAnimation("Die" + Direction_);
		break;
	case DededeState::FLYUP:
		FlyUpTime_ = 0.0f;
		Renderer_->ChangeAnimation("FlyUp" + Direction_);
		break;
	case DededeState::FLY:
		Renderer_->ChangeAnimation("Fly" + Direction_);
		break;
	case DededeState::FLYDOWN:
		Renderer_->ChangeAnimation("FlyDown" + Direction_);
		break;
	case DededeState::FLYDOWNATTACK:
		FlyAttackTime_ = 0.0f;
		Renderer_->ChangeAnimation("FlyDownAttack" + Direction_);
		break;
	case DededeState::JUMP:
		Renderer_->ChangeAnimation("Jump" + Direction_);
		break;
	case DededeState::JUMPDOWN:
		Renderer_->ChangeAnimation("JumpDown" + Direction_);
		break;
	case DededeState::YELL:
		Renderer_->ChangeAnimation("Yell" + Direction_);
		break;
	}

}


void Dedede::StateUpdate()
{
	switch (DededeState_)
	{
	case DededeState::IDLE:
		UpdateIdle();
		break;
	case DededeState::WALK:
		UpdateWalk();
		break;
	case DededeState::ATTACK:
		UpdateAttack();
		break;
	case DededeState::DIE:
		UpdateDie();
		break;
	case DededeState::FLYUP:
		UpdateFlyUp();
		break;
	case DededeState::FLY:
		UpdateFly();
		break;
	case DededeState::FLYDOWN:
		UpdateFlyDown();
		break;
	case DededeState::FLYDOWNATTACK:
		UpdateFlyDownAttack();
		break;
	case DededeState::JUMP:
		UpdateJump();
		break;
	case DededeState::JUMPDOWN:
		UpdateJumpDown();
		break;
	case DededeState::YELL:
		UpdateYell();
		break;
	}
}

void Dedede::Render()
{

}
