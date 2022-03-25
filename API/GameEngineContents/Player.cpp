#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500, 500 });


	CreateRenderer("BackgroundB.bmp");
	//CreateRendererToScale("logoc.bmp", float4(508.0f, 467.0f), RenderPivot::CENTER, float4(0.0f, 180.0f));
	
	// CreateRendererToScale("12345.bmp", float4(508.0f, 467.0f), RenderPivot::CENTER, float4(0.0f, 180.0f));
	// CreateRendererToScale("sparkkirby.bmp", float4(102.0f, 98.0f), RenderPivot::CENTER, float4(0.0f, 180.0f));
	
	// CreateRenderer("testkirby.bmp");
	// CreateRenderer("BackgroundB.bmp");
	// CreateRenderer("LogoC.bmp");
	//CreateRendererToScale("BackgroundE.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));
	//CreateRenderer("monster.bmp", RenderPivot::CENTER, { 0,-1000 }); // 위쪽으로 100 올려 그려라

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		// 이때 대문자여야 합니다.
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("Fire", VK_SPACE);
		// VK_LBUTTON;
	}

}

void Player::Update()
{
	//if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	////{
	////	SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	////}

	////if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	////{
	////	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	////}

	////if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	////{
	////	SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	////}

	////if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	////{
	////	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	////}

	//// 내가 키를 눌렀다면 움직여라.
	////if (0 != GetAsyncKeyState('A'))
	////{
	////	int a = 0;
	////}
}

void Player::Render()
{

}