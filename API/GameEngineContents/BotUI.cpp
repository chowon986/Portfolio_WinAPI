#include "BotUI.h"
#include "Player.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <string>

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
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Fire", 0, 0, 0.1f, false); // float4(82.0f, 570.0f)
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Sword", 4, 4, 0.1f, false); // float4(49.0f, 570.0f)
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Ice", 6, 6, 0.1f, false); // float4(82.0f, 570.0f)
	PlayerUI_->CreateAnimation("CharacterStatus.bmp", "Animal", 7, 7, 0.1f, false); 
	PlayerUI_->ChangeAnimation("Default");
	PlayerUI_->SetPivot(float4(16.0f, 570.0f));

	PlayerHP_ = CreateRenderer("HPUI.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235.0f, 545.0f));
	PlayerHPCount1_ = CreateRenderer("PlayerHPCount1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(155.0f, 520.0f));
	PlayerHPCount2_ = CreateRenderer("PlayerHPCount2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(190.0f, 520.0f));

	{
		HP10_ = CreateRenderer("HP10.bmp"); 
		HP9_ = CreateRenderer("HP9.bmp");
		HP8_ = CreateRenderer("HP8.bmp");
		HP7_ = CreateRenderer("HP7.bmp");
		HP6_ = CreateRenderer("HP6.bmp");
		HP5_ = CreateRenderer("HP5.bmp");
		HP4_ = CreateRenderer("HP4.bmp");
		HP3_ = CreateRenderer("HP3.bmp");
		HP2_ = CreateRenderer("HP2.bmp");
		HP1_ = CreateRenderer("HP1.bmp");
	}

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
	}

	{
		HPNumberLeft_->ChangeAnimation("0");
		HPNumberLeft_->SetPivot(float4(218.0f, 530.0f));
		HPNumberRight_->ChangeAnimation("2");
		HPNumberRight_->SetPivot(float4(237.0f, 530.0f));
	}

	PlayerUI_->CameraEffectOff();
	PlayerHP_->CameraEffectOff();
	HP10_->CameraEffectOff();
	HP9_->CameraEffectOff();
	HP8_->CameraEffectOff();
	HP7_->CameraEffectOff();
	HP6_->CameraEffectOff();
	HP5_->CameraEffectOff();
	HP4_->CameraEffectOff();
	HP3_->CameraEffectOff();
	HP2_->CameraEffectOff();
	HP1_->CameraEffectOff();
	PlayerHPCount1_->CameraEffectOff();
	PlayerHPCount2_->CameraEffectOff();
	HPNumberLeft_->CameraEffectOff();
	HPNumberRight_->CameraEffectOff();
}

void BotUI::Update()
{
	// kirby의 class를 가져오고싶은데 nullptr이 될 경우
	// botui와 kirby가 같이 있는 곳에서 설정이 필요하고,
	// botui에서 kirby 정보가 필요하니까 set함수를 만든다.
	// 지금은 level에서 같이 있으므로 level에서 set 함수를 설정하고
	// 설정된 player를 멤버변수로 받아서 nullptr이 아니게 만든다.
	// 그 후 사용
	if (Player_ == nullptr)
	{
		return;
	}

	KirbyClass Class =  Player_->GetKirbyClass();

	switch (Class)
	{
	case KirbyClass::DEFAULT:
	case KirbyClass::PIG:
		PlayerUI_->ChangeAnimation("Default");
		 PlayerUI_->SetPivot(float4(16.0f, 570.0f));
		break;
	case KirbyClass::ANIMAL:
		PlayerUI_->ChangeAnimation("Animal");
		PlayerUI_->SetPivot(float4(48.0f, 570.0f));
		break;
	case KirbyClass::FIRE:
		PlayerUI_->ChangeAnimation("Fire");
		PlayerUI_->SetPivot(float4(82.0f, 570.0f));
		break;
	case KirbyClass::ICE:
		PlayerUI_->ChangeAnimation("Ice");
		PlayerUI_->SetPivot(float4(82.0f, 570.0f));
		break;
	case KirbyClass::SPARK:
		PlayerUI_->ChangeAnimation("Spark");
		PlayerUI_->SetPivot(float4(49.0f, 570.0f));
		break;
	case KirbyClass::SWORD:
		PlayerUI_->ChangeAnimation("Sword");
		PlayerUI_->SetPivot(float4(49.0f, 570.0f));
		break; 
	}

	int PlayerHPCount = Player_->GetHPCount();
	std::string Num1 = std::to_string(PlayerHPCount);
	std::string Num2 = std::to_string(PlayerHPCount-10);

	switch (PlayerHPCount)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		HPNumberLeft_->ChangeAnimation("0");
		HPNumberLeft_->SetPivot(float4(218.0f, 530.0f));
		HPNumberRight_->ChangeAnimation(Num1);
		HPNumberRight_->SetPivot(float4(237.0f, 530.0f));
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		HPNumberLeft_->ChangeAnimation("1");
		HPNumberLeft_->SetPivot(float4(218.0f, 530.0f));
		HPNumberRight_->ChangeAnimation(Num2);
		HPNumberRight_->SetPivot(float4(237.0f, 530.0f));
		break;
	}

	
	int PlayerHP = Player_->GetHP();

	switch (PlayerHP)
	{
	case 0:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(0);
		break;
	case 1:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(255);
		HP1_->SetPivot(float4(136.0f, 552.0f));
		break;
	case 2:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(255);
		HP1_->SetAlpha(0);
		HP2_->SetPivot(float4(147.0f, 552.0f));
		break;
	case 3:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(255);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(0);
		HP3_->SetPivot(float4(158.0f, 552.0f));
		break;
	case 4:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(255);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(0);
		HP4_->SetPivot(float4(169.0f, 552.0f));
		break;
	case 5:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(255);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(0);
		HP5_->SetPivot(float4(180.0f, 552.0f));
		break;
	case 6:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(255);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(0);
		HP6_->SetPivot(float4(191.0f, 552.0f));
		break;
	case 7:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(255);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(0);
		HP7_->SetPivot(float4(202.0f, 552.0f));
		break;
	case 8:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(255);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(0);
		HP8_->SetPivot(float4(213.0f, 552.0f));
		break;
	case 9:
		HP10_->SetAlpha(0);
		HP9_->SetAlpha(255);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(0);
		HP9_->SetPivot(float4(224.0f, 552.0f));
		break;
	case 10:
		HP10_->SetAlpha(255);
		HP9_->SetAlpha(0);
		HP8_->SetAlpha(0);
		HP7_->SetAlpha(0);
		HP6_->SetAlpha(0);
		HP5_->SetAlpha(0);
		HP4_->SetAlpha(0);
		HP3_->SetAlpha(0);
		HP2_->SetAlpha(0);
		HP1_->SetAlpha(0);
		HP10_->SetPivot(float4(235.0f, 552.0f));
		break;
	}
	
}


void BotUI::Render()
{
}
