#include "Dedede.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "IceAttackEffect.h"

Dedede::Dedede()
	: Monster()
	, Time_(0.0f)
	, AttTime_(0.0f)
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

	Renderer_ = CreateRenderer("KingDedede.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 7);
	Renderer_->CreateAnimation("KingDedede.bmp", "IdleRight", 0, 3, 0.2f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "IdleLeft", 32, 35, 0.2f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "WalkRight", 4, 7, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "WalkLeft", 36, 39, 0.1f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "JumpRight", 8, 10, 0.6f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "JumpLeft", 40, 42, 0.6f, true);

	Renderer_->CreateAnimation("KingDedede.bmp", "AttackRight", 11, 20, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "AttackLeft", 43, 52, 0.1f, true);

	// HP가 어느 이상 줄면
	Renderer_->CreateAnimation("KingDedede.bmp", "YellRight", 21, 24, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "YellLeft", 53, 56, 0.1f, true);


	Renderer_->CreateAnimation("KingDedede.bmp", "FlyRight", 25, 27, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "FlyLeft", 57, 59, 0.1f, true);


	Renderer_->CreateAnimation("KingDedede.bmp", "DieRight", 29, 31, 0.1f, true);
	Renderer_->CreateAnimation("KingDedede.bmp", "DieLeft", 61, 63, 0.1f, true);
	Renderer_->ChangeAnimation("WalkRight");

	SetHP(10);
	SetSpeed(30);
	Collision_ = CreateCollision("BasicMonster", float4(150.0f, 180.0f), float4(0.0f, -90.0f));
	//EffectRenderer_ = CreateRenderer("MonsterDie.bmp");
	//GameEngineImage* EffectImage = EffectRenderer_->GetImage();
	//EffectImage->CutCount(10, 3);
	//EffectRenderer_->CreateAnimation("MonsterDie.bmp", "DieEffect", 0, 24, 0.05f, true);
	//EffectRenderer_->ChangeAnimation("DieEffect");
	//EffectRenderer_->SetAlpha(0);

	Dir_ = float4::LEFT;
	Direction_ = "Left";
}


void Dedede::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();
	AttTime_ += GameEngineTime::GetDeltaTime();
	UpdateMove();
	StateUpdate();
}

void Dedede::UpdateMove()
{
	// 3초에 한 번씩
	if (Time_ > 3.0f)
	{
		PlayerPos_ = Player_->GetPosition();
		Time_ = 0.0f;
	}

	if (PlayerPos_.x - GetPosition().x < -150)
	{
		Dir_ = float4::LEFT;
		Direction_ = "Left";
		SetState(DededeState::WALK);
	}
	else if (PlayerPos_.x - GetPosition().x > 150)
	{
		Dir_ = float4::RIGHT;
		Direction_ = "Right";
		SetState(DededeState::WALK);
	}
	else
	{
		if (GetState() == DededeState::IDLE && AttTime_ > 2.5f )
		{
			if (Direction_ == "Right")
			{
				Dir_ = float4::RIGHT;
				AttTime_ = 0.0f;
			}
			else
			{
				Dir_ = float4::LEFT;
				AttTime_ = 0.0f;
			}
			SetState(DededeState::JUMP);
		}

		else if (GetState() != DededeState::IDLE && GetState() != DededeState::JUMP)
		{
			SetState(DededeState::ATTACK);
			AttTime_ = 0.0f;
		}

	}


	if (GetState() != DededeState::WALK && true == Renderer_->IsEndAnimation())
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
	case DededeState::FLY:
		Renderer_->ChangeAnimation("Fly" + Direction_);
		break;
	case DededeState::JUMP:
		Renderer_->ChangeAnimation("Jump" + Direction_);
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
	case DededeState::FLY:
		UpdateFly();
		break;
	case DededeState::JUMP:
		UpdateJump();
		break;
	case DededeState::YELL:
		UpdateYell();
		break;
	}
}

void Dedede::Render()
{

}
