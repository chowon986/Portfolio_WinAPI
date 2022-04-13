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
    if (Renderer_->IsEndAnimation())
    {
        SetKirbyClass(KirbyClass::SPARK);
    }
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
    if (HPCount_ != 0)
    {
        // �� ������ ���� ��ġ�� ���� idle�Ǳ�
        SetState(KirbyState::IDLE);
    }

    else
    {
        
    }

}

void Player::UpdateUp()
{
    if (GetKirbyClass() == KirbyClass::ANIMAL)
    {
        SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
    }
    else
    {
        SetKirbyClass(KirbyClass::DEFAULT);
        SetState(KirbyState::IDLE);
    }
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
    if (Renderer_->IsAnimationName("EatStartRight") && Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::EAT);
    }
}

void Player::UpdateEat()
{
    // need : EatCol ���� ���� Ȯ�� �� ��ġ Ŀ��� �ű��
    GameEngineCollision* EatCol = CreateCollision("EatCol", float4(10.0f, 10.0f), float4(100.0f, 0.0f));

	std::vector <GameEngineCollision*> ColResult;
    if (true == EatCol->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
    {
        for (GameEngineCollision* Collision : ColResult)
        {
            GameEngineActor* Actor = Collision->GetActor();
            Monster* Monster_ = dynamic_cast<Monster*>(Actor);
            if (nullptr != Monster_)
            {
                float4 MonPos = GetPosition() - Monster_->GetPosition();
                if (MonPos.x > 0) // ���� ������
                {
                    Monster_->SetPosition(Monster_->GetPosition() + MonPos);
                }
                if (MonPos.x < 0) // ���� ����
                {
                    Monster_->SetPosition(Monster_->GetPosition() - MonPos);
                }
                else
                {
                    MonName_ = Monster_->GetNameCopy();
                   // Monster_->Death();
                    SetState(KirbyState::EATEND);
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
    JumpHeight_ = 25;
    AccGravity_ = 0;
    UpdateWalk();
} 

void Player::UpdateJumping()
{
    if (Renderer_->IsAnimationName("JumpingRight") && Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::JUMPDOWN);
    }

    if (Renderer_->IsAnimationName("JumpingLeft") && Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::JUMPDOWN);
    }

    UpdateWalk();
}

void Player::UpdateJumpDown()
{
    UpdateWalk();
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
    // ���߱�
}
