#include "BigWaddledee.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


BigWaddledee::BigWaddledee()
	: Monster()
	, HP_(1)
	, ColMapImage_(nullptr)
	,Level_(nullptr)
	,BigWaddledeeCol_(nullptr)
	,BigWaddledeeRenderer_(nullptr)
{
}

BigWaddledee::~BigWaddledee()
{
}

void BigWaddledee::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	//SetState(::WALK);
	BigWaddledeeRenderer_ = CreateRenderer("monster0.bmp");
	GameEngineImage* BigWaddledeeImage = BigWaddledeeRenderer_->GetImage();
	BigWaddledeeImage->CutCount(10, 26);
	BigWaddledeeRenderer_->CreateAnimation("monster0.bmp", "BigWaddledeeIdle", 0, 5, 0.3f, true);
	BigWaddledeeRenderer_->ChangeAnimation("BigWaddledeeIdle");

	BigWaddledeeCol_ = CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
}

void BigWaddledee::Render()
{
}

void BigWaddledee::Update()
{
	//PrevPos_ = GetPosition();

	//float4 NewPos;
	//NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	//NewPos.y = GetPosition().y;
	//SetPosition(NewPos);

	//// 커비의 공격에만 체력 감소함 -> 커비 공격 구현 이후 변경 필요
	//if (true == BigWaddledeeCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	//{
	//	SetHP(GetHP() - 1);
	//	// BigWaddledeeRenderer_->ChangeAnimation("BigWaddledeedeee");
	//	// BigWaddledeeCol_->Death();
	//	// BigWaddledeeRenderer_->Death();
	//}

	//if (true == CheckMapCollision())
	//{
	//	SetPosition(PrevPos_);
	//}

}

bool BigWaddledee::CheckMapCollision()
{
	return true;
}
