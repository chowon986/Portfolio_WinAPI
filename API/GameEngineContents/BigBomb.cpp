#include "BigBomb.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


BigBomb::BigBomb()
	: Monster() // 부모 생성자 호출
	, HP_(1)
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

void BigBomb::Update()
{
	PrevPos_ = GetPosition();

	float4 NewPos;
	NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	NewPos.y = GetPosition().y;
	SetPosition(NewPos);

	// 커비의 공격에만 체력 감소함 -> 커비 공격 구현 이후 변경 필요
	if (true == BigBombCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		SetHP(GetHP() - 1);
		// BigBombRenderer_->ChangeAnimation("BigBombdeee");
		// BigBombCol_->Death();
		// BigBombRenderer_->Death();
	}

	if (true == CheckMapCollision())
	{
		SetPosition(PrevPos_);
	}

}

bool BigBomb::CheckMapCollision()
{
	if (nullptr != ColMapImage_)
	{
		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y))
		{
			return true;
		}

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y))
		{
			return true;
		}

		// 왼쪽, 오른쪽, 위쪽으로 이동 금지
		if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50) {
			return true;
		}
	}
}
