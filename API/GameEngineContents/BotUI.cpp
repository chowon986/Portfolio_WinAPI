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
	PlayerUI_ = CreateRenderer("NormalStatus.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(49.0f, 550.0f));
	PlayerHP_ = CreateRenderer("HPUI.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235.0f, 545.0f));
	PlayerHPMinus_ = CreateRenderer("HPMinus.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(235.0f, 552.0f));
	PlayerHPCount1_ = CreateRenderer("PlayerHPCount1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(155.0f, 520.0f));
	PlayerHPCount2_ = CreateRenderer("PlayerHPCount2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(190.0f, 520.0f));
	PlayerHPCount3_ = CreateRenderer("Number.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(315.0f, 518.0f));

	PlayerUI_->CameraEffectOff();
	PlayerHP_->CameraEffectOff();
	PlayerHPMinus_->CameraEffectOff();
	PlayerHPCount1_->CameraEffectOff();
	PlayerHPCount2_->CameraEffectOff();
	PlayerHPCount3_->CameraEffectOff();
}

void BotUI::Update()
{

}

void BotUI::Render()
{
}
