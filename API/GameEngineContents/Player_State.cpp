#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include "Monster.h"

void Player::UpdateIdle()
{

}

void Player::UpdateWalk()
{
    float4 direction = float4::ZERO;
    if (true == GameEngineInput::GetInst()->IsPress("WalkLeft"))
    {
        direction = float4::LEFT;

    }
    else if (true == GameEngineInput::GetInst()->IsPress("WalkRight"))
    {
        direction = float4::RIGHT;
    }

    SetMove(direction * GameEngineTime::GetDeltaTime() * Speed_);
}

void Player::UpdateRun()
{
    float4 direction = float4::ZERO;
    if (true == GameEngineInput::GetInst()->IsPress("RunLeft"))
    {
        direction = float4::LEFT;

    }
    else if (true == GameEngineInput::GetInst()->IsPress("RunRight"))
    {
        direction = float4::RIGHT;
    }

    SetMove(direction * GameEngineTime::GetDeltaTime() * Speed_ * 2);
}

void Player::UpdateFly()
{
    if (true == Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::FLYSTAY);
    }
}


void Player::UpdateFlyStay()
{
    // 나는거 -> 날다가 키를 놓으면 kirbystate가 flyattack으로 바껴야함
    SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
    AccGravity_ = 0;
    JumpHeight_ = 0;
    if (true == GameEngineInput::GetInst()->IsUp("Fly"))
    {
        SetState(KirbyState::FLYATTACK);
    }
}

void Player::UpdateFlyAttack()
{
    SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_ * AccGravity_);
}

void Player::UpdateAttack()
{
}

void Player::UpdateDie()
{
}

void Player::UpdateUp()
{
    SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);

}

void Player::UpdateDown()
{
    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x, GetPosition().y))
    {
        Speed_ = 0;
        SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
    }
    SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
}

void Player::UpdateHover()
{
}

void Player::UpdateInhale()
{
}

void Player::UpdateEat()
{
}

void Player::UpdateJump()
{
    float4 JumpDirection = PrevPos_ - GetPosition();
    float JumpDirectionX = JumpDirection.x > 0 ? float4::RIGHT.x : float4::LEFT.x;
    float JumpDirectionY = JumpDirection.y > 0 ? float4::DOWN.y : float4::UP.y;
    AccGravity_ += Gravity_ * GameEngineTime::GetDeltaTime();
    float JumpHeight = JumpHeight_ - AccGravity_;
    SetMove(float4(0, -JumpHeight));
}