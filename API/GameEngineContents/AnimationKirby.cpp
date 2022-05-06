#include "AnimationKirby.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineLevel.h>
#include "GameEngineBase/GameEngineSound.h"

AnimationKirby::AnimationKirby()
{
}

AnimationKirby::~AnimationKirby()
{
}


void AnimationKirby::SetAnimationKirbyClass(AnimationKirbyClass _Class)
{
    Class_ = _Class;
    ClassUpdate();
}

AnimationKirbyClass AnimationKirby::GetClass()
{
    return Class_;
}

GameEngineRenderer* AnimationKirby::GetRenderer()
{
    if (GetClass() == AnimationKirbyClass::DANCE)
    {
        return DanceRenderer_;
    }

    else
    {
        return StarRenderer_;
    }
}

void AnimationKirby::ClassUpdate()
{
    switch (Class_)
    {
    case AnimationKirbyClass::DANCE:
        DanceRenderer_->SetAlpha(255);
        StarRenderer_->SetAlpha(0);
        break;
    case AnimationKirbyClass::STAR:
        DanceRenderer_->SetAlpha(0);
        StarRenderer_->SetAlpha(255);
        break;

    default:
        break;
    }
}

void AnimationKirby::Start()
{
    {
        // Dance
        DanceRenderer_ = CreateRenderer("Test2.bmp");
        DanceImage_ = DanceRenderer_->GetImage();
        DanceImage_->CutCount(10, 6);
        DanceRenderer_->CreateAnimation("Test2.bmp", "DanceStart", 0, 0, 1.0f, false);
        DanceRenderer_->CreateAnimation("Test2.bmp", "Dance", 0, 56, 0.05f, false);
    }

    {
        //Star
        StarRenderer_ = CreateRenderer("Star.bmp");
        StarImage_ = StarRenderer_->GetImage();
        StarImage_->CutCount(2, 1);
        StarRenderer_->CreateAnimation("Star.bmp", "Move", 0, 1, 0.1f, true);
        StarCol_ = CreateCollision("Animation", float4(70.0f, 70.0f), float4(0.0f, 0.0f));
    }

    if (GetLevel()->GetNameCopy() == "DanceStage")
    {
        SetAnimationKirbyClass(AnimationKirbyClass::DANCE);
        DanceRenderer_->ChangeAnimation("DanceStart");
    }

    if (GetLevel()->GetNameCopy() == "Level1")
    {
        SetAnimationKirbyClass(AnimationKirbyClass::STAR);
        StarRenderer_->ChangeAnimation("Move");
    }

    StartPos_ = GetPosition();
}

void AnimationKirby::DelayUpdate()
{
    Time_ += GameEngineTime::GetDeltaTime();
    if (GetClass() == AnimationKirbyClass::DANCE)
	{
		if (DanceRenderer_->IsAnimationName("DanceStart") && DanceRenderer_->IsEndAnimation())
		{
            Time_ = 0.0f;
			DanceRenderer_->ChangeAnimation("Dance");
			GameEngineSound::SoundPlayOneShot("Clear2.mp3");
		}
	}

    if (DanceRenderer_->IsAnimationName("Dance") && DanceRenderer_->IsEndAnimation())
    {
        if (Time_ > 5.0f)
        {
            GameEngine::GetInst().ChangeLevel("WorldMap");
        }
    }

    //if (GetClass() == AnimationKirbyClass::STAR && StarRenderer_->IsAnimationName("Move"))
    //{
    //    float4 MoveDir = StartPos_ - GetPosition();
    //    Speed_ = 100.0f;

    //    if (GetPosition().ix() < 450 && GetPosition().iy() < 100)
    //    {
    //        Dir_ = float4::RIGHTDOWN;
    //    }

    //    else if (GetPosition().ix() >= 450 && GetPosition().iy() < 300)
    //    {
    //        Dir_ = float4::DOWN;
    //    }
    //    
    //    else if (210 > GetPosition().ix() > 200 && GetPosition().iy() > 110)
    //    {
    //        Dir_ = float4::ZERO;
    //    }

    //    else if(GetPosition().ix()< 200)
    //    {
    //        if (Dir_.x != 1.0f && GetPosition().iy() > 120)
    //        {
    //            Dir_ = float4::UP;
    //        }
    //        else if (Dir_.y = -1.0f && GetPosition().iy() > 110)
    //        {
    //            Dir_ = float4::RIGHT;
    //        }
    //        else
    //        {
    //            return;
    //        }
    //    }

    //    else if (200 < GetPosition().ix() <= 450 && 300 <= GetPosition().iy())
    //    {
    //        Dir_ = float4::LEFT;
    //    }

    //    //else
    //    //{
    //    //    Dir_ = float4::ZERO;
    //    //}

    //    SetMove(Dir_ * GameEngineTime::GetDeltaTime() * Speed_);
    //}
}

void AnimationKirby::Render()
{
}

void AnimationKirby::CheckCollision()
{
}

void AnimationKirby::UpdateDance()
{
}

void AnimationKirby::UpdateStar()
{
}
