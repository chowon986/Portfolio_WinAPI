#include "MonBotUI.h"
#include "Monster.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <string>

MonBotUI::MonBotUI()
	: MinusHP_(0)
	, Time_(0.0f)
	, MaxHPCheck_(false)
{
}

MonBotUI::~MonBotUI()
{
}


void MonBotUI::Start()
{

	MonsterHP_ = CreateRenderer("MonHPUI.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(600.0f, 545.0f));

	HP_ = CreateRenderer("MonHP2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(601.0f, 546.0f));
	GameEngineImage* HPImage = HP_->GetImage();
	HPImage->CutCount(1, 2);
	HP_->CreateAnimation("MonHP2.bmp", "HP2", 0, 1,0.1f, false);
	HP_->CreateAnimation("MonHP2.bmp", "HP1", 1, 1,0.1f, false);
	HP_->ChangeAnimation("HP2");

	BossHP_ = CreateRenderer("BossHP.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(601.0f, 546.0f));
	GameEngineImage* BossHPImage = BossHP_->GetImage();
	BossHPImage->CutCount(1, 13);
	BossHP_->CreateAnimation("BossHP.bmp", "HP13", 0, 0, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP12", 0, 1, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP11", 1, 2, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP10", 2, 3, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP9", 3, 4, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP8", 4, 5, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP7", 5, 6, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP6", 6, 7, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP5", 7, 8, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP4", 8, 9, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP3", 9, 10, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP2", 10, 11, 0.1f, false);
	BossHP_->CreateAnimation("BossHP.bmp", "HP1", 11, 12, 0.1f, false);
	BossHP_->ChangeAnimation("HP13");

	MonsterHP_->CameraEffectOff();
	HP_->CameraEffectOff();
	BossHP_->CameraEffectOff();
}

void MonBotUI::Update()
{
	if (MaxHPCheck_ == false)
	{
		MaxHP_ = Monster_->GetHP();
		MaxHPCheck_ = true;
	}

	Time_ = GameEngineTime::GetDeltaTime();
	if (Monster_ == nullptr)
	{
		return;
	}

	int HP = Monster_->GetHP();

	if (MaxHP_ == 2)
	{
		BossHP_->SetAlpha(0);
		switch (HP)
		{
		case 0:
			HP_->SetAlpha(0);
			break;
		case 1:
			HP_->ChangeAnimation("HP1");
			HP_->SetAlpha(255);
			break;
		case 2:
			HP_->ChangeAnimation("HP2");
			HP_->SetAlpha(255);
			break;
		default:
			HP_->SetAlpha(0);
			break;
		}
	}

	if (MaxHP_ == 13)
	{
		HP_->SetAlpha(0);
		switch (HP)
		{
		case 0:
			BossHP_->SetAlpha(0);
			break;
		case 1:
			BossHP_->ChangeAnimation("HP1");
			BossHP_->SetAlpha(255);
			break;
		case 2:
			BossHP_->ChangeAnimation("HP2");
			BossHP_->SetAlpha(255);
			break;
		case 3:
			BossHP_->ChangeAnimation("HP3");
			BossHP_->SetAlpha(255);
			break;
		case 4:
			BossHP_->ChangeAnimation("HP4");
			BossHP_->SetAlpha(255);
			break;
		case 5:
			BossHP_->ChangeAnimation("HP5");
			BossHP_->SetAlpha(255);
			break;
		case 6:
			BossHP_->ChangeAnimation("HP6");
			BossHP_->SetAlpha(255);
			break;
		case 7:
			BossHP_->ChangeAnimation("HP7");
			BossHP_->SetAlpha(255);
			break;
		case 8:
			BossHP_->ChangeAnimation("HP8");
			BossHP_->SetAlpha(255);
			break;
		case 9:
			BossHP_->ChangeAnimation("HP9");
			BossHP_->SetAlpha(255);
			break;
		case 10:
			BossHP_->ChangeAnimation("HP10");
			BossHP_->SetAlpha(255);
			break;
		case 11:
			BossHP_->ChangeAnimation("HP11");
			BossHP_->SetAlpha(255);
			break;
		case 12:
			BossHP_->ChangeAnimation("HP12");
			BossHP_->SetAlpha(255);
			break;
		case 13:
			BossHP_->ChangeAnimation("HP13");
			BossHP_->SetAlpha(255);
			break;
		default:			
			BossHP_->SetAlpha(0);
			break;
		}
	}

}


void MonBotUI::Render()
{
}
