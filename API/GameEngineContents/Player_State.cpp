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
        Dir_ = "Left";
    }
    else if (true == GameEngineInput::GetInst()->IsPress("WalkRight"))
    {
        direction = float4::RIGHT;
        Dir_ = "Right";
    }
    
    SetMove(direction * GameEngineTime::GetDeltaTime() * Speed_);
}

void Player::UpdateRun()
{
    float4 direction = float4::ZERO;
    if (true == GameEngineInput::GetInst()->IsPress("RunLeft"))
    {
        direction = float4::LEFT;
        Dir_ = "Left";
    }
    else if (true == GameEngineInput::GetInst()->IsPress("RunRight"))
    {
        direction = float4::RIGHT;
        Dir_ = "Right";
    }

    SetMove(direction * GameEngineTime::GetDeltaTime() * Speed_ * 2);
}

void Player::UpdateFly()
{
    if (true == GameEngineInput::GetInst()->IsPress("Fly") && true == Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::FLYSTAY);
    }
}

void Player::UpdateFlyStay()
{
    if (true == GameEngineInput::GetInst()->IsPress("Fly"))
    {
    SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
    }
}

void Player::UpdateFlyAttack()
{
    //SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_ * AccGravity_);
   // SetState(KirbyState::FLYDOWN);
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
    // æ÷¥œ∏Ù ªÛ≈¬
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

void Player::UpdateEatStart()
{
}

void Player::UpdateEat()
{
}

void Player::UpdateJump()
{
    JumpHeight_ = 10;
    AccGravity_ = 0;
} 

void Player::UpdateSlide()
{
    float4 direction = float4::ZERO;
    if (true == GameEngineInput::GetInst()->IsPress("SlideLeft"))
    {
        direction = float4::LEFT;
        Dir_ = "Left";
    }
    else if (true == GameEngineInput::GetInst()->IsPress("SlideRight"))
    {
        direction = float4::RIGHT;
        Dir_ = "Right";
    }

    if (Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::SLIDESTAY);
    }
}

void Player::UpdateSlideStay()
{
    // ∏ÿ√ﬂ±‚
}