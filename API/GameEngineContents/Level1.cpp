#include "Level1.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Waddledi.h"
#include "Waddledoo.h"
#include "Sparky.h"
#include "BotUI.h"
#include "ContentsEnum.h"
#include "GameEngine/GameEngineImage.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>


Level1::Level1()
	: MapSizeX_(4608)
	, MapSizeY_(576)
	, Player_(nullptr)
	, PlayerStatus_(nullptr)
	, ColMapImage_(nullptr)
{

}

Level1::~Level1()
{
}


void Level1::Loading()
{

}

void Level1::Update()
{
	/*if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1_2");
	}*/

	SetCameraPos(Player_->GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	if (0 > GetCameraPos().x)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = 0;
		SetCameraPos(CurCameraPos);
	}

	if (0 > GetCameraPos().y)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = 0;
		SetCameraPos(CurCameraPos);
	}

	float CameraRectX = 768;
	float CameraRectY = 576;

	if (MapSizeX_ <= GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = GetCameraPos().x - (GetCameraPos().x + CameraRectX - MapSizeX_);
		SetCameraPos(CurCameraPos);
	}

	if (MapSizeY_ <= GetCameraPos().y + CameraRectY)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = GetCameraPos().y - (GetCameraPos().y + CameraRectY - MapSizeY_);
		SetCameraPos(CurCameraPos);
	}

}

void Level1::LevelChangeStart()
{
	SetColMapImage("Stage1ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage1 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1->CreateRenderer("Stage1.bmp", RenderPivot::CENTER, float4(1920.0f, 0.0f));
	}

	{
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		Door->CreateRenderer("Door.bmp", RenderPivot::CENTER, float4(4153.0f, 60.0f));
		DoorCol1_2 = Door->CreateCollision("DoorCol1_2", float4(44.0f, 64.0f), float4(4153.0f,60.0f));

		Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("DoorStar.bmp", RenderPivot::CENTER, float4(4153.0f, 10.0f));
		GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
		DoorStarImage->CutCount(6, 2);
		DoorStarRenderer->CreateAnimation("DoorStar.bmp", "DoorStar", 0, 11, 0.05f, true);
		DoorStarRenderer->ChangeAnimation("DoorStar");
	}
	{
		Background* Grass1 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass1Renderer = Grass1->CreateRenderer("grass1.bmp", RenderPivot::CENTER, float4(245.0f, 150.0f));
		GameEngineImage* Grass1Image = Grass1Renderer->GetImage();
		Grass1Image->CutCount(2, 2);
		Grass1Renderer->CreateAnimation("grass1.bmp", "grass1", 0, 3, 0.5f, true);
		Grass1Renderer->ChangeAnimation("grass1");
	}

	{
		Background* Grass2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass2Renderer = Grass2->CreateRenderer("grass2.bmp", RenderPivot::CENTER, float4(2078.0f, -45.0f));
		GameEngineImage* Grass2Image = Grass2Renderer->GetImage();
		Grass2Image->CutCount(2, 2);
		Grass2Renderer->CreateAnimation("grass2.bmp", "grass2", 0, 3, 0.5f, true);
		Grass2Renderer->ChangeAnimation("grass2");
	}

	{
		Background* Grass3 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass3Renderer = Grass3->CreateRenderer("grass3.bmp", RenderPivot::CENTER, float4(3545.0f, 97.0f));
		GameEngineImage* Grass3Image = Grass3Renderer->GetImage();
		Grass3Image->CutCount(2, 2);
		Grass3Renderer->CreateAnimation("grass3.bmp", "grass3", 0, 3, 0.5f, true);
		Grass3Renderer->ChangeAnimation("grass3");
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(/*205.0*/4100.0f, /*436.0*/200.0f));
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	{
		Waddledi* Waddledi_ = CreateActor<Waddledi>((int)ORDER::MONSTER);
		Waddledi_->SetPosition(float4(1200.0f, 430.0f));
	}

	{
		Waddledoo* Waddledoo_ = CreateActor<Waddledoo>((int)ORDER::MONSTER);
		Waddledoo_->SetPosition(float4(2837.0f, 377.0f));
		GameEngineCollision* WaddledooCol = Waddledoo_->CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	}

	{
		Monster* Sparky_ = CreateActor<Sparky>((int)ORDER::MONSTER);
		Sparky_->SetPosition(float4(3780.0f, 380.0f));
		GameEngineCollision* SparkyCol = Sparky_->CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	}
}


float Level1::GetMapSizeY()
{
	return MapSizeY_;
}

float Level1::GetMapSizeX()
{
	return MapSizeX_;
}