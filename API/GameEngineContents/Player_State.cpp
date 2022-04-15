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

void Player::UpdateTransform()
{
    //Death();
    SetKirbyClass(KirbyClass::SPARK);
}

void Player::UpdateTransformEnd()
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
    SetState(KirbyState::FLYSTAY);
}

void Player::UpdateFlyStay()
{
    AccGravity_ = 0;
    JumpHeight_ = 0;

    SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
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
    if (HPCount_ != 0)
    {
        // 각 레벨의 시작 위치로 가고 idle되기
        SetState(KirbyState::IDLE);
    }

    else
    {
        
    }

}

void Player::UpdateUp()
{
    //if (GetKirbyClass() == KirbyClass::ANIMAL)
    //{
    AccGravity_ = 0;
    JumpHeight_ = 0;
        SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
        UpdateWalk();
        UpdateRun();
    //}
    //else
    //{
    //    SetKirbyClass(KirbyClass::DEFAULT);
    //    SetState(KirbyState::IDLE);
    //}
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
	std::vector <GameEngineCollision*> ColResult;
    if (true == EatCol_->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
    {
        for (GameEngineCollision* Collision : ColResult)
        {
            GameEngineActor* Actor = Collision->GetActor();
            Monster* Monster_ = dynamic_cast<Monster*>(Actor);
            if (nullptr != Monster_)
            {
                float4 MonPos = GetPosition() - Monster_->GetPosition();
                if (MonPos.x > 0) // 내가 오른쪽
                {
                    Monster_->SetMove(-MonPos * GameEngineTime::GetDeltaTime()* 5); // need to chk : (1) 속도 (2) 애니메이션 반복
                }
                if (MonPos.x < 0) // 내가 왼쪽 
                {
                    Monster_->SetMove(MonPos * GameEngineTime::GetDeltaTime()* 5);
                }
                if (true == KirbyCol_->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
                {
                    MonName_ = Monster_->GetNameCopy();
                    Monster_->Death();
                    ////need to chk : next animation
                }
            }
        }
    }
}

void Player::UpdateEatEnd()
{
    if (true == GameEngineInput::GetInst()->IsUp("Eat"))
    {
        SetState(KirbyState::STARATTACK);
    }

    if (KirbyClass::DEFAULT == GetKirbyClass())
    {
        if (true == GameEngineInput::GetInst()->IsUp("Transform"))
        {
            //if(MonName_ == "Sparky")
            //{
            //	SetKirbyClass(KirbyClass::SPARK);
            //}

            SetState(KirbyState::TRANSFORM);
        }
    }
}


void Player::UpdateJumpUp()
{
    JumpHeight_ = 15;
    AccGravity_ = 0;
    
    //SetState(KirbyState::JUMPDOWN);
    UpdateWalk();
    UpdateRun();
} 

void Player::UpdateJumping()
{
    if (true == Renderer_->IsAnimationName("JumpingRight") && true == Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::JUMPDOWN);
    }

    if (true == Renderer_->IsAnimationName("JumpingLeft") && true == Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::JUMPDOWN);
    }
    UpdateWalk();
    UpdateRun();
}

void Player::UpdateJumpDown()
{
    UpdateWalk();

    if (true == Renderer_->IsAnimationName("JumpDownRight") && true == Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::IDLE);
    }
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
    // 멈추기
}
