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
#include "SparkAttackEffect.h"
#include "BeamAttackEffect.h"
#include "FireAttackEffect.h"
#include "AbandonEffect.h"
#include "Box.h"

void Player::UpdateIdle()
{
    KirbyEatCol_->Off();
    //SparkAttackEffect_->Off();
    //FireAttackEffect_->Off();
    //IceAttackEffect_->Off();
    //AnimalCol_->Off();
    //SwordCol_->Off();
    //KirbySlideCol_->Off();
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

void Player::UpdateTakeDamage()
{
    std::vector<GameEngineCollision*> ColResult;
    if (true == KirbyCol_->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
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
                    if (StartPos.x - GetPosition().x < -20)
                    {
                        float4 Dir = float4::RIGHT;
                        float4 Move = Dir * GameEngineTime::GetDeltaTime() * 100;
                        SetMove(Move);
                    }
                }
                if (MoveDir > 0)
                {
                    if (StartPos.x - GetPosition().x > 20)
                    {
                        float4 Dir = float4::LEFT;
                        float4 Move = Dir * GameEngineTime::GetDeltaTime() * 100;
                        SetMove(Move);
                    }
                }

                if (GetHP() <= 0)
                {
                    SetState(KirbyState::DIE);
                }
            }
        }
    }
}

void Player::UpdateWalk()
{
    float4 direction = float4::ZERO;
    if (true == GameEngineInput::GetInst()->IsPress("Left"))
    {
        direction = float4::LEFT;
        //Dir_ = "Left";
    }
    
    else if (true == GameEngineInput::GetInst()->IsPress("Right"))
    {
        direction = float4::RIGHT;
        //Dir_ = "Right";

    }

    SetMove(direction * GameEngineTime::GetDeltaTime() * Speed_);
}

void Player::UpdateRun()
{
    float4 direction = float4::ZERO;
    if (true == GameEngineInput::GetInst()->IsPress("Left"))
    {
        direction = float4::LEFT;
        //Dir_ = "Left";
    }

    else if (true == GameEngineInput::GetInst()->IsPress("Right"))
    {
        direction = float4::RIGHT;
        //Dir_ = "Right";

    }


    SetMove(direction * GameEngineTime::GetDeltaTime() * (Speed_ * 2));
}

void Player::UpdateFly()
{
}

void Player::UpdateFlyStay()
{
    if (GetKirbyClass() == KirbyClass::SPARK)
    {
        SparkRenderer_->ChangeAnimation("FlyStay" + Dir_);
    }
    if (GetKirbyClass() == KirbyClass::DEFAULT)
    {
        Renderer_->ChangeAnimation("FlyStay" + Dir_);
    }
    if (GetKirbyClass() == KirbyClass::ICE)
    {
        IceRenderer_->ChangeAnimation("FlyStay" + Dir_);
    }
    if (GetKirbyClass() == KirbyClass::SWORD)
    {
        SwordRenderer_->ChangeAnimation("FlyStay" + Dir_);
    }
    if (GetKirbyClass() == KirbyClass::ANIMAL)
    {
        AnimalRenderer_->ChangeAnimation("FlyStay" + Dir_);
    }
    if (GetKirbyClass() == KirbyClass::FIRE)
    {
        FireRenderer_->ChangeAnimation("FlyStay" + Dir_);
    }
    if (GetKirbyClass() == KirbyClass::BEAM)
    {
        BeamRenderer_->ChangeAnimation("FlyStay" + Dir_);
    }

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

	if (SwordCol_ != nullptr && GetKirbyClass() == KirbyClass::SWORD)
	{
		if (Dir_ == "Right")
		{
			SwordCol_->On();
			SwordCol_->SetPivot(float4(50.0f, -30.0f));
		}
		else if (Dir_ == "Left")
		{
			SwordCol_->On();
			SwordCol_->SetPivot(float4(-50.0f, -30.0f));
		}
	}

    if (AnimalCol_ != nullptr && GetKirbyClass() == KirbyClass::ANIMAL)
    {
        if (Dir_ == "Right")
        {
            AnimalCol_->On();
            AnimalCol_->SetPivot(float4(30.0f, -15.0f));
        }
        else if (Dir_ == "Left")
        {
            AnimalCol_->On();
            AnimalCol_->SetPivot(float4(-30.0f, -15.0f));
        }
    }
}

void Player::UpdateDie()
{
	float Jump = (Gravity_ * GameEngineTime::GetDeltaTime() * 5);
	JumpHeight_ = JumpHeight_ - Jump;
	float4 JumpDirection = JumpHeight_ > 0 ? float4::UP : float4::DOWN;
    if (GetPosition().y > GetLevel()->GetMapSizeY())
    {
        SetState(KirbyState::IDLE);
        --HPCount_;
        SetHP(10);
        SetPosition(MapStartPos_);
    }
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
        KirbyEatCol_->On();
        KirbyEatCol_->SetScale(float4(100.0f, 50.0f));
        KirbyEatCol_->SetPivot(float4(50.0f, -20.0f));
    }

    if (Dir_ == "Left")
    {
        KirbyEatCol_->On();
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
                if (MonPos.x > 0) // ���� ������
                {
                    Monster_->SetMove(MonPos * GameEngineTime::GetDeltaTime()* 5); 
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
        MonClass_ = Monster_->GetMonsterClass();
        Monster_->Death();
        Monster_ = nullptr;
    }
   
    KirbyEatCol_->Off();
}

void Player::UpdateAttackStay()
{

    if (IceAttackEffect_ != nullptr && GetKirbyClass() == KirbyClass::ICE)
    {
        IceAttackEffect_->SetPosition(GetPosition());
        if (Dir_ == "Right")
        {
            IceAttackEffect_->On();
            IceAttackEffect_->SetState(IceAttackEffectState::IceAttackEffectRight);
        }
        else if (Dir_ == "Left")
        {
            IceAttackEffect_->On();
            IceAttackEffect_->SetState(IceAttackEffectState::IceAttackEffectLeft);
        }
    }

    if (FireAttackEffect_ != nullptr && GetKirbyClass() == KirbyClass::FIRE)
    {
        FireAttackEffect_->SetPosition(GetPosition());
        if (Dir_ == "Right")
        {
            FireAttackEffect_->On();
            FireAttackEffect_->SetState(FireAttackEffectState::FireAttackEffectRight);
        }
        else if (Dir_ == "Left")
        {
            FireAttackEffect_->On();
            FireAttackEffect_->SetState(FireAttackEffectState::FireAttackEffectLeft);
        }
    }

    if (SparkAttackEffect_ != nullptr && GetKirbyClass() == KirbyClass::SPARK)
    {
        SparkAttackEffect_->On();
        SparkAttackEffect_->SetPosition(GetPosition());
        SparkAttackEffect_->SetState(SparkAttackEffectState::SparkAttackEffect);
    }

    if (BeamAttackEffect_ != nullptr && GetKirbyClass() == KirbyClass::BEAM)
    {
        BeamAttackEffect_->SetPosition(GetPosition());
        if (Dir_ == "Right")
        {
            BeamAttackEffect_->SetState(BeamAttackEffectState::BeamRightAttackEffect);

        }
        else if (Dir_ == "Left")
        {
            BeamAttackEffect_->SetState(BeamAttackEffectState::BeamLeftAttackEffect);
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
    float Range = 0;
    float4 Distance = GetPosition() - StartPos_;
    if (Dir_ == "Right")
    {
        KirbySlideCol_->On();
        direction = float4::RIGHT;
        Range = 50;
        if (Distance.x < Range)
        {
            SetMove(direction * GameEngineTime::GetDeltaTime() * 100);
        }
		if (GetKirbyClass() == KirbyClass::DEFAULT || 
            GetKirbyClass() == KirbyClass::ANIMAL ||
            GetKirbyClass() == KirbyClass::ICE ||
            GetKirbyClass() == KirbyClass::BEAM)
		{
			KirbySlideCol_->SetPivot(float4(20.0f, -15.0f));
		}
		if (GetKirbyClass() == KirbyClass::FIRE ||
            GetKirbyClass() == KirbyClass::SPARK)
		{
			KirbySlideCol_->SetPivot(float4(35.0f, -15.0f));
			KirbySlideCol_->SetScale(float4(50.0f, 35.0f));
		}

        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            KirbySlideCol_->SetPivot(float4(40.0f, -15.0f));
            KirbySlideCol_->SetScale(float4(60.0f, 35.0f));
		}
    }
    if (Dir_ == "Left")
    {
        KirbySlideCol_->On();
        direction = float4::LEFT;
        Range = -50;
        if (Distance.x > Range)
        {
            SetMove(direction * GameEngineTime::GetDeltaTime() * 100);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT ||
            GetKirbyClass() == KirbyClass::ANIMAL ||
            GetKirbyClass() == KirbyClass::ICE)
        {
            KirbySlideCol_->SetScale(float4(35.0f, 35.0f));
            KirbySlideCol_->SetPivot(float4(-20.0f, -15.0f));
        }
        if (GetKirbyClass() == KirbyClass::FIRE ||
            GetKirbyClass() == KirbyClass::SPARK)
        {
            KirbySlideCol_->SetPivot(float4(-35.0f, -15.0f));
            KirbySlideCol_->SetScale(float4(50.0f, 35.0f));
        }

        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            KirbySlideCol_->SetPivot(float4(-40.0f, -15.0f));
            KirbySlideCol_->SetScale(float4(60.0f, 35.0f));
        }
    }

    std::vector<GameEngineCollision*> Result;
    if (true == KirbySlideCol_->CollisionResult("BasicMonster", Result, CollisionType::Rect, CollisionType::Rect) &&
        Time_ >= 1)
    {
		Time_ = 0;
        for (GameEngineCollision* Collision : Result)
        {
            Monster* ColMonster = dynamic_cast<Monster*>(Collision->GetActor());
            if (ColMonster != nullptr)
            {
                ColMonster->SetHP(ColMonster->GetHP() - 1);
            }
        }
    }

    std::vector<GameEngineCollision*> MonsterColResult;
    if ((true == AnimalCol_->CollisionResult("BasicMonster", MonsterColResult, CollisionType::Rect, CollisionType::Rect) ||
        true == SwordCol_->CollisionResult("BasicMonster", MonsterColResult, CollisionType::Rect, CollisionType::Rect))  &&
        Time_ >= 1)
    {
        Time_ = 0;
        for (GameEngineCollision* Collision : MonsterColResult)
        {
            Monster* ColMonster = dynamic_cast<Monster*>(Collision->GetActor());
            if (ColMonster != nullptr)
            {
                ColMonster->SetHP(ColMonster->GetHP() - 2);
            }
        }
    }
}

void Player::UpdateAbandon()
{

}
