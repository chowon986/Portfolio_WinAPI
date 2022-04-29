#include "Animal.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>

Animal::Animal()
	: Monster()
	, HP_(1)
	,AnimalCol_(nullptr)
	,AnimalRenderer_(nullptr)
	,Level_(nullptr)
	, ColMapImage_(nullptr)
{
	SetMonsterClass(MonsterClass::ANIMAL);
}

Animal::~Animal()
{
}

void Animal::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	//SetState(CharacterState::WALK);
	AnimalRenderer_ = CreateRenderer("monster0.bmp");
	GameEngineImage* AnimalImage = AnimalRenderer_->GetImage();
	AnimalImage->CutCount(10, 26);
	AnimalRenderer_->CreateAnimation("monster0.bmp", "AnimalIdle", 0, 5, 0.3f, true);
	AnimalRenderer_->ChangeAnimation("AnimalIdle");

	AnimalCol_ = CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
}

void Animal::Render()
{
}

void Animal::Update()
{
	//PrevPos_ = GetPosition();

	//float4 NewPos;
	//NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	//NewPos.y = GetPosition().y;
	//SetPosition(NewPos);

	//// 커비의 공격에만 체력 감소함 -> 커비 공격 구현 이후 변경 필요
	//if (true == AnimalCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	//{
	//	SetHP(GetHP() - 1);
	//	// AnimalRenderer_->ChangeAnimation("Animaldeee");
	//	// AnimalCol_->Death();
	//	// AnimalRenderer_->Death();
	//}

	//if (true == CheckMapCollision())
	//{
	//	SetPosition(PrevPos_);
	//}

}

bool Animal::CheckMapCollision()
{
	return true;
}
