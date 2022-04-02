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
	: ColMapImage_(nullptr)
	, Gravity_(1.00f)
	, AccGravity_(1.0f)
	, Speed_(1)
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
		Render->CreateAnimation("star.bmp", "star", 0, 1, 0.1f, true);*/ // �ҿ��������� -> Ÿ���� �𸥴�.
		//SetScale({ 500, 500 });

		//CreateRenderer("sparkkirby.bmp");

		//CreateRendererToScale("logoc.bmp", float4(508.0f, 467.0f), RenderPivot::CENTER, float4(0.0f, 180.0f));

		// CreateRendererToScale("12345.bmp", float4(508.0f, 467.0f), RenderPivot::CENTER, float4(0.0f, 180.0f));
		// CreateRendererToScale("sparkkirby.bmp", float4(102.0f, 98.0f), RenderPivot::CENTER, float4(0.0f, 180.0f));

		// CreateRenderer("testkirby.bmp");
		// CreateRenderer("BackgroundB.bmp");
		// CreateRenderer("LogoC.bmp");
		//CreateRendererToScale("BackgroundE.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));
		//CreateRenderer("monster.bmp", RenderPivot::CENTER, { 0,-1000 }); // �������� 100 �÷� �׷���

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft")) // moveleft�� ������ �������
	{
		// �̶� �빮�ڿ��� �մϴ�.
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

	if (true == CanJump()) // Shift
	{
		Jump();
	}

	if (true == CanMoveUp())
	{
		MoveUp();
	}

	if (true == CanMoveDown())
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
		MsgBoxAssert("�浹�� �̹����� ã�� ���߽��ϴ�.")
	}

} ///////////////////////////need to chk

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
	float4 NextPos = GetPosition() + (direction * GameEngineTime::GetDeltaTime() * GetSpeed());
	int Color = ColMapImage_->GetImagePixel(NextPos);
	if (RGB(0, 0, 0) != Color)
	{
		AccGravity_ = 0.05f;
		SetMove(direction * AccGravity_ * GetSpeed());
	}
	else if (RGB(0, 0, 0) == Color)
	{
		AccGravity_ = 0.0f;
	}
}

void Player::Run()
{
	SetState(CharacterState::RUN);
	float4 direction = GameEngineInput::GetInst()->IsPress("RunLeft") ? float4::LEFT : float4::RIGHT;
	float4 NextPos = GetPosition() + (direction * GameEngineTime::GetDeltaTime() * GetSpeed());
	int Color = ColMapImage_->GetImagePixel(NextPos);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(direction * AccGravity_ * GetSpeed());
	}
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
		SetJumpHeight(GetPosition().y); // SaveHeight�� �̸� �����ϱ�
	}

	float desiredHeight = GetPosition().y * GameEngineTime::GetDeltaTime() * 30;/*GetJumpSpeed();*/
	// ���� ���ǵ�
	float4 direction = desiredHeight - GetJumpHeight() < GetJumpMaxHeight() ? float4::UP : float4::DOWN;
	SetMove(direction * GameEngineTime::GetDeltaTime() * GetSpeed()/**/);
}

void Player::MoveUp()
{
	///////////////////////////////////////////////need chk
	SetState(CharacterState::Up);
	if (GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * AccGravity_ * static_cast<float>(Speed_));
	} // need to chk
}


void Player::MoveDown()
{
	SetState(CharacterState::Down);
	if (GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * AccGravity_ * static_cast<float>(Speed_));
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