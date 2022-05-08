#include "Dedede.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImage.h>
#include "StarMonster.h"

void Dedede::UpdateIdle()
{
	Dir_ = float4::ZERO;
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * GetSpeed());
}

void Dedede::UpdateWalk()
{
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * GetSpeed());
}

void Dedede::UpdateJump()
{
	JumpTime_ += GameEngineTime::GetDeltaTime();
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * GetSpeed() * 2);
	Collision_->SetPivot(float4(0, -200));	
}

void Dedede::UpdateJumpDown()
{
	Collision_->SetPivot(float4(0, -85));
}

void Dedede::UpdateAttack()
{
}

void Dedede::UpdateYell()
{
}

void Dedede::UpdateFlyUp()
{
	FlyUpTime_ += GameEngineTime::GetDeltaTime();	
}

void Dedede::UpdateFly()
{
	if (PlayerFlyPos_.y < GetPosition().y - 50)
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * GetSpeed());
	}
	else
	{
		if (PlayerFlyPos_.x - GetPosition().x > 80)
		{
			SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * GetSpeed());
		}
		else if(PlayerFlyPos_.x - GetPosition().x < -80)
		{
			SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * GetSpeed());
		}
		else
		{
			SetState(DededeState::FLYDOWN);
		}
	}	
}

void Dedede::UpdateFlyDown()
{
	if (RGB(0, 0, 0) != ColMapImage_->GetImagePixel(GetPosition() + float4::DOWN))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * GetSpeed());
	}
	else
	{
		SetState(DededeState::FLYDOWNATTACK);
	}
}

void Dedede::UpdateFlyDownAttack()
{
	FlyAttackTime_ += GameEngineTime::GetDeltaTime();
}

void Dedede::UpdateDie()
{
}
