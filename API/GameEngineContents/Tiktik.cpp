#include "Tiktik.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Tiktik::Tiktik()
	: Monster()
{
}

Tiktik::~Tiktik()
{
}

void Tiktik::Start()
{
	Monster::Start();

	Renderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("monster1.bmp", "WalkRight", 137, 145, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 396, 404, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 146, 146, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 405, 405, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 146, 147, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 405, 406, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);
	Renderer_->ChangeAnimation("WalkRight");
}

void Tiktik::DelayUpdate()
{
	UpdateMove();
	Die();
}

void Tiktik::Render()
{
}