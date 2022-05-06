#include "Waddledee.h"
#include "Player.h"
#include "Monster.h"
#include "IceAttackEffect.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <vector>

Waddledee::Waddledee()
	: Monster()
{
}

Waddledee::~Waddledee()
{
}

void Waddledee::Start()
{
	Monster::Start();
	Renderer_ = CreateRenderer("Monster1.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 52);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkRight", 7, 14, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "WalkLeft", 266, 273, 0.3f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionLeft", 15, 15, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "CollisionRight", 274, 274, 0.5f, false);
	Renderer_->CreateAnimation("Monster1.bmp", "DieLeft", 15, 16, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "DieRight", 274, 275, 0.5f, true);
	Renderer_->CreateAnimation("Monster1.bmp", "Ice", 519, 519, 0.5f, false);
	Renderer_->ChangeAnimation("WalkRight");
}

void Waddledee::DelayUpdate()
{
	UpdateMove();
	Die();
}

void Waddledee::Render()
{
}