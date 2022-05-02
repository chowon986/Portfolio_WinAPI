#include "BigWaddledee.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


BigWaddledee::BigWaddledee()
	: Monster()
{
}

BigWaddledee::~BigWaddledee()
{
}

void BigWaddledee::Start()
{
	Monster::Start();

	Renderer_ = CreateRenderer("monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 0, 4, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 259, 263, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 5, 5, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 264, 264, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 5, 6, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 264, 265, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);
	Renderer_->ChangeAnimation("WalkRight");
}

void BigWaddledee::Update()
{
	UpdateMove();
	Die();
}

void BigWaddledee::Render()
{
}