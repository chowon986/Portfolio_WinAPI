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
	, Renderer_(nullptr)
	, Gravity_(1.00f)
	, AccGravity_(1.0f)
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

	Renderer_ = CreateRenderer("star.bmp");
	Renderer_->CreateAnimation("star.bmp", "star", 0, 1, 0.1f, true);
	Renderer_->ChangeAnimation("star");

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
	ColMapImage_ = GameEngineImageManager::GetInst()->Find("Stage1ColMap.bmp");

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

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
	PrevPos_ = GetPosition();

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

	if (true == CheckMapCollision())
	{
		SetPosition(PrevPos_);
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
	switch (GetState())
	{
	case CharacterState::RUN:
		return CharacterBase::GetSpeed() * 2;
	default:
		return CharacterBase::GetSpeed();
	}
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
	SetMove(float4::UP * GameEngineTime::GetDeltaTime() * static_cast<float>(GetSpeed()));
}


void Player::MoveDown()
{
	SetState(CharacterState::Down);
	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * static_cast<float>(GetSpeed()));
}

bool Player::CheckMapCollision()
{
	int Color = RGB(255, 255, 255);
	if (nullptr != ColMapImage_)
	{
		float4 Pos = GetPosition();

		// cut 2번 하는거 같다. 찾아보기 
		float4 Scale = Renderer_->GetImage()->GetCutScale(0);
		float4 HalfWidth(Scale.x * 0.5, 0);
		float4 HalfHeight(0, Scale.y * 0.5);
		
		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Pos + HalfWidth))
			return true;

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Pos - HalfWidth))
			return true;

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Pos + HalfHeight))
			return true;

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Pos - HalfHeight))
			return true;
	}

	return RGB(0, 0, 0) == Color;
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