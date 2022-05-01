#include "Dedede.h"
#include <GameEngine/GameEngineRenderer.h>

void Dedede::UpdateIdle()
{
	Dir_ = float4::ZERO;
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
}

void Dedede::UpdateWalk()
{
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
}

void Dedede::UpdateJump()
{
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_ * 2);
}

void Dedede::UpdateAttack()
{
	SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
}

void Dedede::UpdateYell()
{
}

void Dedede::UpdateFly()
{
}

void Dedede::UpdateDie()
{
}
