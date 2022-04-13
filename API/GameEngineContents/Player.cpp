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
    , AccGravity_(0.0f)
    , JumpHeight_(0.0f)
    , Time_(3.0f)
    , Level_(nullptr)
    , HPCount_(0)
    , Speed_(20)
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
        Renderer_->SetScale(float4 (0.0f, 0.0f)); // Renderer_->Death(); 사용??
        SparkKirbyRenderer_->SetImageScale();
        break;
    case KirbyClass::ANIMAL:
        break;
    case KirbyClass::BEAM:
        break;
    case KirbyClass::DEFAULT:
        break;
    case KirbyClass::FIRE:
        break;
    case KirbyClass::ICE:
        break;
    case KirbyClass::SWORD:
        break;
    case KirbyClass::PIG:
        break;
    default:
        Renderer_->SetImageScale();
        SparkKirbyRenderer_->SetScale(float4(0.0f, 0.0f));
        break;
    }
}

void Player::SetState(KirbyState _KirbyState)
{
    KirbyState_ = _KirbyState;
    switch (KirbyState_)
    {
    case KirbyState::IDLE:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Idle" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Idle" + Dir_);
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
        break;


    case KirbyState::EATSTART:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("EatStart" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("EatStart" + Dir_);
        }
        break;

    case KirbyState::EAT:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Eat" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Eat" + Dir_);
        }
        break;

    case KirbyState::EATEND:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("EatEnd" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("EatEnd" + Dir_);
        }
        break;


    case KirbyState::STARATTACK:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("StarAttack" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("StarAttack" + Dir_);
        }
        break;
    case KirbyState::TRANSFORM:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Transform" + Dir_);
            KirbyEffect_->ChangeAnimation("Transform");
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Transform" + Dir_);
            KirbyEffect_->ChangeAnimation("Transform");
        }
		break;


    case KirbyState::GETDAMAGE:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("GetDamage" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("GetDamage" + Dir_);
        }
        break;



    case KirbyState::JUMPUP:
        PrevPos_ = GetPosition();
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("JumpUp" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("JumpUp" + Dir_);
        }
        break;
    case KirbyState::JUMPING:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("Jumping" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("Jumping" + Dir_);
        }
        break;
    case KirbyState::JUMPDOWN:
        PrevPos_ = GetPosition();
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("JumpDown" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("JumpDown" + Dir_);
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
        break;

    case KirbyState::SLIDESTAY:
        if (GetKirbyClass() == KirbyClass::SPARK)
        {
            SparkKirbyRenderer_->ChangeAnimation("SlideStay" + Dir_);
        }
        if (GetKirbyClass() == KirbyClass::DEFAULT)
        {
            Renderer_->ChangeAnimation("SlideStay" + Dir_);
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
        break;

    default:
        break;
    }

    StateUpdate();
}


void Player::Update()
{
    SetSpeed(100);
    float4 direction = float4::ZERO;
    PrevPos_ = GetPosition();



    if (true == GameEngineInput::GetInst()->IsUp("Spark")) // transform
    {
        SetState(KirbyState::TRANSFORM);
        //Renderer_->Death();
    }

    if (true == GameEngineInput::GetInst()->IsPress("WalkLeft") 
        && GetState() != KirbyState::JUMPUP
        && GetState() != KirbyState::JUMPING
        && GetState() != KirbyState::JUMPDOWN)
    {
        SetState(KirbyState::WALK);
    }
    else if (true == GameEngineInput::GetInst()->IsPress("WalkRight")
        && GetState() != KirbyState::JUMPUP
        && GetState() != KirbyState::JUMPING
        && GetState() != KirbyState::JUMPDOWN)
    {
        SetState(KirbyState::WALK);
    }

    if (true == GameEngineInput::GetInst()->IsPress("RunLeft")
        && GetState() != KirbyState::JUMPUP
        && GetState() != KirbyState::JUMPING
        && GetState() != KirbyState::JUMPDOWN)
    {
        SetState(KirbyState::RUN);
    }
    else if (true == GameEngineInput::GetInst()->IsPress("RunRight")
        && GetState() != KirbyState::JUMPUP
        && GetState() != KirbyState::JUMPING
        && GetState() != KirbyState::JUMPDOWN)
    {
        SetState(KirbyState::RUN);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Fly"))
    {
        SetState(KirbyState::FLY);
    }

    if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
    {
        SetState(KirbyState::UP);
    }

    if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
    {
        SetState(KirbyState::DOWN);
    }

    if (true == GameEngineInput::GetInst()->IsUp("Jump") &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x, GetPosition().y + 1)) // 공중에서 점프 불가
    {
        SetState(KirbyState::JUMPUP);
    }

    if (true == GameEngineInput::GetInst()->IsPress("ResetPos"))
    {
        SetPosition(float4(205.0, 436.0f));
        AccGravity_ = 0;
    }

    if (true == GameEngineInput::GetInst()->IsPress("SlideLeft"))
    {
        SetState(KirbyState::SLIDE);
    }

    else if (true == GameEngineInput::GetInst()->IsPress("SlideRight"))
    {
        SetState(KirbyState::SLIDE);
    }

    if (true == GameEngineInput::GetInst()->IsPress("Eat"))
    {
        SetState(KirbyState::EATSTART);
    }


	AccGravity_ += Gravity_ * GameEngineTime::GetDeltaTime();
	JumpHeight_ = JumpHeight_ - AccGravity_;

    // 땅에 닿았을 때
    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x, GetPosition().y-JumpHeight_))
    {
        JumpHeight_ = 0;
        AccGravity_ = 0;
        if (true == GameEngineInput::GetInst()->IsFree("WalkLeft") &&
            true == GameEngineInput::GetInst()->IsFree("WalkRight") &&
            true == GameEngineInput::GetInst()->IsFree("RunLeft") &&
            true == GameEngineInput::GetInst()->IsFree("RunRight") &&
            true == GameEngineInput::GetInst()->IsFree("MoveDown") &&
            true == GameEngineInput::GetInst()->IsFree("SlideRight") &&
            true == GameEngineInput::GetInst()->IsFree("SlideLeft") &&
            true == GameEngineInput::GetInst()->IsFree("Jump") &&
            true == GameEngineInput::GetInst()->IsFree("Eat"))
        {
			SetState(KirbyState::IDLE);
        }
    }
    // 떠 있을 때
    else
    {
        SetMove(float4(0, -JumpHeight_));
        // 이거랑 updatejumping이 겹쳐서 여러번 구름
        //if (JumpHeight_ < 15 && GetState() != KirbyState::JUMPDOWN)
        //{
        //    //SetState(KirbyState::JUMPING);
        //}
    }

    // 능력 버리기
    if (GetKirbyClass() != KirbyClass::DEFAULT)
    {
        if (true == GameEngineInput::GetInst()->IsUp("AbandonClass"))
        {
            
            SetKirbyClass(KirbyClass::DEFAULT);
        }
    }


//if (CurrentPos.x > GetLevel()->GetMapSizeX())
//{
//   SetPosition(float4(GetLevel()->GetMapSizeX(), CurrentPos.y));
//}

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
    //float4 CurrentPos = GetPosition();
    //float4 JumpDirection = PrevPos_ - GetPosition();
    //float JumpDirectionX = JumpDirection.x > 0 ? float4::RIGHT.x : float4::LEFT.x;
    //float JumpDirectionY = JumpDirection.y > 0 ? float4::DOWN.y : float4::UP.y;
  //   while (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x, GetPosition().y))
    //{
    //   SetMove(float4(0, JumpDirectionY));
    //   AccGravity_ = 0;
    //   JumpHeight_ = 0;
    //}

    //while ((RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y) && RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y - 40))
    //   || (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y) && RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y - 40)))
    //{
    //   SetMove(float4(JumpDirectionX, 0));
    //}

    //if (CurrentPos.x < 0)
    //{
    //   SetPosition(float4(0, CurrentPos.y));
    //}

    //if (CurrentPos.x > GetLevel()->GetMapSizeX())
    //{
    //   SetPosition(float4(GetLevel()->GetMapSizeX(), CurrentPos.y));
    //}

    //if (CurrentPos.y < 50)
    //{
    //   SetPosition(float4(CurrentPos.x, 50));
    //}
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

    if (true == KirbyCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect) && Time_ >= 3)
    {
       Time_ = 0;
       SetHP(GetHP() - 1);
       if (GetHP() > 0)
       {
           KirbyState::IDLE;
       }
       else
       {
           --HPCount_;
           KirbyState::DIE;
       }
    }

    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y))
    {
        SetPosition(PrevPos_);
    }

    if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y))
    {
        SetPosition(PrevPos_);
    }

    if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50)
    {
        SetPosition(PrevPos_);
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
    case KirbyState::FLYSTAY:
        UpdateFlyStay();
        break;
    case KirbyState::FLYATTACK:
        UpdateFlyAttack();
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
    case KirbyState::EAT:
        UpdateEat();
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
    case KirbyState::EATSTART:
        UpdateEatStart();
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
    {
        // NormalKirby
		Dir_ = "Right";
		Level_ = GetLevel();
		SetHPCount(2);
		SetHP(9);
		ColMapImage_ = Level_->GetColMapImage();
		KirbyCol_ = CreateCollision("KirbyCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));

		Renderer_ = CreateRenderer("Normal.bmp");
		GameEngineImage* Image = Renderer_->GetImage();
		Image->CutCount(10, 19);

		Renderer_->CreateAnimation("Normal.bmp", "WalkRight", 19, 28, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "WalkLeft", 111, 120, 0.1f, true);

		Renderer_->CreateAnimation("Normal.bmp", "RunRight", 29, 36, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "RunLeft", 121, 128, 0.1f, true);

		Renderer_->CreateAnimation("Normal.bmp", "IdleRight", 0, 0, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "IdleLeft", 92, 92, 0.1f, true);

		Renderer_->CreateAnimation("Normal.bmp", "FlyRight", 64, 69, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyLeft", 156, 161, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyStayRight", 70, 75, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyStayLeft", 162, 167, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyAttackRight", 85, 88, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyAttackLeft", 177, 180, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyEndRight", 89, 90, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "FlyEndLeft", 181, 182, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "EatStartRight", 64, 69, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "EatStartLeft", 156, 161, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "EatRight", 85, 86, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "EatLeft", 177, 178, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "EatEndRight", 76, 78, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "EatEndLeft", 168, 170, 0.1f, true);
        
        // pig
        Renderer_->CreateAnimation("Normal.bmp", "PigIdleRight", 79, 79, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "PigIdleLeft", 171, 171, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "PigWalkRight", 2, 17, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "PigWalkLeft", 94, 109, 0.1f, true);
        //


		Renderer_->CreateAnimation("Normal.bmp", "StarAttackRight", 18, 18, 0.3f, true);
		Renderer_->CreateAnimation("Normal.bmp", "StarAttackLeft", 110, 110, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "TransformRight", 79, 84, 0.3f, false);
        Renderer_->CreateAnimation("Normal.bmp", "TransformLeft", 171, 176, 0.1f, false);

		Renderer_->CreateAnimation("Normal.bmp", "JumpUpRight", 38, 38, 0.5f, true);
		Renderer_->CreateAnimation("Normal.bmp", "JumpUpLeft", 130, 130, 0.5f, true);
		Renderer_->CreateAnimation("Normal.bmp", "JumpingRight", 39, 44, 0.1f, false);
		Renderer_->CreateAnimation("Normal.bmp", "JumpingLeft", 131, 137, 0.f, false);
        Renderer_->CreateAnimation("Normal.bmp", "JumpDownRight", 45, 46, 0.5f, true);
        Renderer_->CreateAnimation("Normal.bmp", "JumpDownLeft", 138, 139, 0.5f, true);

        Renderer_->CreateAnimation("Normal.bmp", "DownRight", 1, 1, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "DownLeft", 93, 93, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "SlideRight", 184, 185, 0.1f, false);
        Renderer_->CreateAnimation("Normal.bmp", "SlideLeft", 186, 187, 0.1f, false);
		Renderer_->CreateAnimation("Normal.bmp", "SlideStayRight", 185, 185, 0.5f, false);
		Renderer_->CreateAnimation("Normal.bmp", "SlideStayLeft", 187, 187, 0.5f, false);

        Renderer_->CreateAnimation("Normal.bmp", "GetDamageRight", 184, 185, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "GetDamageLeft", 184, 185, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "DieRight", 184, 185, 0.1f, true); // 동작 확인 필요
        Renderer_->CreateAnimation("Normal.bmp", "DieLeft", 184, 185, 0.1f, true);
	}


    {
        SparkKirbyRenderer_ = CreateRenderer("SparkKirby.bmp");
        GameEngineImage* SparkImage = SparkKirbyRenderer_->GetImage();
        SparkImage->CutCount(10, 23);

        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "TransformRight", 10, 22, 0.1f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "TransformLeft", 123, 135, 0.1f, true);


        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "WalkRight", 10, 22, 0.1f, true); 
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "WalkLeft", 123, 135, 0.1f, true);
                                    
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "RunRight", 28, 33, 0.1f, true);
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
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "SlideStayRight", 9, 9, 0.5f, true);
        SparkKirbyRenderer_->CreateAnimation("SparkKirby.bmp", "SlideStayLeft", 122, 122, 0.5f, true);
    }

    {
        KirbyEffect_ = CreateRenderer("Transform.bmp");
        GameEngineImage* TransformEffectImage = KirbyEffect_->GetImage();
        TransformEffectImage->CutCount(10, 2);
        KirbyEffect_->CreateAnimation("Transform.bmp", "Transform", 0, 13, 0.1f, false);

        KirbyEffectCol_ = CreateCollision("TransformEffect", float4(0.1f, 0.1f), float4(0.1f, 0.1f));
    }


    //AttackEffectRenderer_ = CreateRenderer("Attack.bmp"   ,static_cast<int>(EngineMax::RENDERORDERMAX),RenderPivot::CENTER,float4(100.0f,0.0f));
    //GameEngineImage* Attack_ = AttackEffectRenderer_->GetImage();
    //Attack_->CutCount(7, 2);
    //A ttackEffectRenderer_->CreateAnimation("Attack.bmp", "Attack", 0, 12, 0.1f, false);
    AttackEffectCol_ = CreateCollision("KirbyEffect", float4(40.0f, 40.0f), float4(100.0f, -20.0f)); // HoverKirbyEnd2가 바닥에 닿아 끝나면
    //AttackEffectRenderer_->CreateAnimation("AttackEffect.bmp", "AttackEffect", 0, 12, 0.1f, false);

    SetState(KirbyState::IDLE);
    SetKirbyClass(KirbyClass::DEFAULT);
    if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
    {
        GameEngineInput::GetInst()->CreateKey("WalkLeft", 'S');
        GameEngineInput::GetInst()->CreateKey("WalkRight", 'F');
        GameEngineInput::GetInst()->CreateKey("MoveUp", 'E');
        GameEngineInput::GetInst()->CreateKey("MoveDown", 'D');
        GameEngineInput::GetInst()->CreateKey("Jump", VK_LSHIFT);
        GameEngineInput::GetInst()->CreateKey("Hover", VK_SPACE);
        GameEngineInput::GetInst()->CreateKey("Eat", 'X');
        GameEngineInput::GetInst()->CreateKey("RunLeft", 'W');
        GameEngineInput::GetInst()->CreateKey("RunRight", 'R');
        GameEngineInput::GetInst()->CreateKey("Inhale", 'Z'); // 흡입
        GameEngineInput::GetInst()->CreateKey("Fly", 'X'); // 날기
        GameEngineInput::GetInst()->CreateKey("ResetPos", 'P');
        GameEngineInput::GetInst()->CreateKey("SlideLeft", 'A');
        GameEngineInput::GetInst()->CreateKey("SlideRight", 'G');
        GameEngineInput::GetInst()->CreateKey("Spark", 'T');
        GameEngineInput::GetInst()->CreateKey("AbandonClass", 'O');


    }
}