#include "Brontobert.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"


Brontobert::Brontobert()
	: Monster()
	, UpDownDir_(float4::DOWN)
{
}

Brontobert::~Brontobert()
{
}

void Brontobert::Start()
{
	Monster::Start();

	Renderer_ = CreateRenderer("Monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 33, 37, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 292, 296, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 38, 38, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 297, 297, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 38, 39, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 297, 298, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);
	Renderer_->ChangeAnimation("WalkRight");

}

void Brontobert::Render()
{
}

void Brontobert::Update()
{
	UpdateMove();
	Die();
}

void Brontobert::Walk()
{ 
	if (GetPosition().y > 280)
	{
		UpDownDir_ = float4::UP;
	}

	if (GetPosition().y < 200)
	{
		UpDownDir_ = float4::DOWN;
	}

	if (GetPosition().x < 2980)
	{
		Dir_ = float4::RIGHT;
	}

	if (GetPosition().x > 3380)
	{
		Dir_ = float4::LEFT;
	}

	if (true != Renderer_->IsAnimationName("Ice"))
	{
		if (Dir_.x == 1)
		{
			Renderer_->ChangeAnimation("WalkRight");
		}
		else if (Dir_.x == -1)
		{
			Renderer_->ChangeAnimation("WalkLeft");
		}
	}
	SetMove((Dir_ + UpDownDir_)* GameEngineTime::GetDeltaTime() * Speed_);
}
