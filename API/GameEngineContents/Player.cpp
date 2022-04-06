#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include "Level1.h"
#include "Level1_2.h"
#include "Level1_3.h"
#include "Level1_4.h"
#include "Level2.h"
#include "Level2_2.h"

Player::Player()
	: Renderer_(nullptr)
	, Gravity_(1.00f)
	, AccGravity_(1.0f)
	, Time_(3.0f)
	, Level_(nullptr)
{
}

Player::~Player()
{
}


void Player::Start()
{
	Level_ = GetLevel();
	ColMapImage_ = Level_->GetColMapImage();
	KirbyCol_ = CreateCollision("KirbyCol", float4(50, 50), float4(0, -25));
	Renderer_ = CreateRenderer("NormalKirby.bmp");
	SetHP(9);
	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 16);
	Renderer_->CreateAnimation("NormalKirby.bmp", "WalkKirby", 10, 19, 0.1f, true);
	Renderer_->ChangeAnimation("WalkKirby");
	Renderer_->CreateAnimation("NormalKirby.bmp", "RunKirby", 21, 28, 0.1f, true);

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
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

	Time_ += GameEngineTime::GetDeltaTime();
	if (true == KirbyCol_->CollisionCheck("DoorCol1_2", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Level1_2"); 
	}

	if (true == KirbyCol_->CollisionCheck("DoorCol1_3", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Level1_3"); 
	}

	if (true == KirbyCol_->CollisionCheck("DoorCol1_4", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Level1_4"); 
	}

	if (true == KirbyCol_->CollisionCheck("Cannon", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Cannon"); 
	}

	if (true == KirbyCol_->CollisionCheck("DorrCol2_2", CollisionType::Rect, CollisionType::Rect))
	{
		GameEngine::GetInst().ChangeLevel("Level2_2"); 
	}


	if (true == KirbyCol_->CollisionCheck("BasicMonster", CollisionType::Rect, CollisionType::Rect) && Time_ >= 3)
	{
		Time_ = 0;
		SetHP(GetHP() - 1);
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
	Renderer_->ChangeAnimation("WalkKirby");
	float4 direction = GameEngineInput::GetInst()->IsPress("MoveLeft") ? float4::LEFT : float4::RIGHT;
	SetMove(direction * GameEngineTime::GetDeltaTime() * GetSpeed());
}

void Player::Run()
{
	SetState(CharacterState::RUN);
	Renderer_->ChangeAnimation("RunKirby");
	float4 direction = GameEngineInput::GetInst()->IsPress("RunLeft") ? float4::LEFT : float4::RIGHT;
	SetMove(direction * GameEngineTime::GetDeltaTime() * GetSpeed());
}

void Player::Jump()
{
	//float4 JumpStartHeight = GetPosition();

	//if (GetJumpHeight() == GetPosition().y)
	//{
	//	SetState(CharacterState::IDLE);
	//	return;
	//}

	//if (GetState() != CharacterState::JUMP)
	//{
	//	float JumpTime_ = 0.0f;
	//	JumpTime_+= GameEngineTime::GetDeltaTime();
	//	for (GetPosition();JumpTime_ < 3;GetPosition().y -10)
	//	{
	//		SetMove(float4(0.0f, GetPosition().y));
	//	}
	//}

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
	if (nullptr != ColMapImage_)
	{
		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y))
		{
			return true;
		}

		if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y))
		{
			return true;
		}

		//if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x, GetPosition().y - 40))
		//{
		//	return true;
		//}

		//왼쪽, 오른쪽, 위쪽으로 이동 금지 -> 맵마다 다름
		if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50)
		{
			return true;
		}
	}
}