#include "BotUI.h"
#include "Player.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

BotUI::BotUI()
	: MinusHP_(0)
{
}

BotUI::~BotUI()
{
}


void BotUI::Start()
{
	//float4(49.0f, 550.0f)
	PlayerUI_ = CreateRenderer("CharacterStatus.bmp");
	GameEngineImage* StatusImage = PlayerUI_->GetImage();
	StatusImage->CutCount(3, 3);
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Default", 8, 8, 0.1f, false); // 16.0f, 570.0f
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Spark", 1, 1, 0.1f, false); // 49.0f, 570.0f
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Beam", 2, 2, 0.1f, false); // float4(16.0f, 570.0f)
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Fire", 0, 0, 0.1f, false); // float4(82.0f, 570.0f)
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Sword", 4, 4, 0.1f, false); // float4(49.0f, 570.0f)
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Ice", 6, 6, 0.1f, false); // float4(82.0f, 570.0f)
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Animal", 7, 7, 0.1f, false); // float4(48.0f, 570.0f))
	PlayerUI_->ChangeAnimation("Default");
	PlayerUI_->SetPivot(float4(16.0f, 570.0f));

	PlayerHP_ = CreateRenderer("HPUI.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235.0f, 545.0f));
	PlayerHPMinus_ = CreateRenderer("HPMinus.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235.0f, 552.0f));
	PlayerHPCount1_ = CreateRenderer("PlayerHPCount1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(155.0f, 520.0f));
	PlayerHPCount2_ = CreateRenderer("PlayerHPCount2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(190.0f, 520.0f));

	{
		HPNumberLeft_ = CreateRenderer("Number.bmp"); 
		GameEngineImage* HPCountLeftImage = HPNumberLeft_->GetImage();
		HPCountLeftImage->CutCount(10, 1);
		HPNumberLeft_->CreateAnimation("Number.bmp", "0", 0, 0, 0.1f, false);
		HPNumberLeft_->CreateAnimation("Number.bmp", "1", 1, 1, 0.1f, false);
		HPNumberLeft_->CreateAnimation("Number.bmp", "2", 2, 2, 0.1f, false);
		HPNumberLeft_->CreateAnimation("Number.bmp", "3", 3, 3, 0.1f, false);
		HPNumberLeft_->CreateAnimation("Number.bmp", "4", 4, 4, 0.1f, false);
		HPNumberLeft_->CreateAnimation("Number.bmp", "5", 5, 5, 0.1f, false);
		HPNumberLeft_->CreateAnimation("Number.bmp", "6", 6, 6, 0.1f, false);
		HPNumberLeft_->CreateAnimation("Number.bmp", "7", 7, 7, 0.1f, false);
		HPNumberLeft_->CreateAnimation("Number.bmp", "8", 8, 8, 0.1f, false);
		HPNumberLeft_->CreateAnimation("Number.bmp", "9", 9, 9, 0.1f, false);
		HPNumberLeft_->ChangeAnimation("0");
		HPNumberLeft_->SetPivot(float4(218.0f, 530.0f));

		HPNumberRight_ = CreateRenderer("Number.bmp"); //float4(315.0f, 518.0f)
		GameEngineImage* HPCountRightImage = HPNumberRight_->GetImage();
		HPCountRightImage->CutCount(10, 1);
		HPNumberRight_->CreateAnimation("Number.bmp", "0", 0, 0, 0.1f, false);
		HPNumberRight_->CreateAnimation("Number.bmp", "1", 1, 1, 0.1f, false);
		HPNumberRight_->CreateAnimation("Number.bmp", "2", 2, 2, 0.1f, false);
		HPNumberRight_->CreateAnimation("Number.bmp", "3", 3, 3, 0.1f, false);
		HPNumberRight_->CreateAnimation("Number.bmp", "4", 4, 4, 0.1f, false);
		HPNumberRight_->CreateAnimation("Number.bmp", "5", 5, 5, 0.1f, false);
		HPNumberRight_->CreateAnimation("Number.bmp", "6", 6, 6, 0.1f, false);
		HPNumberRight_->CreateAnimation("Number.bmp", "7", 7, 7, 0.1f, false);
		HPNumberRight_->CreateAnimation("Number.bmp", "8", 8, 8, 0.1f, false);
		HPNumberRight_->CreateAnimation("Number.bmp", "9", 9, 9, 0.1f, false);
		HPNumberRight_->ChangeAnimation("2");
		HPNumberRight_->SetPivot(float4(237.0f, 530.0f));
	}

	PlayerUI_->CameraEffectOff();
	PlayerHP_->CameraEffectOff();
	PlayerHPMinus_->CameraEffectOff();
	PlayerHPCount1_->CameraEffectOff();
	PlayerHPCount2_->CameraEffectOff();
	HPNumberLeft_->CameraEffectOff();
	HPNumberRight_->CameraEffectOff();
	
	// 체력바는 총 9칸
	MinusHP_ = PlayerHPMinus_->GetScale().x/9;
}

void BotUI::Update()
{
	//switch ()
	//{
	//case KirbyClass::DEFAULT:
	//case KirbyClass::PIG:
	//	PlayerUI_->ChangeAnimation("Default");
	//	 PlayerUI_->SetPivot(float4(.0f,.0f));
	//	break;
	//case KirbyClass::ANIMAL:
	//	PlayerUI_->ChangeAnimation("Animal");
	//	PlayerUI_->SetPivot(float4(.0f,.0f));
	//	break;
	//case KirbyClass::FIRE:
	//	PlayerUI_->ChangeAnimation("Fire");
	//	PlayerUI_->SetPivot(float4(.0f,.0f));
	//	break;
	//case KirbyClass::ICE:
	//	PlayerUI_->ChangeAnimation("Ice");
	//	PlayerUI_->SetPivot(float4(.0f,.0f));
	//	break;
	//case KirbyClass::SPARK:
	//	PlayerUI_->ChangeAnimation("Spark");
	//	PlayerUI_->SetPivot(float4(.0f,.0f));
	//	break;
	//case KirbyClass::SWORD:
	//	PlayerUI_->ChangeAnimation("Sword");
	//	PlayerUI_->SetPivot(float4(.0f,.0f));
	//	break;
	//}
	
	// 플레이어가 공격을 받으면
	// PlayerHPMinus_->GetScale() - MinusHP_;
}

void BotUI::Render()
{
}
