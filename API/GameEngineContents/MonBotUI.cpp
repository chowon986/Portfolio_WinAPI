#include "MonBotUI.h"
#include "Monster.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <string>

MonBotUI::MonBotUI()
	: MinusHP_(0)
{
}

MonBotUI::~MonBotUI()
{
}


void MonBotUI::Start()
{
	//MonsterHP_ = CreateRenderer("HPUI.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235.0f, 545.0f));
	//MonsterHPCount1_ = CreateRenderer("MonsterHPCount1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(155.0f, 520.0f));
	//MonsterHPCount2_ = CreateRenderer("MonsterHPCount2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(190.0f, 520.0f));

	//{
	//	BossHP10_ = CreateRenderer("HP10.bmp");
	//	BossHP9_ = CreateRenderer("HP9.bmp");
	//	BossHP8_ = CreateRenderer("HP8.bmp");
	//	BossHP7_ = CreateRenderer("HP7.bmp");
	//	BossHP6_ = CreateRenderer("HP6.bmp");
	//	BossHP5_ = CreateRenderer("HP5.bmp");
	//	BossHP4_ = CreateRenderer("HP4.bmp");
	//	BossHP3_ = CreateRenderer("HP3.bmp");
	//	BossHP2_ = CreateRenderer("HP2.bmp");
	//	BossHP1_ = CreateRenderer("HP1.bmp");

	//	HP0_ = CreateRenderer("HP3.bmp");
	//	HP1_ = CreateRenderer("HP2.bmp");
	//	HP2_ = CreateRenderer("HP1.bmp");

	//}

	//{
	//	HPNumberLeft_ = CreateRenderer("Number.bmp");
	//	GameEngineImage* HPCountLeftImage = HPNumberLeft_->GetImage();
	//	HPCountLeftImage->CutCount(10, 1);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "0", 0, 0, 0.1f, false);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "1", 1, 1, 0.1f, false);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "2", 2, 2, 0.1f, false);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "3", 3, 3, 0.1f, false);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "4", 4, 4, 0.1f, false);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "5", 5, 5, 0.1f, false);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "6", 6, 6, 0.1f, false);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "7", 7, 7, 0.1f, false);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "8", 8, 8, 0.1f, false);
	//	HPNumberLeft_->CreateAnimation("Number.bmp", "9", 9, 9, 0.1f, false);

	//	HPNumberRight_ = CreateRenderer("Number.bmp"); //float4(315.0f, 518.0f)
	//	GameEngineImage* HPCountRightImage = HPNumberRight_->GetImage();
	//	HPCountRightImage->CutCount(10, 1);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "0", 0, 0, 0.1f, false);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "1", 1, 1, 0.1f, false);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "2", 2, 2, 0.1f, false);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "3", 3, 3, 0.1f, false);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "4", 4, 4, 0.1f, false);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "5", 5, 5, 0.1f, false);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "6", 6, 6, 0.1f, false);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "7", 7, 7, 0.1f, false);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "8", 8, 8, 0.1f, false);
	//	HPNumberRight_->CreateAnimation("Number.bmp", "9", 9, 9, 0.1f, false);
	//}

	//{
	//	HPNumberLeft_->ChangeAnimation("0");
	//	HPNumberLeft_->SetPivot(float4(218.0f, 530.0f));
	//	HPNumberRight_->ChangeAnimation("2");
	//	HPNumberRight_->SetPivot(float4(237.0f, 530.0f));
	//}

	//MonsterUI_->CameraEffectOff();
	//MonsterHP_->CameraEffectOff();
	//HP10_->CameraEffectOff();
	//HP9_->CameraEffectOff();
	//HP8_->CameraEffectOff();
	//HP7_->CameraEffectOff();
	//HP6_->CameraEffectOff();
	//HP5_->CameraEffectOff();
	//HP4_->CameraEffectOff();
	//HP3_->CameraEffectOff();
	//HP2_->CameraEffectOff();
	//HP1_->CameraEffectOff();
	//MonsterHPCount1_->CameraEffectOff();
	//MonsterHPCount2_->CameraEffectOff();
	//HPNumberLeft_->CameraEffectOff();
	//HPNumberRight_->CameraEffectOff();
}

void MonBotUI::Update()
{
	// Monster의 class를 가져오고싶은데 nullptr이 될 경우
	// MonBotUI와 Monster가 같이 있는 곳에서 설정이 필요하고,
	// MonBotUI에서 Monster 정보가 필요하니까 set함수를 만든다.
	// 지금은 level에서 같이 있으므로 level에서 set 함수를 설정하고
	// 설정된 Monster를 멤버변수로 받아서 nullptr이 아니게 만든다.
	// 그 후 사용
	//if (Monster_ == nullptr)
	//{
	//	return;
	//}

	//MonsterClass Class = Monster_->GetMonsterClass();

	//switch (Class)
	//{
	//case MonsterClass::DEFAULT:
	//case MonsterClass::PIG:
	//	MonsterUI_->ChangeAnimation("Default");
	//	MonsterUI_->SetPivot(float4(16.0f, 570.0f));
	//	break;
	//case MonsterClass::ANIMAL:
	//	MonsterUI_->ChangeAnimation("Animal");
	//	MonsterUI_->SetPivot(float4(48.0f, 570.0f));
	//	break;
	//case MonsterClass::FIRE:
	//	MonsterUI_->ChangeAnimation("Fire");
	//	MonsterUI_->SetPivot(float4(82.0f, 570.0f));
	//	break;
	//case MonsterClass::ICE:
	//	MonsterUI_->ChangeAnimation("Ice");
	//	MonsterUI_->SetPivot(float4(82.0f, 570.0f));
	//	break;
	//case MonsterClass::SPARK:
	//	MonsterUI_->ChangeAnimation("Spark");
	//	MonsterUI_->SetPivot(float4(49.0f, 570.0f));
	//	break;
	//case MonsterClass::SWORD:
	//	MonsterUI_->ChangeAnimation("Sword");
	//	MonsterUI_->SetPivot(float4(49.0f, 570.0f));
	//	break;
	//}


	//int MonsterHP = Monster_->GetHP();

	//switch (MonsterHP)
	//{
	//case 0:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(0);
	//	break;
	//case 1:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(255);
	//	HP1_->SetPivot(float4(136.0f, 552.0f));
	//	break;
	//case 2:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(255);
	//	HP1_->SetAlpha(0);
	//	HP2_->SetPivot(float4(147.0f, 552.0f));
	//	break;
	//case 3:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(255);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(0);
	//	HP3_->SetPivot(float4(158.0f, 552.0f));
	//	break;
	//case 4:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(255);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(0);
	//	HP4_->SetPivot(float4(169.0f, 552.0f));
	//	break;
	//case 5:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(255);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(0);
	//	HP5_->SetPivot(float4(180.0f, 552.0f));
	//	break;
	//case 6:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(255);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(0);
	//	HP6_->SetPivot(float4(191.0f, 552.0f));
	//	break;
	//case 7:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(255);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(0);
	//	HP7_->SetPivot(float4(202.0f, 552.0f));
	//	break;
	//case 8:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(255);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(0);
	//	HP8_->SetPivot(float4(213.0f, 552.0f));
	//	break;
	//case 9:
	//	HP10_->SetAlpha(0);
	//	HP9_->SetAlpha(255);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(0);
	//	HP9_->SetPivot(float4(224.0f, 552.0f));
	//	break;
	//case 10:
	//	HP10_->SetAlpha(255);
	//	HP9_->SetAlpha(0);
	//	HP8_->SetAlpha(0);
	//	HP7_->SetAlpha(0);
	//	HP6_->SetAlpha(0);
	//	HP5_->SetAlpha(0);
	//	HP4_->SetAlpha(0);
	//	HP3_->SetAlpha(0);
	//	HP2_->SetAlpha(0);
	//	HP1_->SetAlpha(0);
	//	HP10_->SetPivot(float4(235.0f, 552.0f));
	//	break;
	//}

}


void MonBotUI::Render()
{
}
