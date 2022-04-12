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
#include "Level1.h"
#include "Level1_2.h"
#include "Level1_3.h"
#include "Level1_4.h"
#include "Level2.h"
#include "Level2_2.h"
#include "Monster.h"

Player::Player()
    : Renderer_(nullptr)
    , Gravity_(9.8f)
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
}

KirbyClass Player::GetKirbyClass()
{
    return KirbyClass_;
}

void Player::SetState(KirbyState _KirbyState)
{
    KirbyState_ = _KirbyState;
    switch (KirbyState_)
    {
    case KirbyState::IDLE:
        Renderer_->ChangeAnimation("Idle" + Dir_);
        break;
    case KirbyState::UP:
        // 사다리 타기 구현
        break;
    case KirbyState::DOWN:
        Renderer_->ChangeAnimation("Down" + Dir_);
        break;
    case KirbyState::WALK:
        Renderer_->ChangeAnimation("Walk" + Dir_);
        break;
    case KirbyState::RUN:
        Renderer_->ChangeAnimation("Run" + Dir_);
        break;


    case KirbyState::FLY:
        Renderer_->ChangeAnimation("Fly" + Dir_);
        StateUpdate();
        break;
    case KirbyState::FLYSTAY:
        Renderer_->ChangeAnimation("FlyStay" + Dir_);
        break;
    case KirbyState::FLYATTACK:
        Renderer_->ChangeAnimation("FlyAttack" + Dir_);
        StateUpdate();
        break;
    case KirbyState::FLYEND:
        Renderer_->ChangeAnimation("FlyEnd" + Dir_);
        StateUpdate();
        break;


    case KirbyState::EATSTART:
        Renderer_->ChangeAnimation("EatStart" + Dir_);
        break;
    case KirbyState::EAT:
        Renderer_->ChangeAnimation("Eat" + Dir_);
        break;
    case KirbyState::EATEND:
        Renderer_->ChangeAnimation("EatEnd" + Dir_);
        break;


    case KirbyState::STARATTACK:
        Renderer_->ChangeAnimation("StarAttack" + Dir_);
        break;
    case KirbyState::TRANSFORM:
		Renderer_->ChangeAnimation("Transform" + Dir_);
		break;
	case KirbyState::TRANSFORMEND:
		Renderer_->ChangeAnimation("Transform" + Dir_);
		break;


    case KirbyState::GETDAMAGE:
        Renderer_->ChangeAnimation("GetDamage" + Dir_);
        break;



    case KirbyState::JUMP:
        PrevPos_ = GetPosition();
        Renderer_->ChangeAnimation("Jump" + Dir_);
        break;
    case KirbyState::JUMPING:
        PrevPos_ = GetPosition();
        Renderer_->ChangeAnimation("Jumping" + Dir_);
        break;

    case KirbyState::SLIDE:
        Renderer_->ChangeAnimation("Slide" + Dir_);
        break;
    case KirbyState::SLIDESTAY:
        Renderer_->ChangeAnimation("SlideStay" + Dir_);
        break;
    case KirbyState::DIE:
        Renderer_->ChangeAnimation("SlideStay" + Dir_);
        break;


    default:
        break;
    }

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

        Renderer_->CreateAnimation("Normal.bmp", "TransformRight", 79, 84, 0.3f, true);
        Renderer_->CreateAnimation("Normal.bmp", "TransformAttackLeft", 171, 176, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "TransformEndRight", 85, 85, 0.3f, true); // 변신 완료 동작
        Renderer_->CreateAnimation("Normal.bmp", "TransformEndAttackLeft", 177, 177, 0.1f, true);

		Renderer_->CreateAnimation("Normal.bmp", "JumpRight", 38, 38, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "JumpLeft", 130, 130, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "JumpingRight", 39, 44, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "JumpingLeft", 131, 137, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "DownRight", 1, 1, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "DownLeft", 93, 93, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "SlideRight", 184, 185, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "SlideLeft", 186, 187, 0.1f, true);
		Renderer_->CreateAnimation("Normal.bmp", "SlideStayRight", 185, 185, 0.5f, true);
		Renderer_->CreateAnimation("Normal.bmp", "SlideStayLeft", 187, 187, 0.5f, true);

        Renderer_->CreateAnimation("Normal.bmp", "GetDamageRight", 184, 185, 0.1f, true);
        Renderer_->CreateAnimation("Normal.bmp", "GetDamageLeft", 184, 185, 0.1f, true);

        Renderer_->CreateAnimation("Normal.bmp", "DieRight", 184, 185, 0.1f, true); // 동작 확인 필요
        Renderer_->CreateAnimation("Normal.bmp", "DieLeft", 184, 185, 0.1f, true);
	}


    {
        // SparkKirby
        //Renderer_ = CreateRenderer("SparkKirby.bmp");
        //GameEngineImage* Image = Renderer_->GetImage();
        //Image->CutCount(10, 23);

        //Renderer_->CreateAnimation("SparkKirby.bmp", "WalkRight", 10, 16, 0.1f, true); // need chk img
        //Renderer_->CreateAnimation("SparkKirby.bmp", "WalkLeft", 123, 129, 0.1f, true); // need chk img
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "RunRight", 28, 34, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "RunLeft", 141, 147, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "IdleRight", 3, 3, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "IdleLeft", 116, 116, 0.1f, true); // ok
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "FlyRight", 64, 69, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "FlyLeft", 156, 161, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "FlyStayRight", 70, 75, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "FlyStayLeft", 162, 167, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "HoverEndRight", 85, 88, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "HoverEndLeft", 177, 180, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "HoverEnd2Right", 89, 90, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "HoverEnd2Left", 181, 182, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "EATRight", 76, 78, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "EATLeft", 168, 178, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "IdleWzMonsterRight", 79, 79, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "IdleWzMonsterLeft", 171, 171, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "WalkWzMonsterRight", 2, 17, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "WalkWzMonsterLeft", 94, 109, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "FlyAttackRight", 18, 18, 0.3f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "FlyAttackLeft", 110, 110, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "AttackRight", 18, 18, 0.3f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "AttackLeft", 110, 110, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "DownRight", 4, 4, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "DownLeft", 117, 117, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "JumpRight", 38, 38, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "JumpLeft", 38, 38, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "JumpingRight", 39, 44, 0.1f, true);
        //Renderer_->CreateAnimation("SparkKirby.bmp", "JumpingLeft", 39, 44, 0.1f, true);
        //                            
        //Renderer_->CreateAnimation("SparkKirby.bmp", "SlideRight", 5, 9, 0.5f, true); // need to chk img :: 오른쪽 바라보는 이미지를 앞에 추가
        //Renderer_->CreateAnimation("SparkKirby.bmp", "SlideLeft", 118, 122, 0.5f, true); // "
    }

    {

    }


    //AttackEffectRenderer_ = CreateRenderer("Attack.bmp"   ,static_cast<int>(EngineMax::RENDERORDERMAX),RenderPivot::CENTER,float4(100.0f,0.0f));
    //GameEngineImage* Attack_ = AttackEffectRenderer_->GetImage();
    //Attack_->CutCount(7, 2);
    //A ttackEffectRenderer_->CreateAnimation("Attack.bmp", "Attack", 0, 12, 0.1f, false);
    AttackEffectCol_ = CreateCollision("KirbyEffect", float4(40.0f, 40.0f), float4(100.0f, -20.0f)); // HoverKirbyEnd2가 바닥에 닿아 끝나면
    //AttackEffectRenderer_->CreateAnimation("AttackEffect.bmp", "AttackEffect", 0, 12, 0.1f, false);

    SetState(KirbyState::IDLE);

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
        GameEngineInput::GetInst()->CreateKey("ResetPos", 'P'); // 날기
        GameEngineInput::GetInst()->CreateKey("SlideLeft", 'A');
        GameEngineInput::GetInst()->CreateKey("SlideRight", 'G');

    }
}

void Player::Update()
{
    SetSpeed(100);
    float4 direction = float4::ZERO;
    if (true == GameEngineInput::GetInst()->IsPress("WalkLeft"))
    {
        SetState(KirbyState::WALK);
        StateUpdate();
    }
    else if (true == GameEngineInput::GetInst()->IsPress("WalkRight"))
    {
        SetState(KirbyState::WALK);
        StateUpdate();
    }

    if (true == GameEngineInput::GetInst()->IsPress("RunLeft"))
    {
        SetState(KirbyState::RUN);
        StateUpdate();
    }
    else if (true == GameEngineInput::GetInst()->IsPress("RunRight"))
    {
        SetState(KirbyState::RUN);
        StateUpdate();
    }

    if (true == GameEngineInput::GetInst()->IsPress("Fly"))
    {
        SetState(KirbyState::FLY);
    }

    if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
    {
        SetState(KirbyState::UP);
        StateUpdate();
    }

    if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
    {
        SetState(KirbyState::DOWN);
        StateUpdate();
    }

    if (true == GameEngineInput::GetInst()->IsUp("Jump") &&
        RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x, GetPosition().y+1)) // 공중에서 점프 불가
    {
        SetState(KirbyState::JUMP);
        StateUpdate();
    }

    if (true == GameEngineInput::GetInst()->IsPress("ResetPos"))
    {
        SetPosition(float4(205.0, 436.0f));
        AccGravity_ = 0;
    }

    if (true == GameEngineInput::GetInst()->IsPress("SlideLeft"))
    {
        SetState(KirbyState::SLIDE);
        StateUpdate();
    }

    else if (true == GameEngineInput::GetInst()->IsPress("SlideRight"))
    {
        SetState(KirbyState::SLIDE);
        StateUpdate();
    }

    if (true == GameEngineInput::GetInst()->IsPress("Eat"))
    {
        SetState(KirbyState::EATSTART);
        StateUpdate();
    }


	AccGravity_ += Gravity_ * GameEngineTime::GetDeltaTime();
	JumpHeight_ = JumpHeight_ - AccGravity_;
	SetMove(float4(0, -JumpHeight_));

    if (true == GameEngineInput::GetInst()->IsUp("WalkLeft") ||
        true == GameEngineInput::GetInst()->IsUp("WalkRight") ||
        true == GameEngineInput::GetInst()->IsUp("RunLeft") ||
        true == GameEngineInput::GetInst()->IsUp("RunRight") ||
        true == GameEngineInput::GetInst()->IsUp("MoveDown") ||
        true == GameEngineInput::GetInst()->IsUp("SlideRight") ||
        true == GameEngineInput::GetInst()->IsUp("SlideLeft"))
    {
        SetState(KirbyState::IDLE);
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

//void Player::UpdateJump()
//{
//   //AccGravity_ += Gravity_ * GameEngineTime::GetDeltaTime();
//   //float JumpHeight = JumpHeight_ - AccGravity_;
//   //SetMove(float4(0, -JumpHeight));
//}

//void Player::UpdateFly()
//{
//   //CharacterState State = GetState();
//   //if (State == CharacterState::HOVER)
//   //{
//   //   if (true == Renderer_->IsAnimationName("HoveringRight"))
//   //   {
//   //      SetMove(float4::UP * GameEngineTime::GetDeltaTime() * static_cast<float>(GetSpeed()));
//   //      AccGravity_ = 0;
//   //      JumpHeight_ = 0;
//   //   }
//   //}
//}
//}



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
    //if (true == KirbyCol_->CollisionCheck("DoorCol1_2", CollisionType::Rect, CollisionType::Rect))
    //{
    //   GameEngine::GetInst().ChangeLevel("Level1_2");
    //}

    //if (true == KirbyCol_->CollisionCheck("DoorCol1_3", CollisionType::Rect, CollisionType::Rect))
    //{
    //   GameEngine::GetInst().ChangeLevel("Level1_3");
    //}

    //if (true == KirbyCol_->CollisionCheck("DoorCol1_4", CollisionType::Rect, CollisionType::Rect))
    //{
    //   GameEngine::GetInst().ChangeLevel("Level1_4");
    //}

    //if (true == KirbyCol_->CollisionCheck("Cannon", CollisionType::Rect, CollisionType::Rect))
    //{
    //   GameEngine::GetInst().ChangeLevel("Cannon");
    //}

    //if (true == KirbyCol_->CollisionCheck("DorrCol2_2", CollisionType::Rect, CollisionType::Rect))
    //{
    //   GameEngine::GetInst().ChangeLevel("Level2_2");
    //}

    //if (true == KirbyCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect) && Time_ >= 3)
    //{
    //   Time_ = 0;
    //   SetHP(GetHP() - 1);
    //}

    //if (GetState() == CharacterState::HOVER)
    //{
    //   // Attack colliison chk
    //   // AttackEffectRenderer_->SetImageScale();
    //   std::vector <GameEngineCollision*> ColResult;
    //   if (true == AttackEffectCol_->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
    //   {
    //      for (GameEngineCollision* Collision : ColResult)
    //      {
    //         GameEngineActor* Actor = Collision->GetActor(); // 충돌한 actor 가져오기
    //         Monster* Monster_ = dynamic_cast<Monster*>(Actor); // monster 맞는지 dynamic_cast로 chk
    //         if (nullptr != Monster_) // monster면
    //         {
    //            AttackEffectRenderer_->ChangeAnimation("Attack");
    //            float4 Position;
    //            Position.x = Monster_->GetPosition().x - 5;
    //            Position.y = Monster_->GetPosition().y;
    //            Monster_->SetPosition(Position);
    //         }
    //      }
    //   }
    //}
    //else
    //{
    //   AttackEffectRenderer_->SetScale(float4(0.0f, 0.0f));
    //}
}

void Player::UpdateAnimation()
{
    //CharacterState State = GetState();
    //CharacterState PrevState = GetPrevState();
    //float4 Direction = PrevPos_ - GetPosition();

    //if (State == CharacterState::HOVER)
    //{
    //   if (PrevState != CharacterState::HOVER) // hover가 아니였다가 hover가 됐을 때
    //   {
    //      Renderer_->ChangeAnimation("Inhale"); // 빨아들이기
    //   }
    //   else if (Renderer_->IsAnimationName("Inhale") && 
    //      Renderer_->IsEndAnimation())
    //   {
    //      Renderer_->ChangeAnimation("HoveringRight");
    //   }
    //}
    //else if (0 != AccGravity_)
    //{
    //   if (Direction.y < 0)
    //   {
    //      if (PrevState == CharacterState::HOVER && State != CharacterState::HOVER)
    //      {
    //         Renderer_->ChangeAnimation("AttackRight");
    //         //AttackEffectRenderer_->ChangeAnimation("Attack");// 떨어지는 동작 1
    //      }
    //      else if (true == Renderer_->IsAnimationName("AttackRight"))
    //      {
    //         if (true == Renderer_->IsEndAnimation())
    //         {
    //            //Renderer_->ChangeAnimation("HoverEndRight");
    //            Renderer_->ChangeAnimation("HoverEnd2Right");
    //         }
    //      }
    //      else
    //      {
    //         if (false == Renderer_->IsAnimationName("HoverEnd2Right"))
    //         {
    //            Renderer_->ChangeAnimation("JumpingRight");
    //         }
    //         else if (true == Renderer_->IsAnimationName("JumpingRight") &&
    //            true == Renderer_->IsEndAnimation())
    //         {
    //            //Renderer_->ChangeAnimation("HoverEndRight");
    //            Renderer_->ChangeAnimation("HoverEnd2Right");
    //         }
    //      }

    //   }
    //   else
    //   {
    //      if (GetState() != CharacterState::HOVER)
    //      {
    //         Renderer_->ChangeAnimation("JumpRight");
    //      }
    //   }
    //}
    //else if (State == CharacterState::WALK)
    //{
    //   if (PrevState != CharacterState::WALK)
    //   {
    //      Renderer_->ChangeAnimation("WalkRight");
    //   }
    //}
    //else if (State == CharacterState::RUN)
    //{
    //   if (PrevState != CharacterState::RUN)
    //   {
    //      Renderer_->ChangeAnimation("RunRight");
    //   }
    //}
    //else if (State == CharacterState::IDLE)
    //{
    //   Renderer_->ChangeAnimation("IdleRight");
    //}
    //
    //switch (State)B
    //{
    //case CharacterState::INHALE:
    //   Renderer_->ChangeAnimation("Inhale");
    //   if (true == Renderer_->IsEndAnimation())
    //   {
    //      // 돼지 되기
    //   }
    //   break;
    //case CharacterState::EAT:
    //   Renderer_->ChangeAnimation("HoverStartRight");
    //   if (true == Renderer_->IsEndAnimation())
    //   {
    //      Renderer_->ChangeAnimation("EatingRight");
    //      if (true == Renderer_->IsEndAnimation())
    //      {
    //         Renderer_->ChangeAnimation("IdleWzMonsterRight"); // 이제부터 걸을때도 볼 부풀린채로
    //         Renderer_->ChangeAnimation("AttackRight"); // 별쏘기
    //         //AttackEffectRenderer_->ChangeAnimation("AttackEffect");
    //      }
    //   }
    //   break;
    //}
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
    case KirbyState::Up:
        UpdateUp();
        break;
    case KirbyState::Down:
        UpdateDown();
        break;
    case KirbyState::HOVER:
        UpdateHover();
        break;
    case KirbyState::INHALE:
        UpdateInhale();
        break;
    case KirbyState::EAT:
        UpdateEat();
        break;
    case KirbyState::JUMP:
        UpdateJump();
    case KirbyState::SLIDE:
        UpdateSlide();
        break;
    default:
        break;
    }
}

bool Player::CanMoveUp()
{
    //return GameEngineInput::GetInst()->IsPress("MoveUp");
    return true;
}

bool Player::CanMoveDown()
{
    //return GameEngineInput::GetInst()->IsPress("MoveDown");
    return true;
}

bool Player::CanWalk()
{
    //return GameEngineInput::GetInst()->IsPress("MoveLeft")
    //   || GameEngineInput::GetInst()->IsPress("MoveRight");

    return true;
}

bool Player::CanRun()
{
    //return GameEngineInput::GetInst()->IsPress("RunLeft")
    //   || GameEngineInput::GetInst()->IsPress("RunRight");
    return true;
}

bool Player::CanJump() //"Jump", VK_LSHIFT
{
    //return GameEngineInput::GetInst()->IsUp("Jump");
    return true;
}

bool Player::CanFly()
{
    //return GameEngineInput::GetInst()->IsPress("Fly");
    return true;
}

bool Player::CanInhale()
{
    //return GameEngineInput::GetInst()->IsPress("Inhale");

    return true;
}

bool Player::CanHover()
{
    //return GameEngineInput::GetInst()->IsPress("Hover")
    //   && GetState() != CharacterState::RUN;

    return true;
}

bool Player::CanEat()
{
    //return GameEngineInput::GetInst()->IsPress("Eat")
    //   && GetState() != CharacterState::WALK
    //   && GetState() != CharacterState::RUN;

    return true;
}


void Player::Jump()
{
    //if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x, GetPosition().y - JumpHeight_))
    //{
    //    AccGravity_ = 0;
    //    JumpHeight_ = 0;
    //}
    //else
    //{
    //    SetMove(float4(0, -JumpHeight_));
    //}

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

void Player::Hover()
{
    SetState(KirbyState::HOVER);
    StateUpdate();
}

void Player::Eat()
{
    //SetState(CharacterState::EAT);ㅉ
}

void Player::Fly()
{
    //SetState(CharacterState::FLY);
}

void Player::Inhale()
{
    //SetState(CharacterState::INHALE);
}