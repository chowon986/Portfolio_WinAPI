#include "StarMonster.h"
#include "Player.h"
#include "Monster.h"
#include "IceAttackEffect.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>

StarMonster::StarMonster()
	: Monster()
{
}

StarMonster::~StarMonster()
{
}

void StarMonster::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetHP(1);
	Renderer_ = CreateRenderer("AttackEffect.bmp");
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(8, 2);
	Renderer_->CreateAnimation("AttackEffect.bmp", "Star", 0, 3, 0.3f, true);
	Renderer_->ChangeAnimation("Star");
	Collision_ = CreateCollision("StarMonster", float4(50.0f, 50.0f), float4(0.0f, -25.0f));
}

void StarMonster::DelayUpdate()
{

}

void StarMonster::Render()
{
}