#include "BotUI.h"
#include "Player.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

BotUI::BotUI()
{
}

BotUI::~BotUI()
{
}


void BotUI::Start()
{
}

void BotUI::Render()
{

	GameEngineRenderer* PlayerUI_ = CreateRenderer("NormalStatus.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER,float4(49.0f,557.0f));
	GameEngineRenderer* PlayerHP_ = CreateRenderer("HPUI.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235.0f, 555.0f));
	PlayerHPMinus_ = CreateRenderer("HPMinus.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235.0f, 562.0f));
	GameEngineRenderer* PlayerHPCount1_ = CreateRenderer("PlayerHPCount1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(155.0f, 525.0f));
	GameEngineRenderer* PlayerHPCount2_ = CreateRenderer("PlayerHPCount2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(190.0f, 527.0f));
	//GameEngineRenderer* PlayerHPCount3 = CreateRenderer("            .bmp", RenderPivot::CENTER, float4(         .0f,            .0f));

	PlayerUI_->CameraEffectOff();
	PlayerHP_->CameraEffectOff();
	PlayerHPMinus_->CameraEffectOff();
	PlayerHPCount1_->CameraEffectOff();
	PlayerHPCount2_->CameraEffectOff();
	// PlayerHPCount3->CameraEffectOff(); // HP에 맞춰 조정되도록 설정 필요

}

void BotUI::Update()
{
}
