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
#include "Monster.h"

Player::Player()
	: Renderer_(nullptr)
	, Gravity_(20.8f)
	, AccGravity_(0.0f)
	, JumpHeight_(0.0f)
	, Time_(3.0f)
	, Level_(nullptr)
	, HPCount_(0)
{
}

Player::~Player()
{
}


void Player::SetPrevState(CharacterState _PrevState)
{
	PrevState_ = _PrevState;
}

CharacterState Player::GetPrevState()
{
	return PrevState_;
}

void Player::SetKirbyClass(KirbyClass _KirbyClass)
{
	KirbyClass_ = _KirbyClass;
}

KirbyClass Player::GetKirbyClass()
{
	return KirbyClass_;
}

void Player::Start()
{
	Level_ = GetLevel();
	SetHPCount(2);
	ColMapImage_ = Level_->GetColMapImage();
	KirbyCol_ = CreateCollision("KirbyCol", float4(0.0f, 0.0f), float4(0.0f, 0.0f));
	Renderer_ = CreateRenderer("Normal.bmp");
	SetHP(9);
	SetState(CharacterState::IDLE);

	GameEngineImage* Image = Renderer_->GetImage();
	Image->CutCount(10, 19);
	Renderer_->CreateAnimation("Normal.bmp", "WalkRight", 19, 28, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "WalkLeft", 111, 120, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "RunRight", 29, 36, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "RunLeft", 121, 128, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "IdleRight", 0, 0, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "IdleLeft", 92, 92, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "Inhale", 64, 69, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "HoverStartLeft", 156, 161, 0.1f, true);
	
	Renderer_->CreateAnimation("Normal.bmp", "HoveringRight", 70, 75, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "HoveringLeft", 162, 167, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "HoverEndRight", 85, 88, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "HoverEndLeft", 177, 180, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "HoverEnd2Right", 89, 90, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "HoverEnd2Left", 181, 182, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "EatingRight", 76, 78, 0.1f, true); 
	Renderer_->CreateAnimation("Normal.bmp", "EatingLeft", 168, 178, 0.1f, true); 

	Renderer_->CreateAnimation("Normal.bmp", "IdleWzMonsterRight", 79, 79, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "IdleWzMonsterLeft", 171, 171, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "WalkWzMonsterRight", 2, 17, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "WalkWzMonsterLeft", 94, 109, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "AttackRight", 18, 18, 0.3f, true);
	Renderer_->CreateAnimation("Normal.bmp", "AttackLeft", 110, 110, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "MoveDownRight", 1, 1, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "MoveDownLeft", 93, 93, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "JumpRight", 38, 38, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "JumpLeft", 38, 38, 0.1f, true);

	Renderer_->CreateAnimation("Normal.bmp", "JumpingRight", 39, 44, 0.1f, true);
	Renderer_->CreateAnimation("Normal.bmp", "JumpingLeft", 39, 44, 0.1f, true);

	Renderer_->ChangeAnimation("IdleRight");

	AttackEffectRenderer_ = CreateRenderer("Attack.bmp"	,static_cast<int>(EngineMax::RENDERORDERMAX),RenderPivot::CENTER,float4(100.0f,0.0f));
	GameEngineImage* Attack_ = AttackEffectRenderer_->GetImage();
	Attack_->CutCount(7, 2);
	AttackEffectRenderer_->CreateAnimation("Attack.bmp", "Attack", 0, 12, 0.1f, false);
	AttackEffectCol_ = CreateCollision("KirbyEffect", float4(40.0f, 40.0f), float4(100.0f, -20.0f)); // HoverKirbyEnd2가 바닥에 닿아 끝나면
	//AttackEffectRenderer_->CreateAnimation("AttackEffect.bmp", "AttackEffect", 0, 12, 0.1f, false);


	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("Hover", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("Eat", 'X');
		GameEngineInput::GetInst()->CreateKey("RunLeft", 'Q');
		GameEngineInput::GetInst()->CreateKey("RunRight", 'E');
		GameEngineInput::GetInst()->CreateKey("Inhale", 'Z'); // 흡입
		GameEngineInput::GetInst()->CreateKey("Fly", 'X'); // 날기
	}
}

void Player::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();

	SetPrevState(GetState());
	SetState(CharacterState::IDLE);
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

	if (true == CanHover()) // 다른거랑 동시에 불가
	{
		Hover();
	}
	if (true == CanEat())
	{
		Eat();
	}
	
	// 위치 처리
	UpdateMove();
	UpdateJump();
	UpdateFly();
	CorrectPos();

	// 충돌 처리
	CheckCollision();

	// 애니메이션 처리
	UpdateAnimation();
}

void Player::Render()
{
	float Time_ = GameEngineTime::GetDeltaTime();
	Time_ += Time_;
	std::string Text = std::to_string(Time_);

	TextOutA(GameEngine::BackBufferImage()->ImageDC(), 0, 0, Text.c_str(), Text.size());
}

void Player::UpdateMove()
{
	CharacterState State = GetState();
	float4 direction = float4::ZERO;
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") ||
		true == GameEngineInput::GetInst()->IsPress("RunLeft"))
	{
		direction = float4::LEFT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight") ||
		true == GameEngineInput::GetInst()->IsPress("RunRight"))
	{
		direction = float4::RIGHT;
	}
	SetMove(direction * GameEngineTime::GetDeltaTime() * GetSpeed());
}

void Player::UpdateJump()
{
	AccGravity_ += Gravity_ * GameEngineTime::GetDeltaTime();
	float JumpHeight = JumpHeight_ - AccGravity_;
	SetMove(float4(0, -JumpHeight));
}

void Player::UpdateFly()
{
	CharacterState State = GetState();
	if (State == CharacterState::HOVER)
	{
		if (true == Renderer_->IsAnimationName("HoveringRight"))
		{
			SetMove(float4::UP * GameEngineTime::GetDeltaTime() * static_cast<float>(GetSpeed()));
			AccGravity_ = 0;
			JumpHeight_ = 0;
		}
	}
}

void Player::CorrectPos()
{
	float4 CurrentPos = GetPosition();
	float4 JumpDirection = PrevPos_ - GetPosition();
	float JumpDirectionX = JumpDirection.x > 0 ? float4::RIGHT.x : float4::LEFT.x;
	float JumpDirectionY = JumpDirection.y > 0 ? float4::DOWN.y : float4::UP.y;
	while (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x, GetPosition().y))
	{
		SetMove(float4(0, JumpDirectionY));
		AccGravity_ = 0;
		JumpHeight_ = 0;
	}

	while ((RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y) && RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y - 40))
		|| (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y) && RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y - 40)))
	{
		SetMove(float4(JumpDirectionX, 0));
	}

	if (CurrentPos.x < 0)
	{
		SetPosition(float4(0, CurrentPos.y));
	}
	if (CurrentPos.x > GetLevel()->GetMapSizeX())
	{
		SetPosition(float4(GetLevel()->GetMapSizeX(), CurrentPos.y));
	}
	if (CurrentPos.y < 50)
	{
		SetPosition(float4(CurrentPos.x, 50));
	}
}

void Player::CheckCollision()
{
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

	if (GetState() == CharacterState::HOVER)
	{
		//AttackEffectRenderer_->SetImageScale();
		std::vector <GameEngineCollision*> ColResult;
		if (true == AttackEffectCol_->CollisionResult("BasicMonster", ColResult, CollisionType::Rect, CollisionType::Rect))
		{
			for (GameEngineCollision* Collision : ColResult)
			{
				GameEngineActor* Actor = Collision->GetActor();
				Monster* Monster_ = dynamic_cast<Monster*>(Actor);
				if (nullptr != Monster_)
				{
					AttackEffectRenderer_->ChangeAnimation("Attack");
					float4 Position;
					Position.x = Monster_->GetPosition().x - 5;
					Position.y = Monster_->GetPosition().y;
					Monster_->SetPosition(Position);
				}
			}
		}
	}
	else
	{
		AttackEffectRenderer_->SetScale(float4(0.0f, 0.0f));
	}
}

void Player::UpdateAnimation()
{
	CharacterState State = GetState();
	CharacterState PrevState = GetPrevState();
	float4 Direction = PrevPos_ - GetPosition();

	if (State == CharacterState::HOVER)
	{
		if (PrevState != CharacterState::HOVER)
		{
			Renderer_->ChangeAnimation("Inhale");
		}
		else if (Renderer_->IsAnimationName("Inhale") &&
			Renderer_->IsEndAnimation())
		{
			Renderer_->ChangeAnimation("HoveringRight");
		}
	}
	else if (0 != AccGravity_)
	{
		if (Direction.y < 0)
		{
			if (PrevState == CharacterState::HOVER && State != CharacterState::HOVER)
			{
				Renderer_->ChangeAnimation("AttackRight");
				//AttackEffectRenderer_->ChangeAnimation("Attack");// 떨어지는 동작 1
			}
			else if (true == Renderer_->IsAnimationName("AttackRight"))
			{
				if (true == Renderer_->IsEndAnimation())
				{
					//Renderer_->ChangeAnimation("HoverEndRight");
					Renderer_->ChangeAnimation("HoverEnd2Right");
				}
			}
			else
			{
				if (false == Renderer_->IsAnimationName("HoverEnd2Right"))
				{
					Renderer_->ChangeAnimation("JumpingRight");
				}
				else if (true == Renderer_->IsAnimationName("JumpingRight") &&
					true == Renderer_->IsEndAnimation())
				{
					//Renderer_->ChangeAnimation("HoverEndRight");
					Renderer_->ChangeAnimation("HoverEnd2Right");
				}
			}

		}
		else
		{
			if (GetState() != CharacterState::HOVER)
			{
				Renderer_->ChangeAnimation("JumpRight");
			}
		}
	}
	else if (State == CharacterState::WALK)
	{
		if (PrevState != CharacterState::WALK)
		{
			Renderer_->ChangeAnimation("WalkRight");
		}
	}
	else if (State == CharacterState::RUN)
	{
		if (PrevState != CharacterState::RUN)
		{
			Renderer_->ChangeAnimation("RunRight");
		}
	}
	else if (State == CharacterState::IDLE)
	{
		Renderer_->ChangeAnimation("IdleRight");
	}
	
	//switch (State)B
	//{
	//case CharacterState::INHALE:
	//	Renderer_->ChangeAnimation("Inhale");
	//	if (true == Renderer_->IsEndAnimation())
	//	{
	//		// 돼지 되기
	//	}
	//	break;
	//case CharacterState::EAT:
	//	Renderer_->ChangeAnimation("HoverStartRight");
	//	if (true == Renderer_->IsEndAnimation())
	//	{
	//		Renderer_->ChangeAnimation("EatingRight");
	//		if (true == Renderer_->IsEndAnimation())
	//		{
	//			Renderer_->ChangeAnimation("IdleWzMonsterRight"); // 이제부터 걸을때도 볼 부풀린채로
	//			Renderer_->ChangeAnimation("AttackRight"); // 별쏘기
	//			//AttackEffectRenderer_->ChangeAnimation("AttackEffect");
	//		}
	//	}
	//	break;
	//}
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
	return GameEngineInput::GetInst()->IsUp("Jump");
}

bool Player::CanFly()
{
	return GameEngineInput::GetInst()->IsPress("Fly");
}

bool Player::CanInhale()
{
	return GameEngineInput::GetInst()->IsPress("Inhale");
}

bool Player::CanHover()
{
	return GameEngineInput::GetInst()->IsPress("Hover")
		&& GetState() != CharacterState::RUN;
}

bool Player::CanEat()
{
	return GameEngineInput::GetInst()->IsPress("Eat")
		&& GetState() != CharacterState::WALK
		&& GetState() != CharacterState::RUN;
}

void Player::Walk()
{
	SetState(CharacterState::WALK);
}

void Player::Run()
{
	SetState(CharacterState::RUN);
}

void Player::Jump()
{
	JumpHeight_ = 20;

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
		//if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x + 20, GetPosition().y))
		//{
		//	return true;
		//}

		//if (RGB(0, 0, 0) == ColMapImage_->GetImagePixel(GetPosition().x - 20, GetPosition().y))
		//{
		//	return true;
		//}


		////왼쪽, 오른쪽, 위쪽으로 이동 금지 -> 맵마다 다름
		//if (GetPosition().x < 0 || GetPosition().x > GetLevel()->GetMapSizeX() || GetPosition().y < 50)
		//{
		//	return true;
		//}
	}
	return true;
}

void Player::Hover()
{
	SetState(CharacterState::HOVER);
}

void Player::Eat()
{
	SetState(CharacterState::EAT);
}

void Player::Fly()
{
	SetState(CharacterState::FLY);
}

void Player::Inhale()
{
	SetState(CharacterState::INHALE);
}
