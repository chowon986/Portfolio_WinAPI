#include "Dedede.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>

Dedede::Dedede()
	: Monster()
{
	SetMonsterClass(MonsterClass::BOSS);
}

Dedede::~Dedede()
{
}

void Dedede::Start()
{
	DededeRenderer_ = CreateRenderer("KingDedede.bmp");
	DededeImage_ = DededeRenderer_->GetImage();
	DededeImage_->CutCount(8, 8);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "IdleRight",0,3,0.2f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "IdleLeft",32,35,0.2f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "WalkRight",4,7,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "WalkLeft",36,39,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "JumpRight",8,10,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "JumpLeft",40,52,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "AttackRight",11,20,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "AttackLeft",43,62,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "YellRight",21,24,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "YellLeft",53,56,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "FlyRight",25,27,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "FlyLeft",57,59,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "DieRight",29,31,0.1f,true);
	DededeRenderer_->CreateAnimation("KingDedede.bmp", "DieLeft",61,63,0.1f,true);
	DededeRenderer_->ChangeAnimation("IdleLeft");
}

void Dedede::Render()
{

}

void Dedede::Update()
{
}

//bool Dedede::CheckMapCollision()
//{
//}
