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
#include "AttackEffect.h"
#include "IceAttackEffect.h"
#include "Box.h"

void Player::UpdateIdle()
{

}

void Player::UpdateTransform()
{
}

void Player::UpdateTransformEnd()
{

}

//void Player::UpdateOpenDoor()
//{
//	//if (true == KirbyCol_->CollisionCheck("DoorCol1_2", CollisionType::Rect, CollisionType::Rect))
//	//{
//	//	GameEngine::GetInst().ChangeLevel("Level1_2");
//	//}
//}

// need to chk : 왜 여기로 안들어오는지
void Player::UpdateTakeDamage()
{
    SetHP(GetHP() - 1);
    std::vector<GameEngineCollision*> ColResult;
    if (KirbyCol_->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
    {
        float4 StartPos = GetPosition();
        for (GameEngineCollision* CenterCol : ColResult)
        {
            Monster* CenterColMonster = dynamic_cast<Monster*>(CenterCol->GetActor());
            if (CenterColMonster != nullptr)
            {
                float MoveDir = CenterColMonster->GetPosition().x - GetPosition().x;
                if (MoveDir <= 0)
                {
                    if (StartPos.x - GetPosition().x > -20)
                    {
                        float4 Dir = float4::RIGHT;
                        float4 Move = Dir * GameEngineTime::GetDeltaTime() * 20;
                        SetMove(Move);
                    }
                }
                if (MoveDir > 0)
                {
                    if (StartPos.x - GetPosition().x < 20)
                    {
                        float4 Dir = float4::LEFT;
                        float4 Move = Dir * GameEngineTime::GetDeltaTime() * 20;
                        SetMove(Move);
                    }
                }
            }
        }
    }

	if (GetHP() <= 0)
	{
		SetState(KirbyState::DIE);
		--HPCount_;
	}
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


    SetMove(direction * GameEngineTime::GetDeltaTime() * (Speed_ * 2));
}

void Player::UpdateFly()
{
}

void Player::UpdateFlyStay()
{
    JumpHeight_ = 0;

    SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
    UpdateWalk();
}

void Player::UpdateFlyAttack()
{
	if (AttackEffect_ != nullptr)
	{
        AttackEffect_->SetPosition(GetPosition()); // need to chk : the pos;
		if (Dir_ == "Right")
		{
            AttackEffect_->SetState(AttackEffectState::AttackEffectRight);
		}
		else if (Dir_ == "Left")
		{
            AttackEffect_->SetState(AttackEffectState::AttackEffectLeft);
		}
	}

    UpdateWalk();
}

void Player::UpdateFlyEnd()
{
    UpdateWalk();
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
        MonClass_ = MonsterClass::NONE;
        //SetKirbyAttackEffet(KirbyAttackEffect::AttackStart);
        //PigAttackRenderer_->SetPivot(float4(100.0f, 0.0f));
    }
}

void Player::UpdateDie()
{
    //need to chk colmap 무시하고 애니메이션 하면서 바닥으로 떨어짐
   // SetMove(float4::DOWN);
}

void Player::UpdateUp()
{
    //if (GetKirbyClass() == KirbyClass::ANIMAL)
    //{
	/*JumpHeight_ = 0;
	SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	UpdateWalk();
	UpdateRun();*/
    //}
    //else
    //{
    //    SetKirbyClass(KirbyClass::DEFAULT);
    //    SetState(KirbyState::IDLE);
    //}
}

void Player::UpdateDown()
{
    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x, GetPosition().y+1))
    {
        SetMove(float4::DOWN);
    }
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
        KirbyEatCol_->SetScale(float4(100.0f, 50.0f));
        KirbyEatCol_->SetPivot(float4(50.0f, -20.0f));
    }

    if (Dir_ == "Left")
    {
        KirbyEatCol_->SetScale(float4(100.0f, 50.0f));
        KirbyEatCol_->SetPivot(float4(-50.0f, -20.0f));
    }

	std::vector <GameEngineCollision*> ColResult;
    if (true == KirbyEatCol_->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
    {
        for (GameEngineCollision* Collision : ColResult)
        {
            GameEngineActor* Actor = Collision->GetActor();
            Monster_ = dynamic_cast<Monster*>(Actor);
            if (nullptr != Monster_)
            {
                float4 MonPos = GetPosition() - Monster_->GetPosition();
                if (MonPos.x > 0) // 내가 오른쪽
                {
                    Monster_->SetMove(MonPos * GameEngineTime::GetDeltaTime()* 5); // need to chk : (1) 속도 (2) 애니메이션 반복
                }
                if (MonPos.x < 0) // 내가 왼쪽 
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
        MonClass_ = Monster_->GetMonsterClass();
        Monster_->Death();
        Monster_ = nullptr;
        KirbyEatCol_->SetScale(float4(0.0f, 0.0f));
    }
}

void Player::UpdateAttackStay()
{
    if (IceAttackEffect_ != nullptr && GetKirbyClass() == KirbyClass::ICE)
    {
        IceAttackEffect_->SetPosition(GetPosition()); // need to chk : the pos;
        if (Dir_ == "Right")
        {
            IceAttackEffect_->SetState(IceAttackEffectState::IceAttackEffectRight);
        }
        else if (Dir_ == "Left")
        {
            IceAttackEffect_->SetState(IceAttackEffectState::IceAttackEffectLeft);
        }
    }
}

void Player::UpdateJumpUp()
{
    UpdateWalk();
} 

void Player::UpdateJumping()
{
    UpdateWalk();
}

void Player::UpdateJumpDown()
{
    UpdateWalk();
}

void Player::UpdateSlide()
{
    float4 direction = float4::ZERO;
    if (true == GameEngineInput::GetInst()->IsPress("Left"))
    {
        direction = float4::LEFT;
        SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 500);
        Dir_ = "Left";
        KirbySlideCol_->SetScale(float4(30.0f, 30.0f));
        KirbySlideCol_->SetPivot(float4(-20.0f, -15.0f));

        //float4 Distance = GetPosition() - StartPos_;
    }

   else if (true == GameEngineInput::GetInst()->IsPress("Right"))
    {
        direction = float4::RIGHT;
        SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 500);
        Dir_ = "Right";
        KirbySlideCol_->SetScale(float4(30.0f, 30.0f));
        KirbySlideCol_->SetPivot(float4(20.0f, -15.0f));

       // float4 Distance = GetPosition() - StartPos_;
    }
}
