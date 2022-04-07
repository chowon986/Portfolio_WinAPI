#include "Level2_4.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Sword.h"
#include "BotUI.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>

Level2_4::Level2_4()
	: Player_(nullptr)
	, MapSizeX_(768)
	, MapSizeY_(1152)
{
}

Level2_4::~Level2_4()
{
}


void Level2_4::Loading()
{
}

void Level2_4::Update()
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

void Level2_4::LevelChangeStart()
{
	SetColMapImage("Stage2_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage2_4 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage2_4->CreateRenderer("Stage2_4.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0.0f,288.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(370, 850));
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	{
		Sword* Sword_ = CreateActor<Sword>((int)ORDER::MONSTER);
		Sword_->SetPosition(float4(340.0f, 858.0f));
	}
}

float Level2_4::GetMapSizeY()
{
	return MapSizeY_;
}

float Level2_4::GetMapSizeX()
{
	return MapSizeX_;
}
