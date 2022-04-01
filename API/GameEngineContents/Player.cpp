#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>

Player::Player()
	: CharacterBase()
{
}

Player::~Player()
{
}


void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("star.bmp");
	Image->CutCount(2, 1);

	GameEngineRenderer* Render = CreateRenderer("star.bmp");
	Render->CreateAnimation("star.bmp", "star", 0, 1, 0.1f, true);
	Render->ChangeAnimation("star");

	/*	GameEngineRenderer* Render = CreateRenderer("star.bmp");
		Render->CreateAnimation("star.bmp", "star", 0, 1, 0.1f, true);*/ // 불완전한형식 -> 타입을 모른다.
		//SetScale({ 500, 500 });

		//CreateRenderer("sparkkirby.bmp");

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
	//Render->SetIndex(0);
	//Render->CreateAnimation("star.bmp", "star", 0, 1, 0.1f, true);
	//Render->SetIndex(0);
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

	if (CanMoveUp())
	{
		MoveUp();
	}

	if (CanMoveDown())
	{
		MoveDown();
	}

	//GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	//if (0 > GetLevel()->GetCameraPos().x)
	//{
	//	float4 CurCameraPos = GetLevel()->GetCameraPos();
	//	CurCameraPos.x = 0;
	//	GetLevel()->SetCameraPos(CurCameraPos);
	//}


	//if (0 > GetLevel()->GetCameraPos().y)
	//{
	//	float4 CurCameraPos = GetLevel()->GetCameraPos();
	//	CurCameraPos.y = 0;
	//	GetLevel()->SetCameraPos(CurCameraPos);
	//}

	//float MapSizeX = 4608;
	//float MapSizeY = 576;
	//float CameraRectX = 768;
	//float CameraRectY = 576;

	//if (MapSizeX <= GetLevel()->GetCameraPos().x + CameraRectX)
	//{
	//	float4 CurCameraPos = GetLevel()->GetCameraPos();
	//	CurCameraPos.x = GetLevel()->GetCameraPos().x - (GetLevel()->GetCameraPos().x + CameraRectX - MapSizeX);
	//	GetLevel()->SetCameraPos(CurCameraPos);
	//}

	//if (MapSizeY <= GetLevel()->GetCameraPos().y + CameraRectY)
	//{
	//	float4 CurCameraPos = GetLevel()->GetCameraPos();
	//	CurCameraPos.y = GetLevel()->GetCameraPos().y - (GetLevel()->GetCameraPos().y + CameraRectY - MapSizeY);
	//	GetLevel()->SetCameraPos(CurCameraPos);
	//}
	ColMapImage_ = GameEngineImageManager::GetInst()->Find("Stage1ColMap.bmp");
	
	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

}

bool Player::CanMoveUp()
{
	return GameEngineInput::GetInst()->IsPress("MoveUp");
}

bool Player::CanMoveDown()
{
	return GameEngineInput::GetInst()->IsPress("MoveDown");
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
	SetMove(direction * GameEngineTime::GetDeltaTime() * GetSpeed()/**/);
}

void Player::MoveUp()
{
	SetState(CharacterState::Up);
	if (GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * GetSpeed());
	}
}

void Player::MoveDown()
{
	SetState(CharacterState::Down);
	if (GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * GetSpeed());
	}
}

/*
	int Color = ColMapImage_->GetImagePixel(GetPosition());
	if (RGB(0, 0, 0) == Color)
	{
		Gravity_ =  0.0f;
	}
*/


void Player::Render()
{

}