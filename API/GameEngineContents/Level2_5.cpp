#include "Level2_5.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Monster1.h"
#include "Sword.h"
#include "Tiktik.h"
#include "BotUI.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

Level2_5::Level2_5()
	: Player_(nullptr)
	, MapSizeX_(5280)
	, MapSizeY_(576)
{
}

Level2_5::~Level2_5()
{
}


void Level2_5::Loading()
{
}

void Level2_5::Update()
{
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

void Level2_5::LevelChangeStart()
{
	SetColMapImage("Stage2_5ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage2_5 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage2_5->CreateRenderer("Stage2_5.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-2352.0f, 0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(100, 100));
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	{
		Monster* TreasureChest = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* TreasureChestRenderer = TreasureChest->CreateRenderer("TresureChest.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(958.0f, 330.0f));
	}

	// 커터 or 대체?

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(340.0f, 858.0f));
	}

	{
		Tiktik* Tiktik_ = CreateActor<Tiktik>((int)ORDER::MONSTER);
		Tiktik_->SetPosition(float4(340.0f, 858.0f));
	}
}

float Level2_5::GetMapSizeY()
{
	return MapSizeY_;
}

float Level2_5::GetMapSizeX()
{
	return MapSizeX_;
}
