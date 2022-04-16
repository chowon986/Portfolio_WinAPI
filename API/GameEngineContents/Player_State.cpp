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
#include "StarAttackEffect.h"

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
    if (true == GameEngineInput::GetInst()->IsPress("Left"))
    {
        direction = float4::LEFT;
        Dir_ = "Left";
    }
    else if (true == GameEngineInput::GetInst()->IsPress("Right"))
    {
        direction = float4::RIGHT;
        Dir_ = "Right";
    }
    
    SetMove(direction * GameEngineTime::GetDeltaTime() * Speed_);
}

void Player::UpdateRun()
{
    float4 direction = float4::ZERO;
    if (true == GameEngineInput::GetInst()->IsPress("Left"))
    {
        direction = float4::LEFT;
        Dir_ = "Left";
    }
    else if (true == GameEngineInput::GetInst()->IsPress("Right"))
    {
        direction = float4::RIGHT;
        Dir_ = "Right";
    }

    SetMove(direction * GameEngineTime::GetDeltaTime() * Speed_ * 2);
}

void Player::UpdateFly()
{
//need to chk
    //if (true == Renderer_->IsEndAnimation())
    //{
    SetState(KirbyState::FLYSTAY);

    //}
}

void Player::UpdateFlyStay()
{
    AccGravity_ = 0;
    JumpHeight_ = 0;

    if (true == GameEngineInput::GetInst()->IsUp("Fly"))
    {
        SetState(KirbyState::FLYATTACK);
    }
    SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
    UpdateWalk();
}

void Player::UpdateFlyAttack()
{
    SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_ * AccGravity_);
    if (true == Renderer_->IsEndAnimation())
    {
        SetState(KirbyState::FLYEND);
    }
}

void Player::UpdateAttack()
{
    if (KirbyClass::PIG == GetKirbyClass())
    {
        if (StarAttackEffect_ != nullptr)
        {
            StarAttackEffect_->SetPosition(GetPosition()); // need to chk : the pos;
            if (Dir_ == "Right")
            {
                StarAttackEffect_->SetState(StarAttackEffectState::AttackStartRight);
            }
            else if (Dir_ == "Left")
            {
                StarAttackEffect_->SetState(StarAttackEffectState::AttackStartLeft);
            }
        }


        //PigAttackRenderer_->SetAlpha(255);
        //PigAttackCol_->SetScale(float4(50.0f, 50.0f));
        MonName_ = "";
        //SetKirbyAttackEffet(KirbyAttackEffect::AttackStart);
        //PigAttackRenderer_->SetPivot(float4(100.0f, 0.0f));
    }
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
    if (Dir_ == "Right")
    {
        EatCol_->SetScale(float4(100.0f, 50.0f));
        EatCol_->SetPivot(float4(50.0f, -20.0f));
    }

    if (Dir_ == "Left")
    {
        EatCol_->SetScale(float4(100.0f, 50.0f));
        EatCol_->SetPivot(float4(-50.0f, -20.0f));
    }

	std::vector <GameEngineCollision*> ColResult;
    if (true == EatCol_->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
    {
        for (GameEngineCollision* Collision : ColResult)
        {
            GameEngineActor* Actor = Collision->GetActor();
            Monster_ = dynamic_cast<Monster*>(Actor);
            if (nullptr != Monster_)
            {
                float4 MonPos = GetPosition() - Monster_->GetPosition();
                if (MonPos.x > 0) // ���� ������
                {
                    Monster_->SetMove(MonPos * GameEngineTime::GetDeltaTime()* 5); // need to chk : (1) �ӵ� (2) �ִϸ��̼� �ݺ�
                }
                if (MonPos.x < 0) // ���� ���� 
                {
                    Monster_->SetMove(MonPos * GameEngineTime::GetDeltaTime()* 5);
                }
            }
        }
    }
}

void Player::UpdateEatEnd()
{
    if (nullptr != Monster_)
    {
        MonName_ = Monster_->GetNameCopy();
        Monster_->Death();
        Monster_ = nullptr;
        EatCol_->SetScale(float4(0.0f, 0.0f));
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
    if (true == GameEngineInput::GetInst()->IsPress("Left"))
    {
        direction = float4::LEFT;
        Dir_ = "Left";
    }
    else if (true == GameEngineInput::GetInst()->IsPress("Right"))
    {
        direction = float4::RIGHT;
        Dir_ = "Right";
    }

    if (Renderer_->IsEndAnimation())
    {
        //SetState(KirbyState::SLIDESTAY);
    }
}
