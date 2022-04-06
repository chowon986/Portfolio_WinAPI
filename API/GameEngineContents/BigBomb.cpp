#include "BigBomb.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


BigBomb::BigBomb()
	: HP_(1)
{
}

BigBomb::~BigBomb()
{
}

void BigBomb::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(CharacterState::WALK);
	BigBombRenderer_ = CreateRenderer("monster0.bmp");
	GameEngineImage* BigBombImage = BigBombRenderer_->GetImage();
	BigBombImage->CutCount(10, 26);
	BigBombRenderer_->CreateAnimation("monster0.bmp", "BigBombIdel", 0, 5, 0.3f, true);
	BigBombRenderer_->ChangeAnimation("BigBombIdel");

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

	// Ŀ���� ���ݿ��� ü�� ������ -> Ŀ�� ���� ���� ���� ���� �ʿ�
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

		// ����, ������, �������� �̵� ����
		if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50) {
			return true;
		}
	}
}
