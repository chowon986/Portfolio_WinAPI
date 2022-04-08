#include "BigWaddledee.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


BigWaddledee::BigWaddledee()
	: HP_(1)
{
}

BigWaddledee::~BigWaddledee()
{
}

void BigWaddledee::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	SetState(CharacterState::WALK);
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
	PrevPos_ = GetPosition();

	float4 NewPos;
	NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	NewPos.y = GetPosition().y;
	SetPosition(NewPos);

	// Ŀ���� ���ݿ��� ü�� ������ -> Ŀ�� ���� ���� ���� ���� �ʿ�
	if (true == BigWaddledeeCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		SetHP(GetHP() - 1);
		// BigWaddledeeRenderer_->ChangeAnimation("BigWaddledeedeee");
		// BigWaddledeeCol_->Death();
		// BigWaddledeeRenderer_->Death();
	}

	if (true == CheckMapCollision())
	{
		SetPosition(PrevPos_);
	}

}

bool BigWaddledee::CheckMapCollision()
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
