#include "Cannon.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"
#include "Player.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>
#include "Tomato.h"

Cannon::Cannon()
{
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if (Player_->GetPosition().x >= GetMapSizeX() - 20)
	{
		GameEngine::GetInst().ChangeLevel("DanceStage");
	}

	if (true == CanRenderer_->IsAnimationName("CanStop") && true == CanRenderer_->IsEndAnimation())
	{
		Player_->SetGravity(0.0f);
		if ((PrevPos_.x - Player_->GetPosition().x) > -1000)
		{
			PlayerRenderer_->GetActor()->On();
			Player_->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 5000);
		}
	}

	if (true == CanRenderer_->IsAnimationName("CanMove") && true == CanRenderer_->IsEndAnimation() && true != CanRenderer_->IsAnimationName("CanStop"))
	{
		CanRenderer_->ChangeAnimation("CanStop");
		PlayerRenderer_->ChangeAnimation("Die");
	}

	if (/*RGB(0, 0, 0) == ColMapImage_->GetImagePixel(Player_->GetPosition() + float4::DOWN)*/CanCol_->CollisionCheck("KirbyCol",CollisionType::Rect,CollisionType::Rect) &&
		true != CanRenderer_->IsAnimationName("CanMove") &&
		true != CanRenderer_->IsAnimationName("CanStop"))
	{
		PrevPos_.x = Player_->GetPosition().x;
		PlayerRenderer_->GetActor()->Off();
		CanRenderer_->ChangeAnimation("CanMove");
	}
}


void Cannon::LevelChangeStart()
{
	SetMapSizeX(768);
	SetMapSizeY(576);
	{
		Background* Cannon = CreateActor<Background>((int)ORDER::BACKGROUND);
		Cannon->CreateRenderer("Cannon.bmp");

	}

	{
		Background* Can = CreateActor<Background>((int)ORDER::BACKGROUND);
		CanRenderer_ = Can->CreateRenderer("can.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0.0f, 30.0f));
		GameEngineImage* CanImage = CanRenderer_->GetImage();
		CanImage->CutCount(4, 2);
		CanRenderer_->CreateAnimation("can.bmp", "CanIdle", 0, 0, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "CanMove", 0, 7, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "CanStop", 0, 2, 0.08f, false);

		CanRenderer_->ChangeAnimation("CanIdle");
		CanCol_ = Can->CreateCollision("CanCol", float4(10.0f, 10.0f), float4(0.0f, 30.0f));

	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(384.0f, 0.0f));
		PlayerRenderer_ = Player_->GetRenderer();
		PlayerRenderer_->ChangeAnimation("JumpDownRight");
	}

	{
		Tomato* Tomato_ = CreateActor<Tomato>((int)ORDER::ITEM);
		GameEngineRenderer* TomatoRenderer = Tomato_->CreateRenderer("Tomato.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(384.0f, 50.0f));
	}
}

void Cannon::Loading()
{
}
