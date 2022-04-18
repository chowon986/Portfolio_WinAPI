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

Player::Player()
    : Renderer_(nullptr)
    , Gravity_(5.0f)
    , JumpHeight_(0.0f)
    , Time_(3.0f)
    , Level_(nullptr)
    , HPCount_(0)
    , Speed_(20)
    , KirbyEatCol_(nullptr)
    , MonClass_(MonsterClass::NONE)
{
}

Player::~Player()
{
}


void Player::SetKirbyClass(KirbyClass _KirbyClass)
{
    KirbyClass_ = _KirbyClass;
    ClassUpdate();
}

KirbyClass Player::GetKirbyClass()
{
	return KirbyClass_;
}

void Player::ClassUpdate()
{
    switch (KirbyClass_)
    {
    case KirbyClass::SPARK:
        Renderer_->SetAlpha(0);
        SparkKirbyRenderer_->SetAlpha(255);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        break;
    case KirbyClass::ANIMAL:
        Renderer_->SetAlpha(0);
        SparkKirbyRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(255);
        break;
    case KirbyClass::DEFAULT:
        Renderer_->SetAlpha(255);
        SparkKirbyRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        // AttackEffectRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        break;
    case KirbyClass::ICE:
        Renderer_->SetAlpha(0);
        SparkKirbyRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(255);
        AnimalRenderer_->SetAlpha(0);
        break;
    case KirbyClass::SWORD:
        Renderer_->SetAlpha(0);
        SparkKirbyRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(255);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        break;
    case KirbyClass::FIRE:
        Renderer_->SetAlpha(0);
        SparkKirbyRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(255);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        break;
    case KirbyClass::PIG:
        Renderer_->SetAlpha(0);
        SparkKirbyRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(255);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        break;
    default:
        break;
    }
}

void Player::SetState(KirbyState _KirbyState)
{
    KirbyState_ = _KirbyState;
    switch (KirbyState_)
    { 
        // case : default, ice, spark, sword, fire, animal
    case KirbyState::IDLE:
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Idle" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("Idle" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Idle" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("Idle" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("Idle" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("Idle" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::PIG)
        {
            PigRenderer_->ChangeAnimation("Idle" + Dir_);
        }
        break;

    case KirbyState::UP: // Animal 사용
        break;

    case KirbyState::DOWN:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Down" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Down" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("Down" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("Down" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("Down" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("Down" + Dir_);
        }
        break;

    case KirbyState::WALK:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Walk" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Walk" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("Walk" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("Walk" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("Walk" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("Walk" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::PIG)
        {
            PigRenderer_->ChangeAnimation("Walk" + Dir_);
        }
        break;

    case KirbyState::RUN:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
		    SparkKirbyRenderer_->ChangeAnimation("Run" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Run" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("Run" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("Run" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("Run" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("Run" + Dir_);
        }
        break;


    case KirbyState::FLY:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Fly" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Fly" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("Fly" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("Fly" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("Fly" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("Fly" + Dir_);
        }
        break;

    case KirbyState::FLYSTAY:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("FlyStay" + Dir_);
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
        break;

    case KirbyState::FLYATTACK:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("FlyAttack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("FlyAttack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("FlyAttack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("FlyAttack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("FlyAttack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("FlyAttack" + Dir_);
        }
        break;

    case KirbyState::FLYEND:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("FlyEnd" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("FlyEnd" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("FlyEnd" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("FlyEnd" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("FlyEnd" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("FlyEnd" + Dir_);
        }
        break;


    case KirbyState::EATSTART:
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("EatStart" + Dir_);
        }
        break;

    case KirbyState::EAT:
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Eat" + Dir_);
        }
        break;

    case KirbyState::EATEND:
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("EatEnd" + Dir_);
        }
        break;


    case KirbyState::ATTACK:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Attack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::PIG)
        {
            PigRenderer_->ChangeAnimation("Attack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("Attack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("Attack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("Attack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("Attack" + Dir_);
        }
        break;
    case KirbyState::TRANSFORM:
        PigRenderer_->ChangeAnimation("Transform" + Dir_);
		break;


    case KirbyState::TAKEDAMAGE:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("GetDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("GetDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("GetDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("GetDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("GetDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("GetDamage" + Dir_);
        }
        break;



    case KirbyState::JUMPUP:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("JumpUp" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("JumpUp" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("JumpUp" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("JumpUp" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("JumpUp" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("JumpUp" + Dir_);
        }
        break;
    case KirbyState::JUMPING:
        if (GetKirbyClass() == KirbyClass::SPARK && GetState() != KirbyState::IDLE)
        {
            SparkKirbyRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT && GetState() != KirbyState::IDLE)
        {
            Renderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        break;
    case KirbyState::JUMPDOWN:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("JumpDown" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("JumpDown" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("JumpDown" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("JumpDown" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("JumpDown" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("JumpDown" + Dir_);
        }
        break;



    case KirbyState::SLIDE:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        break;

    case KirbyState::DIE:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Die" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Die" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("Die" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("Die" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("Die" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("Die" + Dir_);
        }
        break;

    default:
        break;
    }
}


void Player::Update()
{
    if (true == GameEngineInput::GetInst()->IsPress("Left") &&
        false == GameEngineInput::GetInst()->IsPress("Run") &&
        false == GameEngineInput::GetInst()->IsPress("Attack") &&
        false == GameEngineInput::GetInst()->IsPress("Fly") &&
        false == GameEngineInput::GetInst()->IsPress("Jump") &&
        false == GameEngineInput::GetInst()->IsPress("Eat") &&
        false == GameEngineInput::GetInst()->IsPress("Abandon") &&
        KirbyState::FLY != GetState() &&
        KirbyState::SLIDE != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4::DOWN))

    {
        SetState(KirbyState::WALK);
    }
    else if (true == GameEngineInput::GetInst()->IsPress("Right") &&
        false == GameEngineInput::GetInst()->IsPress("Run") &&
        false == GameEngineInput::GetInst()->IsPress("Attack") &&
        false == GameEngineInput::GetInst()->IsPress("Fly") &&
        false == GameEngineInput::GetInst()->IsPress("Jump") &&
        false == GameEngineInput::GetInst()->IsPress("Eat") &&
        false == GameEngineInput::GetInst()->IsPress("Abandon") &&
        KirbyState::FLY != GetState() &&
        KirbyState::SLIDE != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4::DOWN))
    {
        SetState(KirbyState::WALK);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Left") && 
        true == GameEngineInput::GetInst()->IsPress("Run") &&
        false == GameEngineInput::GetInst()->IsPress("Attack") &&
        false == GameEngineInput::GetInst()->IsPress("Fly") &&
        false == GameEngineInput::GetInst()->IsPress("Jump") &&
        false == GameEngineInput::GetInst()->IsPress("Eat") &&
        false == GameEngineInput::GetInst()->IsPress("Abandon") &&
        KirbyState::FLY != GetState() &&
        KirbyState::SLIDE != GetState() && 
        KirbyState::TRANSFORM != GetState() &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4::DOWN))
    {
        SetState(KirbyState::RUN);
    }
    else if (true == GameEngineInput::GetInst()->IsPress("Right") &&
        true == GameEngineInput::GetInst()->IsPress("Run") &&
        false == GameEngineInput::GetInst()->IsPress("Attack") &&
        false == GameEngineInput::GetInst()->IsPress("Fly") &&
        false == GameEngineInput::GetInst()->IsPress("Jump") &&
        false == GameEngineInput::GetInst()->IsPress("Eat") &&
        false == GameEngineInput::GetInst()->IsPress("Abandon") &&
        KirbyState::FLY != GetState() &&
        KirbyState::SLIDE != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4::DOWN))
    {
        SetState(KirbyState::RUN);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Up") &&
        KirbyClass::ANIMAL == GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState()//&&
        /*need to chk RGB(,,)  */)
    {
        SetState(KirbyState::UP);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Down") &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState())
    {
        SetState(KirbyState::DOWN);
    }

    if (true == GameEngineInput::GetInst()->IsDown("Slide") &&
        KirbyState::DOWN == GetState() &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState())
    {
        SetState(KirbyState::SLIDE);
    }

    if (true == GameEngineInput::GetInst()->IsDown("Attack") &&
        KirbyClass::DEFAULT != GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState())
    {
        SetState(KirbyState::ATTACK);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Fly") &&
        GetState() != KirbyState::JUMPUP &&
        GetState() != KirbyState::JUMPING &&
        GetState() != KirbyState::JUMPDOWN &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState())
    {
        if (KirbyState::FLYSTAY != GetState())
        {
            SetState(KirbyState::FLY);
        }

        if (KirbyState::FLY == GetState() &&
            true == Renderer_->IsEndAnimation())
        {
            SetState(KirbyState::FLYSTAY);
        }
    }
    else if (true == GameEngineInput::GetInst()->IsFree("Fly") &&
        (KirbyState::FLYSTAY == GetState() || KirbyState::FLYATTACK == GetState() || KirbyState::FLYEND == GetState()) &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState())
    {
        
        if (KirbyState::FLYEND != GetState())
        {
            SetState(KirbyState::FLYATTACK);
        }

        if (KirbyState::FLYATTACK == GetState() &&
            true == Renderer_->IsEndAnimation())
        {
            SetState(KirbyState::FLYEND);
        }
    }

    if (true == GameEngineInput::GetInst()->IsUp("Jump") &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState() &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4::DOWN)) // 공중에서 점프 불가
    {
        JumpHeight_ = 200;
        SetState(KirbyState::JUMPUP);
    }

    if (true == GameEngineInput::GetInst()->IsUp("Transform") &&
        MonClass_ != MonsterClass::NONE &&
        MonClass_ != MonsterClass::DEFAULT &&
        MonClass_ != MonsterClass::BOSS)
    {
        SetState(KirbyState::TRANSFORM);
    }

    if (true == GameEngineInput::GetInst()->IsPress("ResetPos"))
    {
        SetPosition(float4(205.0, 436.0f));
    }

    if (true == GameEngineInput::GetInst()->IsPress("Eat") &&
        KirbyState::ATTACK != GetState() &&
        KirbyState::DOWN != GetState() &&
        KirbyState::FLY != GetState() &&
        KirbyState::FLYSTAY != GetState() &&
        KirbyState::FLYATTACK != GetState() &&
        KirbyState::EATEND != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        KirbyClass::PIG != GetKirbyClass())
    {
        if (KirbyState::EAT != GetState())
        {
            SetState(KirbyState::EATSTART);
        }        
        if (KirbyState::EATSTART == GetState() &&
            true == Renderer_->IsEndAnimation())
        {
            SetState(KirbyState::EAT);
        }

        if (KirbyState::EAT == GetState() &&
            KirbyCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect)) // Kirby의 Col Monster Coli 가 충돌할 떄)
        {
            SetState(KirbyState::EATEND);
        }
    }

    float Jump = (Gravity_ * GameEngineTime::GetDeltaTime() * 100);
    JumpHeight_ = JumpHeight_ - Jump;
    float4 JumpDirection = JumpHeight_ > 0 ? float4::UP : float4::DOWN;
    if (KirbyState::FLYSTAY == GetState())
    {
        JumpDirection = float4::ZERO;
    }

    SetMove(JumpDirection * Jump);
    // 땅에 닿았을 때
    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4::DOWN) && JumpDirection.y > 0)
    {
        while (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()))
        {
            SetMove(float4::UP);
        }
        SetPosition(float4(GetPosition().ix(), GetPosition().iy()));

        JumpHeight_ = 0;
        if (true == GameEngineInput::GetInst()->IsFree("Left") &&
            true == GameEngineInput::GetInst()->IsFree("Right") &&
            true == GameEngineInput::GetInst()->IsFree("Down") &&
            true == GameEngineInput::GetInst()->IsFree("Slide") &&
            true == GameEngineInput::GetInst()->IsFree("Slide") &&
            true == GameEngineInput::GetInst()->IsFree("Jump") &&
            true == GameEngineInput::GetInst()->IsFree("Fly") &&
            true == GameEngineInput::GetInst()->IsFree("Attack") &&
            (true == GameEngineInput::GetInst()->IsFree("Eat") || (KirbyState::EATEND == GetState() && true == Renderer_->IsEndAnimation())))
        {
            if (GetKirbyClass() != KirbyClass::ANIMAL &&
                GetKirbyClass() != KirbyClass::FIRE &&
                GetKirbyClass() != KirbyClass::ICE &&
                GetKirbyClass() != KirbyClass::SPARK &&
                GetKirbyClass() != KirbyClass::SWORD)
            {
                if (MonClass_ == MonsterClass::NONE)
                {
                    SetKirbyClass(KirbyClass::DEFAULT);
                }
                else
                {
                    SetKirbyClass(KirbyClass::PIG);
                }
            }

            if (KirbyState::TRANSFORM == GetState())
            {
                if (true == PigRenderer_->IsEndAnimation())
                {
                    switch (MonClass_)
                    {
                    case MonsterClass::ANIMAL:
                        SetKirbyClass(KirbyClass::ANIMAL);
                        break;
                    case MonsterClass::SPARK:
                        SetKirbyClass(KirbyClass::SPARK);
                        break;
                    case MonsterClass::SWORD:
                        SetKirbyClass(KirbyClass::SWORD);
                        break;
                    case MonsterClass::FIRE:
                        SetKirbyClass(KirbyClass::FIRE);
                        break;
                    case MonsterClass::ICE:
                        SetKirbyClass(KirbyClass::ICE);
                        break;
                    }
                    MonClass_ = MonsterClass::NONE;
                    SetState(KirbyState::IDLE);
                }
            }
            else
            {
                SetState(KirbyState::IDLE);
            }
            
        }
    }
    // 떠 있을 때
    else
    {
        if (GetState() != KirbyState::FLYSTAY &&
            GetState() != KirbyState::FLY &&
            GetState() != KirbyState::FLYATTACK &&
            GetState() != KirbyState::FLYEND)
        {
            if (KirbyState::JUMPUP == GetState() &&
                JumpHeight_ < 0)
            {
                SetState(KirbyState::JUMPING);
            }
            if (KirbyState::JUMPING == GetState() &&
                true == Renderer_->IsEndAnimation())
            {
                SetState(KirbyState::JUMPDOWN);
            }
        }
    }

    // 능력 버리기
    if (GetKirbyClass() != KirbyClass::DEFAULT)
    {
        if (true == GameEngineInput::GetInst()->IsUp("Abandon"))
        {            
            SetKirbyClass(KirbyClass::DEFAULT);
        }
    }

    StateUpdate();
    CheckCollision();

}

// 시간 확인
void Player::Render()
{
    //   float Time_ = GameEngineTime::GetDeltaTime();
    //   Time_ += Time_;
    //   std::string Text = std::to_string(Time_);
    //
    //   TextOutA(GameEngine::BackBufferImage()->ImageDC(), 0, 0, Text.c_str(), Text.size());
}


void Player::CorrectPos()
{
}

void Player::CheckCollision()
{
    if (true == KirbyCol_->CollisionCheck("DoorCol1_2", CollisionType::Rect, CollisionType::Rect))
    {
       GameEngine::GetInst().ChangeLevel("Level1_2");
    }

    if (true == KirbyCol_->CollisionCheck("DoorCol1_3", CollisionType::Rect, CollisionType::Rect))
    {
       GameEngine::GetInst().ChangeLevel("Level1_3");
    }

    if (true == KirbyCol_->CollisionCheck("DoorCol1_4", CollisionType::Rect, CollisionType::Rect))
    {
       GameEngine::GetInst().ChangeLevel("Level1_4");
    }

    if (true == KirbyCol_->CollisionCheck("Cannon", CollisionType::Rect, CollisionType::Rect))
    {
       GameEngine::GetInst().ChangeLevel("Cannon");
    }

    if (true == KirbyCol_->CollisionCheck("DorrCol2_2", CollisionType::Rect, CollisionType::Rect))
    {
       GameEngine::GetInst().ChangeLevel("Level2_2");
    }

    if (true == KirbyCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect) && Time_ >= 3 && KirbyState() != KirbyState::EAT)
    {
       Time_ = 0;
       SetHP(GetHP() - 1);
       // need to chk : HPBar --;
       if (GetHP() > 0)
       {
           // need to chk : getattack으로 chng animation 후
           KirbyState::IDLE;
       }
       else
       {
           --HPCount_;
           KirbyState::DIE;
       }
    }

    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y) &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y - 25))
    {
        while (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y) &&
               RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y - 25))
        {
            SetMove(float4::LEFT);
        }
    }

    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y) &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y - 25))
    {
        while (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y) &&
               RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y - 25))
        {
            SetMove(float4::RIGHT);
        }
    }

    if (GetPosition().x < 0)
    {
        SetPosition(float4(0, GetPosition().y));
    }

    if (GetPosition().x > GetLevel()->GetMapSizeX())
    {
        SetPosition(float4(GetLevel()->GetMapSizeX(), GetPosition().y));
    }

    if (GetPosition().y < 70)
    {
        SetPosition(float4(GetPosition().x, 70));
    }
}


void Player::StateUpdate()
{
    switch (KirbyState_)
    {
    case KirbyState::IDLE:
        UpdateIdle();
        break;
    case KirbyState::WALK:
        UpdateWalk();
        break;
    case KirbyState::RUN:
        UpdateRun();
        break;
    case KirbyState::FLY:
        UpdateFly();
        break;
    case KirbyState::ATTACK:
        UpdateAttack();
        break;
    case KirbyState::FLYSTAY:
        UpdateFlyStay();
        break;
    case KirbyState::FLYATTACK:
        UpdateFlyAttack();
        break;
    case KirbyState::FLYEND:
        UpdateFlyEnd();
        break;
    case KirbyState::DIE:
        UpdateDie();
        break;
    case KirbyState::UP:
        UpdateUp();
        break;
    case KirbyState::DOWN:
        UpdateDown();
        break;
    case KirbyState::EATSTART:
        UpdateEatStart();
        break;
    case KirbyState::EAT:
        UpdateEat();
        break;
    case KirbyState::EATEND:
        UpdateEatEnd();
        break;
    case KirbyState::JUMPUP:
        UpdateJumpUp();
        break;
    case KirbyState::JUMPING:
        UpdateJumping();
        break;
    case KirbyState::JUMPDOWN:
        UpdateJumpDown();
        break;
    case KirbyState::SLIDE:
        UpdateSlide();
        break;
    case KirbyState::TRANSFORM:
        UpdateTransform();
        break;
    default:
        break;
    }
}



bool Player::CheckMapCollision()
{
    if (nullptr != ColMapImage_)
    {
        if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y))
        {
           return true;
        }

        if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y))
        {
           return true;
        }

        if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50)
        {
           return true;
        }
    }
    return true;
}


void Player::Start()
{
        // NormalKirby == DefaultKirby
		Dir_ = "Right";
		Level_ = GetLevel();
		SetHPCount(2);
		SetHP(9);
        SetSpeed(200);
		ColMapImage_ = Level_->GetColMapImage();
        KirbyCol_ = CreateCollision("KirbyCol", float4(50.0f, 50.0f), float4(0.0f,-25.0f));
        KirbyEatCol_ = CreateCollision("KirbyEatCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
        KirbyAttackCol_ = CreateCollision("KirbyAttackCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));


		Renderer_ = CreateRenderer("Normal.bmp");
		GameEngineImage* Image_ = Renderer_->GetImage();
        Image_->CutCount(10, 18);

		Renderer_->CreateAnimation("Normal.bmp", "WalkRight", 19, 28, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "WalkLeft", 109, 118, 0.1f, true);

		Renderer_->CreateAnimation("Normal.bmp", "RunRight", 29, 36, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "RunLeft", 119, 126, 0.1f, true);

		Renderer_->CreateAnimation("Normal.bmp", "IdleRight", 0, 0, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "IdleLeft", 90, 90, 0.1f, true);

		Renderer_->CreateAnimation("Normal.bmp", "FlyRight", 53, 58, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyLeft", 143, 148, 0.1f, true); 
		Renderer_->CreateAnimation("Normal.bmp", "FlyStayRight", 59, 64, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyStayLeft", 149, 154, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyAttackRight", 74, 74, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyAttackLeft", 164, 164, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyEndRight", 78, 79, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyEndLeft", 168, 169, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "EatStartRight", 53, 58, 0.1f, false);
        Renderer_->CreateAnimation("Normal.bmp", "EatStartLeft", 143, 148, 0.1f, false);
		Renderer_->CreateAnimation("Normal.bmp", "EatRight", 74, 75, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "EatLeft", 164, 165, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "EatEndRight", 65, 67, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "EatEndLeft", 155, 157, 0.1f, true);

		Renderer_->CreateAnimation("Normal.bmp", "JumpUpRight", 38, 38, 0.5f, true);
		Renderer_->CreateAnimation("Normal.bmp", "JumpUpLeft", 128, 128, 0.5f, true);
		Renderer_->CreateAnimation("Normal.bmp", "JumpingRight", 39, 44, 0.03f, false);
		Renderer_->CreateAnimation("Normal.bmp", "JumpingLeft", 129, 134, 0.03f, false);
        Renderer_->CreateAnimation("Normal.bmp", "JumpDownRight", 45, 46, 0.3f, true);
        Renderer_->CreateAnimation("Normal.bmp", "JumpDownLeft", 135, 136, 0.3f, true);

        Renderer_->CreateAnimation("Normal.bmp", "DownRight", 1, 1, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "DownLeft", 91, 91, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "SlideRight", 47, 47, 0.1f, false); // 루프안돌리고 이미지 이으면?
        Renderer_->CreateAnimation("Normal.bmp", "SlideLeft", 137, 137, 0.1f, false);
        Renderer_->CreateAnimation("Normal.bmp", "TakeDamageRight", 82, 82, 0.1f, true); 
        Renderer_->CreateAnimation("Normal.bmp", "TakeDamageLeft", 172, 172, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "DieRight", 81, 88, 0.1f, true); 
        Renderer_->CreateAnimation("Normal.bmp", "DieLeft", 171, 178, 0.1f, true);

        {
            //pig
            PigRenderer_ = CreateRenderer("Normal.bmp");
            PigImage_ = PigRenderer_->GetImage();
            PigImage_->CutCount(10, 18);

            PigRenderer_->CreateAnimation("Normal.bmp", "IdleRight", 68, 68, 0.1f, true);
            PigRenderer_->CreateAnimation("Normal.bmp", "IdleLeft", 158, 158, 0.1f, true);

            PigRenderer_->CreateAnimation("Normal.bmp", "WalkRight", 2, 17, 0.1f, true);
            PigRenderer_->CreateAnimation("Normal.bmp", "WalkLeft", 92, 107, 0.1f, true);

			PigRenderer_->CreateAnimation("Normal.bmp", "TransformRight", 69, 73, 0.3f, false);
            PigRenderer_->CreateAnimation("Normal.bmp", "TransformLeft", 159, 163, 0.1f, false);

            PigRenderer_->CreateAnimation("Normal.bmp", "AttackRight", 74, 74, 0.1f, true);
            PigRenderer_->CreateAnimation("Normal.bmp", "AttackLeft", 164, 167, 0.1f, true);

        }
    {
        // fire 
        // Need to chk 이미지 수정으로 인해 애니메이션 안맞음 
            FireRenderer_ = CreateRenderer("FireKirby.bmp");
            GameEngineImage* FireKirbyImage = FireRenderer_->GetImage();
            FireKirbyImage->CutCount(10, 25);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "WalkRight", 2, 11, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "WalkLeft", 148, 159, 0.1f, true);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "RunRight", 12, 19, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "RunLeft", 160, 167, 0.1f, true);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "IdleRight", 0, 0, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "IdleLeft", 133, 133, 0.1f, true);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "FlyRight", 35, 39, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "FlyLeft", 168, 172, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "FlyStayRight", 40, 45, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "FlyStayLeft", 173, 178, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "FlyAttackRight", 52, 54, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "FlyAttackLeft", 179, 181, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "FlyEndRight", 19, 20, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "FlyEndLeft", 191, 192, 0.1f, true);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "AttackRight", 51, 54, 0.3f, true); // need to chk : 이름 통일
            FireRenderer_->CreateAnimation("FireKirby.bmp", "AttackLeft", 184, 187, 0.1f, true);
            /*
                    FireRenderer_->CreateAnimation("FireKirby.bmp", "StarAttackRight", 87, 102, 0.3f, true);
                    FireRenderer_->CreateAnimation("FireKirby.bmp", "StarAttackLeft", 220, 235, 0.1f, true);
            */

            FireRenderer_->CreateAnimation("FireKirby.bmp", "JumpUpRight", 22, 22, 0.5f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "JumpUpLeft", 135, 135, 0.5f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "JumpingRight", 23, 28, 0.1f, false);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "JumpingLeft", 136, 145, 0.f, false);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "JumpDownRight", 29, 30, 0.5f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "JumpDownLeft", 146, 147, 0.5f, true);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "DownRight", 1, 1, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "DownLeft", 134, 134, 0.1f, true);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "SlideRight", 20, 21, 0.1f, false); // 루프안돌리고 이미지 이으면?
            FireRenderer_->CreateAnimation("FireKirby.bmp", "SlideLeft", 182, 182, 0.1f, false);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "GetDamageRight", 211, 211, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "GetDamageLeft", 78, 78, 0.1f, true);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "DieRight", 197, 212, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "DieLeft", 64, 79, 0.1f, true);

            FireRenderer_->CreateAnimation("FireKirby.bmp", "DoorOpenRight", 31, 34, 0.1f, true);
            FireRenderer_->CreateAnimation("FireKirby.bmp", "DoorOpen", 164, 167, 0.1f, true);

    }

    {
         //Animal
         //Need to chk 이미지 수정으로 인해 애니메이션 안맞음 
        AnimalRenderer_ = CreateRenderer("AnimalKirby.bmp");
        GameEngineImage* AnimalKirbyImage = AnimalRenderer_->GetImage();
        AnimalKirbyImage->CutCount(10, 25);

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "WalkRight", 2, 11, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "WalkLeft", 148, 159, 0.1f, true);

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "RunRight", 12, 19, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "RunLeft", 160, 167, 0.1f, true);

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "IdleRight", 0, 0, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "IdleLeft", 133, 133, 0.1f, true);

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "FlyRight", 35, 39, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "FlyLeft", 168, 172, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "FlyStayRight", 40, 45, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "FlyStayLeft", 173, 178, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "FlyAttackRight", 52, 54, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "FlyAttackLeft", 179, 181, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "FlyEndRight", 19, 20, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "FlyEndLeft", 191, 192, 0.1f, true);

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "AttackRight", 51, 54, 0.3f, true); // need to chk : 이름 통일
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "AttackLeft", 184, 187, 0.1f, true);
        /*
                AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "StarAttackRight", 87, 102, 0.3f, true);
                AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "StarAttackLeft", 220, 235, 0.1f, true);
        */

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "JumpUpRight", 22, 22, 0.5f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "JumpUpLeft", 135, 135, 0.5f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "JumpingRight", 23, 28, 0.1f, false);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "JumpingLeft", 136, 145, 0.f, false);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "JumpDownRight", 29, 30, 0.5f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "JumpDownLeft", 146, 147, 0.5f, true);

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "DownRight", 1, 1, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "DownLeft", 134, 134, 0.1f, true);

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "SlideRight", 20, 21, 0.1f, false); // 루프안돌리고 이미지 이으면?
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "SlideLeft", 182, 182, 0.1f, false);

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "GetDamageRight", 211, 211, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "GetDamageLeft", 78, 78, 0.1f, true);

        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "DieRight", 197, 212, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "DieLeft", 64, 79, 0.1f, true);
       
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "DoorOpenRight", 31, 34, 0.1f, true);
        AnimalRenderer_->CreateAnimation("AnimalKirby.bmp", "DoorOpen", 164, 167, 0.1f, true);

    }

        SwordRenderer_ = CreateRenderer("SwordKirby.bmp");
        SwordKirbyImage_ = SwordRenderer_->GetImage();
        SwordKirbyImage_->CutCount(10, 27);

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "WalkRight", 15, 26, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "WalkLeft", 148, 159, 0.1f, true);

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "RunRight", 27, 34, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "RunLeft", 160, 167, 0.1f, true);

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "IdleRight", 0, 0, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "IdleLeft", 133, 133, 0.1f, true);

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "FlyRight", 35, 39, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "FlyLeft", 168, 172, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "FlyStayRight", 40, 45, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "FlyStayLeft", 173, 178, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "FlyAttackRight", 46, 48, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "FlyAttackLeft", 179, 181, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "FlyEndRight", 58, 59, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "FlyEndLeft", 191, 192, 0.1f, true);

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "AttackRight", 51, 54, 0.3f, true); // need to chk : 이름 통일
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "AttackLeft", 184, 187, 0.1f, true);
        /*
                SwordRenderer_->CreateAnimation("SwordKirby.bmp", "StarAttackRight", 87, 102, 0.3f, true); 
                SwordRenderer_->CreateAnimation("SwordKirby.bmp", "StarAttackLeft", 220, 235, 0.1f, true);
        */

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "JumpUpRight", 2, 2, 0.5f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "JumpUpLeft", 135, 135, 0.5f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "JumpingRight", 3, 12, 0.1f, false);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "JumpingLeft", 136, 145, 0.f, false);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "JumpDownRight", 13, 14, 0.5f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "JumpDownLeft", 146, 147, 0.5f, true);

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "DownRight", 1, 1, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "DownLeft", 134, 134, 0.1f, true);

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "SlideRight", 49,49, 0.1f, false); // 루프안돌리고 이미지 이으면?
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "SlideLeft", 182, 182, 0.1f, false);

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "GetDamageRight", 211, 211, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "GetDamageLeft", 78, 78, 0.1f, true);

        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "DieRight", 197, 212, 0.1f, true);
        SwordRenderer_->CreateAnimation("SwordKirby.bmp", "DieLeft", 64, 79, 0.1f, true);

        // IceKirby
        IceRenderer_ = CreateRenderer("IceKirby.bmp");
        IceKirbyImage_ = IceRenderer_->GetImage();
        IceKirbyImage_->CutCount(10, 18);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "WalkRight", 13, 22, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "WalkLeft", 102, 111, 0.1f, true);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "RunRight", 23, 30, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "RunLeft", 112, 119, 0.1f, true);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "IdleRight", 0, 0, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "IdleLeft", 89, 89, 0.1f, true);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "FlyRight", 32, 36, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "FlyLeft", 121, 125, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "FlyStayRight", 37, 42, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "FlyStayLeft", 126, 131, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "FlyAttackRight", 43, 44, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "FlyAttackLeft", 132, 133, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "FlyEndRight", 45, 46, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "FlyEndLeft", 134, 135, 0.1f, true);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "AttackRight", 79, 84, 0.3f, true); // need to chk : 이름 통일
        IceRenderer_->CreateAnimation("IceKirby.bmp", "AttackLeft", 168, 173, 0.1f, true);
        
        IceRenderer_->CreateAnimation("IceKirby.bmp", "AttackStayRight", 85, 86, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "AttackStayLeft", 174, 175, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "AttackEndRight", 87, 88, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "AttackEndLeft", 176, 177, 0.1f, true);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "JumpUpRight", 4, 4, 0.5f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "JumpUpLeft", 93, 93, 0.5f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "JumpingRight", 5, 10, 0.1f, false);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "JumpingLeft", 94, 99, 0.f, false);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "JumpDownRight", 11, 12, 0.5f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "JumpDownLeft", 100, 101, 0.5f, true);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "DownRight", 1, 1, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "DownLeft", 90, 90, 0.1f, true);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "SlideRight", 2, 2, 0.1f, false); // 루프안돌리고 이미지 이으면?
        IceRenderer_->CreateAnimation("IceKirby.bmp", "SlideLeft", 91, 91, 0.1f, false);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "GetDamageRight", 60, 60, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "GetDamageLeft", 73, 73, 0.1f, true);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "DieRight", 59, 74, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "DieLeft", 148, 163, 0.1f, true);

        IceRenderer_->CreateAnimation("IceKirby.bmp", "DoorOpenRight", 75, 78, 0.1f, true);
        IceRenderer_->CreateAnimation("IceKirby.bmp", "DoorOpenLeft", 164, 167, 0.1f, true);


    {
     //Spark
     //Need to chk 이미지 수정으로 인해 애니메이션 안맞음
        SparkKirbyRenderer_ = CreateRenderer("SparkKirby.bmp");
        GameEngineImage* SparkImage = SparkKirbyRenderer_->GetImage();
        SparkImage->CutCount(10, 18);

        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "WalkRight", 19, 28, 0.1f, true); // 이미지 순서 확인 필요
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "WalkLeft", 107, 126, 0.1f, true);
                                    
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "RunRight", 38, 45, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "RunLeft", 141, 147, 0.1f, true);
                                   
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "IdleRight", 3, 3, 0.1f, true); // 머리 바뀌는 이미지로 변경 필요
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "IdleLeft", 116, 116, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "FlyRight", 64, 69, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "FlyLeft", 156, 161, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "FlyStayRight", 70, 75, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "FlyStayLeft", 162, 167, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "HoverEndRight", 85, 88, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "HoverEndLeft", 177, 180, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "HoverEnd2Right", 89, 90, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "HoverEnd2Left", 181, 182, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "EatRight", 76, 78, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "EatLeft", 168, 178, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "IdleWzMonsterRight", 79, 79, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "IdleWzMonsterLeft", 171, 171, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "WalkWzMonsterRight", 2, 17, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "WalkWzMonsterLeft", 94, 109, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "FlyAttackRight", 18, 18, 0.3f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "FlyAttackLeft", 110, 110, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "AttackRight", 18, 18, 0.3f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "AttackLeft", 110, 110, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "DownRight", 4, 4, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "DownLeft", 117, 117, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "JumpUpRight", 38, 38, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "JumpUpLeft", 38, 38, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "JumpingRight", 39, 44, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "JumpingLeft", 39, 44, 0.1f, true);
                           
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "SlideRight", 5, 9, 0.5f, true); 
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "SlideLeft", 118, 122, 0.5f, true);
    }



    SetState(KirbyState::IDLE);
    SetKirbyClass(KirbyClass::DEFAULT);
    if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
    {
        GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
        GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);
        GameEngineInput::GetInst()->CreateKey("Up", VK_UP);
        GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
        GameEngineInput::GetInst()->CreateKey("Jump", VK_LCONTROL);
        GameEngineInput::GetInst()->CreateKey("Fly", VK_LSHIFT); 
        GameEngineInput::GetInst()->CreateKey("Copy", 'A');
        GameEngineInput::GetInst()->CreateKey("Abandon", 'S');
        GameEngineInput::GetInst()->CreateKey("Slide", 'D');
        GameEngineInput::GetInst()->CreateKey("Run", 'Z');
        GameEngineInput::GetInst()->CreateKey("Eat", 'X');
        GameEngineInput::GetInst()->CreateKey("Attack", 'C');
        GameEngineInput::GetInst()->CreateKey("Transform", 'V');

        
        
        GameEngineInput::GetInst()->CreateKey("ResetPos", 'P');
        /*GameEngineInput::GetInst()->CreateKey("Spark", '1');
        GameEngineInput::GetInst()->CreateKey("Fire", '2');
        GameEngineInput::GetInst()->CreateKey("Sword", '3');
        GameEngineInput::GetInst()->CreateKey("Animal", '4');
        GameEngineInput::GetInst()->CreateKey("Ice", '5');
        GameEngineInput::GetInst()->CreateKey("Default", 'Y');
        GameEngineInput::GetInst()->CreateKey("AbandonClass", 'O');*/
     }
}