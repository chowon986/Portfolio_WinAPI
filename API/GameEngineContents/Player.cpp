#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

Player::Player()
	:CharacterBase()
{
}

Player::~Player()
{
}


void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500, 500 });


	CreateRenderer("sparkkirby.bmp");
	//CreateRendererToScale("logoc.bmp", float4(508.0f, 467.0f), RenderPivot::CENTER, float4(0.0f, 180.0f));

	// CreateRendererToScale("12345.bmp", float4(508.0f, 467.0f), RenderPivot::CENTER, float4(0.0f, 180.0f));
	// CreateRendererToScale("sparkkirby.bmp", float4(102.0f, 98.0f), RenderPivot::CENTER, float4(0.0f, 180.0f));

	// CreateRenderer("testkirby.bmp");
	// CreateRenderer("BackgroundB.bmp");
	// CreateRenderer("LogoC.bmp");
	//CreateRendererToScale("BackgroundE.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));
	//CreateRenderer("monster.bmp", RenderPivot::CENTER, { 0,-1000 }); // 위쪽으로 100 올려 그려라

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft")) // moveleft가 없으면 만들어줘
	{
		// 이때 대문자여야 합니다.
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("Fire", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("RunLeft", 'Q');
		GameEngineInput::GetInst()->CreateKey("RunRight", 'E');
		// VK_LBUTTON;
	}

}

void Player::Update()
{
	if (true == CanRun())
	{
		Run();
	}

	else if (true == CanWalk())
	{
		Walk();
	}

	if (CanJump()) // Shift
	{
		Jump();
	}


	//if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	//{
	//	SetMove(float4::UP * GameEngineTime::GetDeltaTime() * GetSpeed());
	//}

	//if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	//{
	//	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * GetSpeed());
	//}

}

float Player::GetSpeed()
{
	return GetState() == CharacterState::WALK ? CharacterBase::GetSpeed() : CharacterBase::GetSpeed() * 2;
}

bool Player::CanWalk()
{
	return GameEngineInput::GetInst()->IsPress("MoveLeft")
		|| GameEngineInput::GetInst()->IsPress("MoveRight");
}

bool Player::CanRun()
{
	return GameEngineInput::GetInst()->IsPress("RunLeft")
		|| GameEngineInput::GetInst()->IsPress("RunRight");
}

bool Player::CanJump() //"Jump", VK_LSHIFT
{
	return GameEngineInput::GetInst()->IsUp("Jump") || GetState() == CharacterState::JUMP;
}

void Player::Walk()
{
	SetState(CharacterState::WALK);
	float4 direction = GameEngineInput::GetInst()->IsPress("MoveLeft") ? float4::LEFT : float4::RIGHT;
	SetMove(direction * GameEngineTime::GetDeltaTime() * GetSpeed());

	// 나중에 애니메이션 구현하기
	// if (GetState() == CharacterState::WALK) {걷는 애니메이션}
}

void Player::Run()
{
	SetState(CharacterState::RUN);
	float4 direction = GameEngineInput::GetInst()->IsPress("RunLeft") ? float4::LEFT : float4::RIGHT;
	SetMove(direction * GameEngineTime::GetDeltaTime() * GetSpeed());
}

void Player::Jump()
{
	if (GetJumpHeight() == GetPosition().y)
	{
		SetState(CharacterState::IDLE);
		return;
	}

	if (GetState() != CharacterState::JUMP)
	{
		SetState(CharacterState::JUMP);
		SetJumpHeight(GetPosition().y); // SaveHeight로 이름 변경하기
	}

	float desiredHeight = GetPosition().y * GameEngineTime::GetDeltaTime() * 30;/*GetJumpSpeed();*/
	// 점프 스피드
	float4 direction = desiredHeight - GetJumpHeight() < GetJumpMaxHeight() ? float4::UP : float4::DOWN;
	SetMove(direction * GameEngineTime::GetDeltaTime() * 30/**/);
}

void Player::Render()
{

}