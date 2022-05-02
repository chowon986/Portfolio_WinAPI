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
#include "TransformEffect.h"
#include "GroundStarEffect.h"
#include "Monster.h"
#include "RunEffect.h"

int Player::HP_COUNT = 2;
int Player::HP = 10;
KirbyClass Player::KIRBYCLASS = KirbyClass::DEFAULT;
Player::Player()
    : Renderer_(nullptr)
    , Gravity_(5.0f)
    , JumpHeight_(0.0f)
    , Time_(3.0f)
    , Level_(nullptr)
    , HPCount_(0)
    , KirbyEatCol_(nullptr)
    , MonClass_(MonsterClass::NONE)
    , AnimalRenderer_(nullptr)
    , AttackEffectRenderer_(nullptr)
    , ColMapImage_(nullptr)
    , FireRenderer_(nullptr)
    , IceKirbyImage_(nullptr)
    , SwordRenderer_(nullptr)
    , SwordKirbyImage_(nullptr)
    , StarAttackEffect_(nullptr)
    , BeamRenderer_(nullptr)
    , IsGround_(false)
    , SwordCol_(nullptr)
    , SwordAttackEffect_(nullptr)
    , Speed_(20.0f)
    , RunEffect_(nullptr)
    , PigRenderer_(nullptr)
    , PigImage_(nullptr)
    , Monster_(nullptr)
    , KirbyState_(KirbyState::IDLE)
    , KirbySlideCol_(nullptr)
    , KirbyCol_(nullptr)
    , Image_(nullptr)
    , IceRenderer_(nullptr)
    , IceAttackEffect_(nullptr)
    , FireAttackEffect_(nullptr)
    , DieEffect_(nullptr)
    , BeamAttackEffect_(nullptr)
    , AttackEffect_(nullptr)
    , SparkAttackEffect_(nullptr)
    , SparkRenderer_(nullptr)
    , TransformEffect_(nullptr)
    , KirbyClass_(KirbyClass::DEFAULT)
    , GroundStarEffect_(nullptr)
    , AnimalCol_(nullptr)
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

GameEngineRenderer* Player::GetRenderer()
{
    if (GetKirbyClass() == KirbyClass::ANIMAL)
    {
        return AnimalRenderer_;
    }
    else if (GetKirbyClass() == KirbyClass::BEAM)
    {
        return BeamRenderer_;
    }
    else if (GetKirbyClass() == KirbyClass::DEFAULT)
    {
        return Renderer_;
    }
    else if (GetKirbyClass() == KirbyClass::FIRE)
    {
        return FireRenderer_;
    }
    else if (GetKirbyClass() == KirbyClass::ICE)
    {
        return IceRenderer_;
    }
    else if (GetKirbyClass() == KirbyClass::PIG)
    {
        return PigRenderer_;
    }
    else if (GetKirbyClass() == KirbyClass::SPARK)
    {
        return SparkRenderer_;
    }
    else if (GetKirbyClass() == KirbyClass::SWORD)
    {
        return SwordRenderer_;
    }
}

void Player::ClassUpdate()
{
    switch (KirbyClass_)
    {
    case KirbyClass::SPARK:
        Renderer_->SetAlpha(0);
        SparkRenderer_->SetAlpha(255);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        BeamRenderer_->SetAlpha(0);
        break;
    case KirbyClass::ANIMAL:
        Renderer_->SetAlpha(0);
        SparkRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(255);
        BeamRenderer_->SetAlpha(0);
        break;
    case KirbyClass::DEFAULT:
        Renderer_->SetAlpha(255);
        SparkRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        BeamRenderer_->SetAlpha(0);
        break;
    case KirbyClass::ICE:
        Renderer_->SetAlpha(0);
        SparkRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(255);
        AnimalRenderer_->SetAlpha(0);
        BeamRenderer_->SetAlpha(0);
        break;
    case KirbyClass::SWORD:
        Renderer_->SetAlpha(0);
        SparkRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(255);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        BeamRenderer_->SetAlpha(0);
        break;
    case KirbyClass::FIRE:
        Renderer_->SetAlpha(0);
        SparkRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(255);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        BeamRenderer_->SetAlpha(0);
        break;
    case KirbyClass::PIG:
        Renderer_->SetAlpha(0);
        SparkRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(255);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        BeamRenderer_->SetAlpha(0);
        break;
    case KirbyClass::BEAM:
        Renderer_->SetAlpha(0);
        SparkRenderer_->SetAlpha(0);
        PigRenderer_->SetAlpha(0);
        SwordRenderer_->SetAlpha(0);
        FireRenderer_->SetAlpha(0);
        IceRenderer_->SetAlpha(0);
        AnimalRenderer_->SetAlpha(0);
        BeamRenderer_->SetAlpha(255);
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
            SparkRenderer_->ChangeAnimation("Idle" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("Idle" + Dir_);
        }
        break;

    case KirbyState::UP: // Animal 사용
        break;

    case KirbyState::DOWN:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkRenderer_->ChangeAnimation("Down" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("Down" + Dir_);
        }
        break;

    case KirbyState::WALK:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkRenderer_->ChangeAnimation("Walk" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("Walk" + Dir_);
        }
        break;

    case KirbyState::RUN:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
		    SparkRenderer_->ChangeAnimation("Run" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("Run" + Dir_);
        }
        break;


    case KirbyState::FLY:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkRenderer_->ChangeAnimation("Fly" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("Fly" + Dir_);
        }
        break;

    case KirbyState::FLYSTAY:
        

    case KirbyState::FLYATTACK:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkRenderer_->ChangeAnimation("FlyAttack" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("FlyAttack" + Dir_);
        }
        break;

    case KirbyState::FLYEND:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkRenderer_->ChangeAnimation("FlyEnd" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("FlyEnd" + Dir_);
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
            SparkRenderer_->ChangeAnimation("Attack" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("Attack" + Dir_);
        }
        break;

    case KirbyState::ATTACKSTAY:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkRenderer_->ChangeAnimation("AttackStay" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::PIG)
        {
            PigRenderer_->ChangeAnimation("AttackStay" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("AttackStay" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("AttackStay" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("AttackStay" + Dir_);
        }
        break;

    case KirbyState::TRANSFORM:
        PigRenderer_->ChangeAnimation("Transform" + Dir_);
        if (TransformEffect_ != nullptr)
        {
            TransformEffect_->SetPosition(GetPosition());
            TransformEffect_->SetState(TransformEffectState::TransformEffect);
        }
		break;


    case KirbyState::TAKEDAMAGE:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkRenderer_->ChangeAnimation("TakeDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("TakeDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            IceRenderer_->ChangeAnimation("TakeDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            SwordRenderer_->ChangeAnimation("TakeDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            AnimalRenderer_->ChangeAnimation("TakeDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            FireRenderer_->ChangeAnimation("TakeDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("TakeDamage" + Dir_);
        }
        break;

    case KirbyState::JUMPUP:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkRenderer_->ChangeAnimation("JumpUp" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("JumpUp" + Dir_);
        }
        break;

    case KirbyState::JUMPING:
        if (GetKirbyClass() == KirbyClass::SPARK && GetState() != KirbyState::IDLE)
        {
            SparkRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT && GetState() != KirbyState::IDLE)
        {
            Renderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE && GetState() != KirbyState::IDLE)
        {
            IceRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD && GetState() != KirbyState::IDLE)
        {
            SwordRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL && GetState() != KirbyState::IDLE)
        {
            AnimalRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE && GetState() != KirbyState::IDLE)
        {
            FireRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::BEAM && GetState() != KirbyState::IDLE)
        {
            BeamRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        break;

    case KirbyState::JUMPDOWN:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkRenderer_->ChangeAnimation("JumpDown" + Dir_);
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
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("JumpDown" + Dir_);
        }
        break;



    case KirbyState::SLIDE:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            StartPos_ = GetPosition();
            SparkRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            StartPos_ = GetPosition();
            Renderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ICE)
        {
            StartPos_ = GetPosition();

            IceRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::SWORD)
        {
            StartPos_ = GetPosition();

            SwordRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::ANIMAL)
        {
            StartPos_ = GetPosition();
            AnimalRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::FIRE)
        {
            StartPos_ = GetPosition();
            FireRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::BEAM)
        {
            BeamRenderer_->ChangeAnimation("Slide" + Dir_);
        }
        break;

    case KirbyState::DIE:
		SparkRenderer_->SetAlpha(0);
		Renderer_->SetAlpha(255);
		IceRenderer_->SetAlpha(0);
		SwordRenderer_->SetAlpha(0);
		AnimalRenderer_->SetAlpha(0);
		FireRenderer_->SetAlpha(0);
		BeamRenderer_->SetAlpha(0);
		Renderer_->ChangeAnimation("Die");
        JumpHeight_ = 200;
        StartPos_ = GetPosition();
		break;

    //case KirbyState::OPENDOOR:
    //    if (GetKirbyClass() == KirbyClass::SPARK)
    //    {
    //        SparkRenderer_->ChangeAnimation("DoorOpen" + Dir_);
    //    }
    //    if (GetKirbyClass() == KirbyClass::DEFAULT)
    //    {
    //        Renderer_->ChangeAnimation("DoorOpen" + Dir_);
    //    }
    //    if (GetKirbyClass() == KirbyClass::ICE)
    //    {
    //        IceRenderer_->ChangeAnimation("DoorOpen" + Dir_);
    //    }
    //    if (GetKirbyClass() == KirbyClass::SWORD)
    //    {
    //        SwordRenderer_->ChangeAnimation("DoorOpen" + Dir_);
    //    }
    //    if (GetKirbyClass() == KirbyClass::ANIMAL)
    //    {
    //        AnimalRenderer_->ChangeAnimation("DoorOpen" + Dir_);
    //    }
    //    if (GetKirbyClass() == KirbyClass::FIRE)
    //    {
    //        FireRenderer_->ChangeAnimation("DoorOpen" + Dir_);
    //    }
    //    break;
    default:
        break;
    }
}


void Player::Update()
{
    float AddTime = GameEngineTime::GetDeltaTime();
    Time_ += AddTime;

    if (true == GameEngineInput::GetInst()->IsPress("Right"))
    {
        Dir_ = "Right";
    }

    if (true == GameEngineInput::GetInst()->IsPress("Left"))
    {
        Dir_ ="Left";
    }
    if (true == GameEngineInput::GetInst()->IsPress("Ice"))
    {
        SetKirbyClass(KirbyClass::ICE);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Spark"))
    {
        SetKirbyClass(KirbyClass::SPARK);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Fire"))
    {
        SetKirbyClass(KirbyClass::FIRE);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Beam"))
    {
        SetKirbyClass(KirbyClass::BEAM);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Sword"))
    {
        SetKirbyClass(KirbyClass::SWORD);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Animal"))
    {
        SetKirbyClass(KirbyClass::ANIMAL);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Animal"))
    {
        SetKirbyClass(KirbyClass::ANIMAL);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Abandon"))
    {
        SetKirbyClass(KirbyClass::DEFAULT);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Left") &&
        false == GameEngineInput::GetInst()->IsPress("Run") &&
        false == GameEngineInput::GetInst()->IsPress("Attack") &&
        false == GameEngineInput::GetInst()->IsPress("Fly") &&
        false == GameEngineInput::GetInst()->IsPress("Jump") &&
        false == GameEngineInput::GetInst()->IsPress("Eat") &&
        false == GameEngineInput::GetInst()->IsPress("Abandon") &&
        KirbyState::EATEN != GetState() &&
        KirbyState::DIE != GetState() &&
        KirbyState::FLY != GetState() &&
        KirbyState::SLIDE != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        true == IsGround_ &&
        ColMapImage_ != nullptr)

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
        KirbyState::DIE != GetState() &&
        KirbyState::EATEN != GetState() &&
        KirbyState::FLY != GetState() &&
        KirbyState::SLIDE != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        true == IsGround_ &&
        ColMapImage_ != nullptr)

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
        KirbyState::EATEN != GetState() &&
        KirbyState::DIE != GetState() &&
        KirbyState::FLY != GetState() &&
        KirbyState::SLIDE != GetState() && 
        KirbyState::TRANSFORM != GetState() &&
        true == IsGround_ &&
        ColMapImage_ != nullptr)
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
        KirbyState::EATEN != GetState() &&
        KirbyState::DIE != GetState() &&
        KirbyState::FLY != GetState() &&
        KirbyState::SLIDE != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        true == IsGround_ &&
        ColMapImage_ != nullptr)
    {
        SetState(KirbyState::RUN);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Up") &&
        KirbyState::EATEN != GetState() &&
        KirbyClass::ANIMAL == GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState() &&
        KirbyState::SLIDE != GetState() &&
        KirbyState::DIE != GetState()
        /*need to chk RGB(,,)  */)
    {
        SetState(KirbyState::UP);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Down") &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState() &&
        KirbyState::SLIDE != GetState() &&
        KirbyState::EATEN != GetState() &&
        KirbyState::DIE != GetState())
    {
        SetState(KirbyState::DOWN);
    }

    if (true == GameEngineInput::GetInst()->IsDown("Slide") &&
        KirbyState::DOWN == GetState() &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState() &&
        KirbyState::EATEN != GetState() &&
        KirbyState::DIE != GetState())
    {
        SetState(KirbyState::SLIDE);
    }

    //if (true == GameEngineInput::GetInst()->IsDown("OpenDoor")
    //    /*true == Renderer_->IsEndAnimation()*/)
    //{
    //    SetState(KirbyState::OPENDOOR);
    //}

    if (true == GameEngineInput::GetInst()->IsPress("Attack") &&
        KirbyClass::DEFAULT != GetKirbyClass() &&
        KirbyState::EATEN != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        KirbyState::DIE != GetState())
    {
        if (KirbyState::ATTACKSTAY != GetState())
        {
        SetState(KirbyState::ATTACK);
        }

        if (KirbyState::ATTACK == GetState())
        {
            if (GetKirbyClass() == KirbyClass::DEFAULT && true == Renderer_->IsEndAnimation())
            {
                SetState(KirbyState::ATTACKSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::ICE && true == IceRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::ATTACKSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::FIRE && true == FireRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::ATTACKSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::SPARK && true == SparkRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::ATTACKSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::BEAM && true == BeamRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::ATTACKSTAY);
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////
        }
    }

    if (true == GameEngineInput::GetInst()->IsPress("Fly") &&
        GetState() != KirbyState::JUMPUP &&
        GetState() != KirbyState::JUMPING &&
        GetState() != KirbyState::JUMPDOWN &&
        KirbyState::EATEN != GetState() &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::TRANSFORM != GetState() &&
        GetState() != KirbyState::DIE)
    {
        if (KirbyState::FLYSTAY != GetState())
        {
            SetState(KirbyState::FLY);
        }

        if (KirbyState::FLY == GetState())
        {
            if (GetKirbyClass() == KirbyClass::DEFAULT && true == Renderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::ICE && true == IceRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::ANIMAL && true == AnimalRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::SWORD && true == SwordRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::FIRE && true == FireRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::SPARK && true == SparkRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYSTAY);
            }

            else if (GetKirbyClass() == KirbyClass::BEAM && true == BeamRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYSTAY);
            }
        }

    }
    else if (true == GameEngineInput::GetInst()->IsFree("Fly") &&
        (KirbyState::FLYSTAY == GetState() || KirbyState::FLYATTACK == GetState() || KirbyState::FLYEND == GetState()) &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::EATEN != GetState() &&
        KirbyState::DIE != GetState() &&
        KirbyState::TRANSFORM != GetState())
    {

        if (KirbyState::FLYEND != GetState())
        {
            SetState(KirbyState::FLYATTACK);
        }

        if (KirbyState::FLYATTACK == GetState())
        {
            if (GetKirbyClass() == KirbyClass::DEFAULT && true == Renderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYEND);
            }

            else if (GetKirbyClass() == KirbyClass::ICE && true == IceRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYEND);
            }

            else if (GetKirbyClass() == KirbyClass::ANIMAL && true == AnimalRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYEND);
            }

            else if (GetKirbyClass() == KirbyClass::SWORD && true == SwordRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYEND);
            }            
            
            else if (GetKirbyClass() == KirbyClass::FIRE && true == FireRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYEND);
            }

            else if (GetKirbyClass() == KirbyClass::SPARK && true == SparkRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYEND);
            }

            else if (GetKirbyClass() == KirbyClass::BEAM && true == BeamRenderer_->IsEndAnimation())
            {
                SetState(KirbyState::FLYEND);
            }
        }
    }

    if (true == GameEngineInput::GetInst()->IsUp("Jump") &&
        KirbyClass::PIG != GetKirbyClass() &&
        KirbyState::EATEN != GetState() &&
        KirbyState::DIE != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        true == IsGround_ &&
        ColMapImage_ != nullptr) // 공중에서 점프 불가
    {
        JumpHeight_ = 200;
        SetState(KirbyState::JUMPUP);
    }
   
    if (true == GameEngineInput::GetInst()->IsUp("Transform") &&
        KirbyState::DIE != GetState() &&
        KirbyState::EATEN != GetState() &&
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
        KirbyState::DIE != GetState() &&
        KirbyState::ATTACK != GetState() &&
        KirbyState::EATEN != GetState() &&
        KirbyState::DOWN != GetState() &&
        KirbyState::FLY != GetState() &&
        KirbyState::FLYSTAY != GetState() &&
        KirbyState::FLYATTACK != GetState() &&
        KirbyState::EATEND != GetState() &&
        KirbyState::TRANSFORM != GetState() &&
        KirbyClass::DEFAULT == GetKirbyClass())
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
            true == KirbyCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect))
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
    
    bool OnTheObstruction = false;
    // 장애물에 부딪혔을 때
    std::vector<GameEngineCollision*> BoxResult;
    if(true == KirbyCol_->CollisionResult("Obstruction", BoxResult, CollisionType::Rect, CollisionType::Rect))
    {
        for (GameEngineCollision* Collision : BoxResult)
        {
            if (nullptr != Collision->GetActor())
            {
                float Offset = Collision->GetActor()->GetPosition().y - GetPosition().y;

                if (Offset > 0)
                {
                    OnTheObstruction = true;
                    //GroundStarEffect_->SetState(GroundStarEffectState::GroundStarEffect);
                }
            }
        }
	}

    // 땅에 닿았을 때
    if (ColMapImage_ != nullptr && 
        (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition() + float4::DOWN) || OnTheObstruction == true ) &&
        JumpDirection.y > 0 && 
        GetState() != KirbyState::DIE)
    {
        IsGround_ = true;
        while (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition()) && ColMapImage_ != nullptr)
        {
            SetMove(float4::UP);
        }
        // need to chk**
         SetPosition(float4(GetPosition().x, GetPosition().iy()));

        JumpHeight_ = 0;
        float4 Distance = GetPosition() - StartPos_;
        float DistanceX = Distance.x < 0 ? Distance.x * -1 : Distance.x;
        if (GetState() != KirbyState::DIE &&
            GetState() != KirbyState::EATEN  &&
            true == GameEngineInput::GetInst()->IsFree("Left") &&
            true == GameEngineInput::GetInst()->IsFree("Right") &&
            true == GameEngineInput::GetInst()->IsFree("Down") &&
            true == GameEngineInput::GetInst()->IsFree("Slide")&&
            true == GameEngineInput::GetInst()->IsFree("Jump") &&
            true == GameEngineInput::GetInst()->IsFree("Fly") &&
            true == GameEngineInput::GetInst()->IsFree("Attack") &&
            (KirbyState::TAKEDAMAGE != GetState() || KirbyState::TAKEDAMAGE == GetState() && true == Renderer_->IsEndAnimation()) &&
            (true == GameEngineInput::GetInst()->IsFree("Eat") || (KirbyState::EATEND == GetState() && true == Renderer_->IsEndAnimation())))
            /////////////////////////need to chk : isendanimation
        {
            if (GetKirbyClass() != KirbyClass::ANIMAL &&
                GetKirbyClass() != KirbyClass::FIRE &&
                GetKirbyClass() != KirbyClass::ICE &&
                GetKirbyClass() != KirbyClass::SPARK &&
                GetKirbyClass() != KirbyClass::SWORD &&
                GetKirbyClass() != KirbyClass::BEAM)
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
                    case MonsterClass::BEAM:
                        SetKirbyClass(KirbyClass::BEAM);
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
        IsGround_ = false;
        if (GetState() != KirbyState::FLYSTAY &&
            GetState() != KirbyState::DIE &&
            GetState() != KirbyState::FLY &&
            GetState() != KirbyState::FLYATTACK &&
            GetState() != KirbyState::FLYEND)
        {
            if (KirbyState::JUMPUP == GetState() &&
                JumpHeight_ < 0)
            {
                SetState(KirbyState::JUMPING);
            }
            if (KirbyState::JUMPING == GetState())
            {
                if (GetKirbyClass() == KirbyClass::DEFAULT && true == Renderer_->IsEndAnimation())
                {
                    SetState(KirbyState::JUMPDOWN);
                }

                else if (GetKirbyClass() == KirbyClass::ICE && true == IceRenderer_->IsEndAnimation())
                {
                    SetState(KirbyState::JUMPDOWN);
                }

                else if (GetKirbyClass() == KirbyClass::ANIMAL && true == AnimalRenderer_->IsEndAnimation())
                {
                    SetState(KirbyState::JUMPDOWN);
                }

                else if (GetKirbyClass() == KirbyClass::SWORD && true == SwordRenderer_->IsEndAnimation())
                {
                    SetState(KirbyState::JUMPDOWN);
                }

                else if (GetKirbyClass() == KirbyClass::FIRE && true == FireRenderer_->IsEndAnimation())
                {
                    SetState(KirbyState::JUMPDOWN);
                }

                else if (GetKirbyClass() == KirbyClass::SPARK && true == SparkRenderer_->IsEndAnimation())
                {
                    SetState(KirbyState::JUMPDOWN);
                }

                else if (GetKirbyClass() == KirbyClass::BEAM && true == BeamRenderer_->IsEndAnimation())
                {
                    SetState(KirbyState::JUMPDOWN);
                }
            }
        }
    }

    // 능력 버리기
    if (GetKirbyClass() != KirbyClass::DEFAULT)
    {
        if (true == GameEngineInput::GetInst()->IsUp("Abandon") || GetState() == KirbyState::DIE)
        {            
            SetKirbyClass(KirbyClass::DEFAULT);
        }
    }

    std::vector<GameEngineCollision*> Result;
    if (KirbyState::EAT != GetState() &&
        KirbyState::EATSTART != GetState() &&
        KirbyState::EATEND != GetState() &&
        KirbyState::DIE != GetState() &&
        KirbyCol_->CollisionResult("BasicMonster", Result, CollisionType::Rect, CollisionType::Rect) &&
        Time_ >= 2)
    {
		SetHP(GetHP() - 1);
		Time_ = 0;
    }

    StateUpdate();
    CheckCollision();

}

// 시간 확인
void Player::Render()
{

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
        HP_COUNT = GetHPCount();
        HP = GetHP();
        KIRBYCLASS = GetKirbyClass();
        GameEngine::GetInst().ChangeLevel("Level1_2");
    }

    if (true == KirbyCol_->CollisionCheck("DoorCol1_3", CollisionType::Rect, CollisionType::Rect))
    {
       HP_COUNT = GetHPCount();
       HP = GetHP();
       KIRBYCLASS = GetKirbyClass();
       GameEngine::GetInst().ChangeLevel("Level1_3");
    }

    if (true == KirbyCol_->CollisionCheck("DoorCol1_4", CollisionType::Rect, CollisionType::Rect))
    {
       HP_COUNT = GetHPCount();
       HP = GetHP();
       KIRBYCLASS = GetKirbyClass();
       GameEngine::GetInst().ChangeLevel("Level1_4");
    }

    if (true == KirbyCol_->CollisionCheck("Cannon", CollisionType::Rect, CollisionType::Rect))
    {
       HP_COUNT = GetHPCount();
       HP = GetHP();
       KIRBYCLASS = GetKirbyClass();
       GameEngine::GetInst().ChangeLevel("Cannon");
    }

    if (true == KirbyCol_->CollisionCheck("DoorCol2_2", CollisionType::Rect, CollisionType::Rect))
    {
       HP_COUNT = GetHPCount();
       HP = GetHP();
       KIRBYCLASS = GetKirbyClass();
       GameEngine::GetInst().ChangeLevel("Level2_2");
    }

    if (true == KirbyCol_->CollisionCheck("DoorCol2_3", CollisionType::Rect, CollisionType::Rect))
    {
        HP_COUNT = GetHPCount();
        HP = GetHP();
        KIRBYCLASS = GetKirbyClass();
        GameEngine::GetInst().ChangeLevel("Level2_3");
    }

    if (true == KirbyCol_->CollisionCheck("DoorCol2_4", CollisionType::Rect, CollisionType::Rect))
    {
        HP_COUNT = GetHPCount();
        HP = GetHP();
        KIRBYCLASS = GetKirbyClass();
        GameEngine::GetInst().ChangeLevel("Level2_4");
    }

    if (true == KirbyCol_->CollisionCheck("DoorCol2_5", CollisionType::Rect, CollisionType::Rect))
    {
        HP_COUNT = GetHPCount();
        HP = GetHP();
        KIRBYCLASS = GetKirbyClass();
        GameEngine::GetInst().ChangeLevel("Level2_5");
    }

    if (true == KirbyCol_->CollisionCheck("DoorCol3", CollisionType::Rect, CollisionType::Rect))
    {
        HP_COUNT = GetHPCount();
        HP = GetHP();
        KIRBYCLASS = GetKirbyClass();
        GameEngine::GetInst().ChangeLevel("Level3");
    }

    if (true == KirbyCol_->CollisionCheck("Boss", CollisionType::Rect, CollisionType::Rect))
    {
        HP_COUNT = GetHPCount();
        HP = GetHP();
        KIRBYCLASS = GetKirbyClass();
        GameEngine::GetInst().ChangeLevel("Boss");
    }

    if (true == KirbyCol_->CollisionCheck("CanCol", CollisionType::Rect, CollisionType::Rect))
    {
        KirbyCol_->Off();
    }

    if (ColMapImage_ != nullptr &&
        GetState() != KirbyState::DIE &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y - 25)))
    {
        while (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y)) &&
               RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x + 20), int(GetPosition().y - 25)))
        {
            SetMove(float4::LEFT);
        }
    }

    if (ColMapImage_ != nullptr &&
        GetState() != KirbyState::DIE &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 20.0f), int(GetPosition().y)) &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 20.0f), int(GetPosition().y - 25.0f)))
    {
        while (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 20.0f), int(GetPosition().y)) &&
               RGB(0, 0, 0) == ColMapImage_->GetImagePixel(int(GetPosition().x - 20.0f), int(GetPosition().y - 25.0f)))
        {
            SetMove(float4::RIGHT);
        }
    }

    if (GetPosition().x < 0 && GetState() != KirbyState::DIE)
    {
        SetPosition(float4(0, GetPosition().y));
    }

    if (GetPosition().x > GetLevel()->GetMapSizeX() && GetState() != KirbyState::DIE)
    {
        SetPosition(float4(GetLevel()->GetMapSizeX()-1.0f, GetPosition().y));
    }

    if (GetPosition().y < 70)
    {
        SetPosition(float4(GetPosition().x, 70));
    }

    if (RGB(16, 184, 152) == ColMapImage_->GetImagePixel(GetPosition() + float4::DOWN))
    {
        if (HPCount_ == 0)
        {
            GameEngine::GetInst().ChangeLevel("GameOver");
        }

        if (HPCount_ != 0)
        {
			--HPCount_;
			SetHP(10);
			SetPosition(StartPos_);
        }

    }

    std::vector<GameEngineCollision*> ColResult;
    while (true == KirbyCol_->CollisionResult("Obstruction", ColResult, CollisionType::Rect, CollisionType::Rect))
    {
        for (GameEngineCollision* BoxCollision : ColResult)
        {
            GameEngineActor* CollisionActor = BoxCollision->GetActor();
            if (CollisionActor != nullptr)
            {
                float XDir = CollisionActor->GetPosition().x - GetPosition().x;
                float YDir = CollisionActor->GetPosition().y - GetPosition().y;
            
                if (YDir > 0)
                {
                    SetMove(float4::UP);
                }
                else if (XDir <= 0)
                {
                    SetMove(float4::RIGHT);
                }

                else if (XDir > 0)
                {
                    SetMove(float4::LEFT);
                }

                else if (YDir <= 0)
                {
                    SetMove(float4::DOWN);
                }
            }
        }
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
	case KirbyState::ATTACKSTAY:
		UpdateAttackStay();
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
    case KirbyState::TAKEDAMAGE:
        UpdateTakeDamage();
        break;
    case KirbyState::ABANDON:
        UpdateAbandon();
        break;
    case KirbyState::EATEN:
        UpdateEaten();
        break;
    //case KirbyState::OPENDOOR:
    //    UpdateOpenDoor();
    //    break;
    default:
        break;
    }
}



bool Player::CheckMapCollision()
{
    if (nullptr != ColMapImage_)
    {
        //if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y))
        //{
        //   return true;
        //}

        //if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y))
        //{
        //   return true;
        //}

    //    if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50)
    //    {
    //       return true;
    //    }
    }
    return true;
}


void Player::Start()
{
    {
        Dir_ = "Right";
        SetSpeed(200);
        Level_ = GetLevel();
        ColMapImage_ = Level_->GetColMapImage();

        KirbyCol_ = CreateCollision("KirbyCol", float4(50.0f, 50.0f), float4(0.0f, -25.0f));
        KirbyEatCol_ = CreateCollision("KirbyEatCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
        KirbySlideCol_ = CreateCollision("KirbySlideCol", float4(30.0f, 30.0f), float4(0.0f, 0.0f));
        AnimalCol_ = CreateCollision("AnimalCol", float4(35.0f, 35.0f), float4(0.0f, 0.0f));
        SwordCol_ = CreateCollision("SwordCol", float4(100.0f, 150.0f), float4(0.0f, 0.0f));

        Renderer_ = CreateRenderer("Normal.bmp");
        GameEngineImage* Image_ = Renderer_->GetImage();
        Image_->CutCount(10, 26);
    }

    {
        //Default
        Renderer_->CreateAnimation("Normal.bmp", "WalkRight", 19, 28, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "WalkLeft", 109, 118, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "RunRight", 29, 36, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "RunLeft", 119, 126, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "IdleRight", 0, 0, 0.1f, false);
        Renderer_->CreateAnimation("Normal.bmp", "IdleLeft", 90, 90, 0.1f, false);

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

        Renderer_->CreateAnimation("Normal.bmp", "SlideRight", 47, 47, 0.5f, false);
        Renderer_->CreateAnimation("Normal.bmp", "SlideLeft", 137, 137, 0.5f, false);

        Renderer_->CreateAnimation("Normal.bmp", "TakeDamageRight", 172, 172, 0.5f, true);
        Renderer_->CreateAnimation("Normal.bmp", "TakeDamageLeft", 82, 82, 0.5f, true);

        Renderer_->CreateAnimation("Normal.bmp", "DoorOpenRight", 49, 52, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "DoorOpenLeft", 139, 142, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "Dance", 201, 207, 0.03f, true);
        Renderer_->CreateAnimation("Normal.bmp", "Die", 180, 95, 0.1f, true);
    }

	{
		//pig
		PigRenderer_ = CreateRenderer("Normal.bmp");
		PigImage_ = PigRenderer_->GetImage();
		PigImage_->CutCount(10, 26);

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
        //Beam
        BeamRenderer_ = CreateRenderer("Beam.bmp");
        GameEngineImage* BeamKirbyImage = BeamRenderer_->GetImage();
        BeamKirbyImage->CutCount(10, 30);

        BeamRenderer_->CreateAnimation("Beam.bmp", "WalkRight", 20, 31, 0.05f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "WalkLeft", 170, 181, 0.05f, true);

        BeamRenderer_->CreateAnimation("Beam.bmp", "RunRight", 32, 40, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "RunLeft", 182, 190, 0.1f, true);

        BeamRenderer_->CreateAnimation("Beam.bmp", "IdleRight", 0, 0, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "IdleLeft", 150, 150, 0.1f, true);

        BeamRenderer_->CreateAnimation("Beam.bmp", "FlyRight", 69, 73, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "FlyLeft", 219, 223, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "FlyStayRight", 74, 82, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "FlyStayLeft", 224, 232, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "FlyAttackRight", 83, 84, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "FlyAttackLeft", 233, 234, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "FlyEndRight", 66, 67, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "FlyEndLeft", 216, 217, 0.1f, true);

        BeamRenderer_->CreateAnimation("Beam.bmp", "AttackRight", 115, 116, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "AttackLeft", 265, 266, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "AttackStayRight", 117, 148, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "AttackStayLeft", 267, 298, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "AttackEndRight", 149, 149, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "AttackEndLeft", 299, 299, 0.1f, true);

        BeamRenderer_->CreateAnimation("Beam.bmp", "JumpUpRight", 41, 42, 0.5f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "JumpUpLeft", 191, 192, 0.5f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "JumpingRight", 43, 48, 0.03f, false);
        BeamRenderer_->CreateAnimation("Beam.bmp", "JumpingLeft", 193, 198, 0.03f, false);
        BeamRenderer_->CreateAnimation("Beam.bmp", "JumpDownRight", 49, 50, 0.5f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "JumpDownLeft", 199, 200, 0.5f, true);

        BeamRenderer_->CreateAnimation("Beam.bmp", "DownRight", 11, 11, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "DownLeft", 161, 161, 0.1f, true);

        BeamRenderer_->CreateAnimation("Beam.bmp", "SlideRight", 17, 18, 0.1f, false);
        BeamRenderer_->CreateAnimation("Beam.bmp", "SlideLeft", 167, 168, 0.1f, false);

        BeamRenderer_->CreateAnimation("Beam.bmp", "TakeDamageRight", 86, 86, 0.1f, true);
        BeamRenderer_->CreateAnimation("Beam.bmp", "TakeDamageLeft", 236, 236, 0.1f, true);

        BeamRenderer_->CreateAnimation("Beam.bmp", "DoorOpenRight", 0, 0, 0.1f, true); // 이미지 없음
        BeamRenderer_->CreateAnimation("Beam.bmp", "DoorOpenLeft", 0, 0, 0.1f, true);
    }


    {
		//Fire
		FireRenderer_ = CreateRenderer("Fire.bmp");
		GameEngineImage* FireKirbyImage = FireRenderer_->GetImage();
		FireKirbyImage->CutCount(10, 62);

		FireRenderer_->CreateAnimation("Fire.bmp", "WalkRight", 96, 115, 0.05f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "WalkLeft", 406, 425, 0.05f, true);

		FireRenderer_->CreateAnimation("Fire.bmp", "RunRight", 117, 123, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "RunLeft", 427, 433, 0.1f, true);

		FireRenderer_->CreateAnimation("Fire.bmp", "IdleRight", 0, 2, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "IdleLeft", 310, 313, 0.1f, true);

		FireRenderer_->CreateAnimation("Fire.bmp", "FlyRight", 128, 132, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "FlyLeft", 438, 442, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "FlyStayRight", 133, 161, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "FlyStayLeft", 443, 471, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "FlyAttackRight", 162, 163, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "FlyAttackLeft", 472, 473, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "FlyEndRight", 164, 165, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "FlyEndLeft", 474, 475, 0.1f, true);

		FireRenderer_->CreateAnimation("Fire.bmp", "AttackRight", 203, 208, 0.1f, true); 
		FireRenderer_->CreateAnimation("Fire.bmp", "AttackLeft", 513, 518, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "AttackStayRight", 209, 212, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "AttackStayLeft", 519, 522, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "AttackEndRight", 213, 214, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "AttackEndLeft", 523, 524, 0.1f, true);

		FireRenderer_->CreateAnimation("Fire.bmp", "JumpUpRight", 85, 86, 0.5f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "JumpUpLeft", 395, 396, 0.5f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "JumpingRight", 87, 92, 0.03f, false);
		FireRenderer_->CreateAnimation("Fire.bmp", "JumpingLeft", 397, 402, 0.03f, false);
		FireRenderer_->CreateAnimation("Fire.bmp", "JumpDownRight", 93, 94, 0.5f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "JumpDownLeft", 403, 404, 0.5f, true);

		FireRenderer_->CreateAnimation("Fire.bmp", "DownRight", 8, 11, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "DownLeft", 318, 321, 0.1f, true);

		FireRenderer_->CreateAnimation("Fire.bmp", "SlideRight", 80, 83, 0.1f, false); 
		FireRenderer_->CreateAnimation("Fire.bmp", "SlideLeft", 390, 393, 0.1f, false);

		FireRenderer_->CreateAnimation("Fire.bmp", "TakeDamageRight", 549, 549, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "TakeDamageLeft", 562, 562, 0.1f, true);

		FireRenderer_->CreateAnimation("Fire.bmp", "DoorOpenRight", 546, 541, 0.1f, true);
		FireRenderer_->CreateAnimation("Fire.bmp", "DoorOpenLeft", 236, 231, 0.1f, true);
    }

	{
		//Animal
		AnimalRenderer_ = CreateRenderer("Animal.bmp");
		GameEngineImage* AnimalImage = AnimalRenderer_->GetImage();
		AnimalImage->CutCount(10, 42);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "IdleRight", 0, 0, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "IdleLeft", 210, 210, 0.1f, true);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "WalkRight", 20, 29, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "WalkLeft", 230, 239, 0.1f, true);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "RunRight", 31, 38, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "RunLeft", 241, 248, 0.1f, true);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "FlyRight", 70, 72, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "FlyLeft", 280, 282, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "FlyStayRight", 73, 78, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "FlyStayLeft", 283, 288, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "FlyAttackRight", 72, 72, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "FlyAttackLeft", 282, 282, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "FlyEndRight", 48, 49, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "FlyEndLeft", 258, 259, 0.1f, true);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "AttackRight", 172, 177, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "AttackLeft", 382, 387, 0.1f, true);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "JumpUpRight", 41, 41, 0.5f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "JumpUpLeft", 251, 251, 0.5f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "JumpingRight", 42, 47, 0.03f, false);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "JumpingLeft", 252, 257, 0.03f, false);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "JumpDownRight", 48, 49, 0.5f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "JumpDownLeft", 258, 259, 0.5f, true);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "DownRight", 2, 2, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "DownLeft", 212, 212, 0.1f, true);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "SlideRight", 39, 39, 0.1f, false);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "SlideLeft", 249, 249, 0.1f, false);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "TakeDamageRight", 399, 399, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "TakeDamageLeft", 189, 189, 0.1f, true);

		AnimalRenderer_->CreateAnimation("Animal.bmp", "DoorOpenRight", 54, 57, 0.1f, true);
		AnimalRenderer_->CreateAnimation("Animal.bmp", "DoorOpenLeft", 264, 267, 0.1f, true);

	}

	{
		// Ice
		IceRenderer_ = CreateRenderer("Ice.bmp");
		IceKirbyImage_ = IceRenderer_->GetImage();
		IceKirbyImage_->CutCount(10, 18);

		IceRenderer_->CreateAnimation("Ice.bmp", "WalkRight", 13, 22, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "WalkLeft", 102, 111, 0.1f, true);

		IceRenderer_->CreateAnimation("Ice.bmp", "RunRight", 23, 30, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "RunLeft", 112, 119, 0.1f, true);

		IceRenderer_->CreateAnimation("Ice.bmp", "IdleRight", 0, 0, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "IdleLeft", 89, 89, 0.1f, true);

		IceRenderer_->CreateAnimation("Ice.bmp", "FlyRight", 32, 36, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "FlyLeft", 121, 125, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "FlyStayRight", 37, 42, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "FlyStayLeft", 126, 131, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "FlyAttackRight", 43, 44, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "FlyAttackLeft", 132, 133, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "FlyEndRight", 45, 46, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "FlyEndLeft", 134, 135, 0.1f, true);

		IceRenderer_->CreateAnimation("Ice.bmp", "AttackRight", 79, 84, 0.08f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "AttackLeft", 168, 173, 0.08f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "AttackStayRight", 85, 86, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "AttackStayLeft", 174, 175, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "AttackEndRight", 87, 88, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "AttackEndLeft", 176, 177, 0.1f, true);

		IceRenderer_->CreateAnimation("Ice.bmp", "JumpUpRight", 4, 4, 0.5f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "JumpUpLeft", 93, 93, 0.5f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "JumpingRight", 5, 10, 0.03f, false);
		IceRenderer_->CreateAnimation("Ice.bmp", "JumpingLeft", 94, 99, 0.03f, false);
		IceRenderer_->CreateAnimation("Ice.bmp", "JumpDownRight", 11, 12, 0.3f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "JumpDownLeft", 100, 101, 0.3f, true);

		IceRenderer_->CreateAnimation("Ice.bmp", "DownRight", 1, 1, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "DownLeft", 90, 90, 0.1f, true);

		IceRenderer_->CreateAnimation("Ice.bmp", "SlideRight", 2, 2, 0.1f, false); 
		IceRenderer_->CreateAnimation("Ice.bmp", "SlideLeft", 91, 91, 0.1f, false);

		IceRenderer_->CreateAnimation("Ice.bmp", "TakeDamageRight", 60, 60, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "TakeDamageLeft", 73, 73, 0.1f, true);

		IceRenderer_->CreateAnimation("Ice.bmp", "DieRight", 59, 74, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "DieLeft", 148, 163, 0.1f, true);

		IceRenderer_->CreateAnimation("Ice.bmp", "DoorOpenRight", 75, 78, 0.1f, true);
		IceRenderer_->CreateAnimation("Ice.bmp", "DoorOpenLeft", 164, 167, 0.1f, true);
	}

	{
		//Sword
		SwordRenderer_ = CreateRenderer("Sword.bmp");
		SwordKirbyImage_ = SwordRenderer_->GetImage();
		SwordKirbyImage_->CutCount(10, 36);

		SwordRenderer_->CreateAnimation("Sword.bmp", "WalkRight", 33, 44, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "WalkLeft", 213, 224, 0.1f, true);

		SwordRenderer_->CreateAnimation("Sword.bmp", "RunRight", 45, 52, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "RunLeft", 225, 232, 0.1f, true);

		SwordRenderer_->CreateAnimation("Sword.bmp", "IdleRight", 0, 0, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "IdleLeft", 180, 180, 0.1f, true);

		SwordRenderer_->CreateAnimation("Sword.bmp", "FlyRight", 56, 60, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "FlyLeft", 236, 240, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "FlyStayRight", 61, 78, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "FlyStayLeft", 241, 258, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "FlyAttackRight", 79, 80, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "FlyAttackLeft", 259, 260, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "FlyEndRight", 81, 82, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "FlyEndLeft", 261, 262, 0.1f, true);

		SwordRenderer_->CreateAnimation("Sword.bmp", "AttackRight", 150, 165, 0.05f, true); 
		SwordRenderer_->CreateAnimation("Sword.bmp", "AttackLeft", 330, 345, 0.1f, true);

		SwordRenderer_->CreateAnimation("Sword.bmp", "JumpUpRight", 134, 134, 0.5f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "JumpUpLeft", 314, 314, 0.5f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "JumpingRight", 83, 91, 0.03f, false);
		SwordRenderer_->CreateAnimation("Sword.bmp", "JumpingLeft", 263, 271, 0.03f, false);
		SwordRenderer_->CreateAnimation("Sword.bmp", "JumpDownRight", 92, 93, 0.5f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "JumpDownLeft", 272, 273, 0.5f, true);

		SwordRenderer_->CreateAnimation("Sword.bmp", "DownRight", 10, 10, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "DownLeft", 190, 190, 0.1f, true);

		SwordRenderer_->CreateAnimation("Sword.bmp", "SlideRight", 20, 20, 0.1f, false);
		SwordRenderer_->CreateAnimation("Sword.bmp", "SlideLeft", 200, 200, 0.1f, false);

		SwordRenderer_->CreateAnimation("Sword.bmp", "TakeDamageRight", 97, 97, 0.1f, true);
		SwordRenderer_->CreateAnimation("Sword.bmp", "TakeDamageLeft", 277, 277, 0.1f, true);

        SwordRenderer_->CreateAnimation("Sword.bmp", "DoorOpenRight", 75, 78, 0.1f, true); // need to chk
        SwordRenderer_->CreateAnimation("Sword.bmp", "DoorOpenLeft", 164, 167, 0.1f, true); // need to chk
	}


    {
		//Spark
        SparkRenderer_ = CreateRenderer("Spark.bmp");
        GameEngineImage* SparkImage = SparkRenderer_->GetImage();
        SparkImage->CutCount(10, 40);

        SparkRenderer_->CreateAnimation("Spark.bmp", "WalkRight", 40, 59, 0.05f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "WalkLeft", 240, 259, 0.05f, true);
        
        SparkRenderer_->CreateAnimation("Spark.bmp", "RunRight", 60, 67, 0.1f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "RunLeft", 260, 267, 0.1f, true);
        
        SparkRenderer_->CreateAnimation("Spark.bmp", "IdleRight", 0, 2, 0.1f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "IdleLeft", 200, 203, 0.1f, true);
        
        SparkRenderer_->CreateAnimation("Spark.bmp", "FlyRight", 72, 76, 0.05f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "FlyLeft", 272, 276, 0.05f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "FlyStayRight", 77, 105, 0.1f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "FlyStayLeft", 277, 305, 0.1f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "FlyAttackRight", 106, 107, 0.1f, false);
        SparkRenderer_->CreateAnimation("Spark.bmp", "FlyAttackLeft", 306, 307, 0.1f, false);
        SparkRenderer_->CreateAnimation("Spark.bmp", "FlyEndRight", 108, 109, 0.1f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "FlyEndLeft", 308, 309, 0.1f, true);
        
        SparkRenderer_->CreateAnimation("Spark.bmp", "AttackRight", 186, 186, 0.3f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "AttackLeft", 386, 386, 0.3f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "AttackStayRight", 187, 192, 0.1f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "AttackStayLeft", 387, 392, 0.1f, true);


        SparkRenderer_->CreateAnimation("Spark.bmp", "JumpUpRight", 13, 14, 0.5f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "JumpUpLeft", 213, 214, 0.5f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "JumpingRight", 15, 20, 0.03f, false);
        SparkRenderer_->CreateAnimation("Spark.bmp", "JumpingLeft", 215, 220, 0.03f, false);
        SparkRenderer_->CreateAnimation("Spark.bmp", "JumpDownRight", 21, 22, 0.5f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "JumpDownLeft", 221, 222, 0.5f, true);
        
        SparkRenderer_->CreateAnimation("Spark.bmp", "DownRight", 4, 7, 0.1f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "DownLeft", 204, 207, 0.1f, true);
        
        SparkRenderer_->CreateAnimation("Spark.bmp", "SlideRight", 8, 11, 0.1f, false);
        SparkRenderer_->CreateAnimation("Spark.bmp", "SlideLeft", 208, 211, 0.1f, false);
        
        SparkRenderer_->CreateAnimation("Spark.bmp", "TakeDamageRight", 126, 126, 0.1f, true);
        SparkRenderer_->CreateAnimation("Spark.bmp", "TakeDamageLeft", 326, 326, 0.1f, true);
        
        SparkRenderer_->CreateAnimation("Spark.bmp", "DoorOpenRight", 181, 185, 0.1f, true); // need to chk
        SparkRenderer_->CreateAnimation("Spark.bmp", "DoorOpenLeft", 164, 167, 0.1f, true); // need to chk

    }

    SetState(KirbyState::IDLE);
    SetHPCount(HP_COUNT);
    SetHP(HP);
    SetKirbyClass(KIRBYCLASS);
    if (false == GameEngineInput::GetInst()->IsKey("Left"))
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
        GameEngineInput::GetInst()->CreateKey("OpenDoor", VK_SPACE);

        
        
        GameEngineInput::GetInst()->CreateKey("ResetPos", 'P');
        GameEngineInput::GetInst()->CreateKey("Spark", '1');
        GameEngineInput::GetInst()->CreateKey("Fire", '2');
        GameEngineInput::GetInst()->CreateKey("Sword", '3');
        GameEngineInput::GetInst()->CreateKey("Animal", '4');
        GameEngineInput::GetInst()->CreateKey("Ice", '5');
        GameEngineInput::GetInst()->CreateKey("Beam", '6');
        //GameEngineInput::GetInst()->CreateKey("AbandonClass", 'O');
     }
}