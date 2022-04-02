#include "Level1_3.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>

Level1_3::Level1_3()
	: Player_(nullptr)
	, MapSizeX_(768)
	, MapSizeY_(1152)
{
}

Level1_3::~Level1_3()
{
}


void Level1_3::Loading()
{
}

void Level1_3::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1_4");
	}


	// CHK : CAMERA SETTING
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

void Level1_3::LevelChangeStart()
{
	{
		Background* Stage1_2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_2->CreateRendererToScale("Stage1_3.bmp", float4(MapSizeX_, MapSizeY_), RenderPivot::CENTER, float4(0.0f, -96.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
	}

	{
		// 아이템 생성
		Monster* HPUP = CreateActor<Monster>((int)ORDER::MONSTER);
		HPUP->CreateRenderer("HPUP.bmp", RenderPivot::CENTER, float4(145, 26));
	}

}
