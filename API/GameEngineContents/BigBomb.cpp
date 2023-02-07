#include "BigBomb.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


BigBomb::BigBomb()
	: Monster() // �θ� ������ ȣ��
	, HP_(1)
	,ColMapImage_(nullptr)
	,Level_(nullptr)
	,BigBombCol_(nullptr)
	,BigBombRenderer_(nullptr)
{
	SetMonsterClass(MonsterClass::BOSS);
}

BigBomb::~BigBomb()
{
}

void BigBomb::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	//SetState(CharacterState::WALK);
	BigBombRenderer_ = CreateRenderer("monster0.bmp");
	GameEngineImage* BigBombImage = BigBombRenderer_->GetImage();
	BigBombImage->CutCount(10, 26);
	BigBombRenderer_->CreateAnimation("monster0.bmp", "BigBombIdle", 0, 5, 0.3f, true);
	BigBombRenderer_->ChangeAnimation("BigBombIdle");

	BigBombCol_ = CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
}

void BigBomb::Render()
{
}

void BigBomb::DelayUpdate()
{
	//PrevPos_ = GetPosition();

	//float4 NewPos;
	//NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	//NewPos.y = GetPosition().y;
	//SetPosition(NewPos);

	//// Ŀ���� ���ݿ��� ü�� ������ -> Ŀ�� ���� ���� ���� ���� �ʿ�
	//if (true == BigBombCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	//{
	//	SetHP(GetHP() - 1);
	//	// BigBombRenderer_->ChangeAnimation("BigBombdeee");
	//	// BigBombCol_->Death();
	//	// BigBombRenderer_->Death();
	//}

	//if (true == CheckMapCollision())
	//{
	//	SetPosition(PrevPos_);
	//}

}

bool BigBomb::CheckMapCollision()
{
	return true;
}
