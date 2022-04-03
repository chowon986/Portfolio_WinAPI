#include "Level1.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "BotUI.h"
#include "ContentsEnum.h"
#include "GameEngine/GameEngineImage.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineWindow.h>

Level1::Level1()
	:MapSizeX_(4608)
	,MapSizeY_(576)
	,Player_(nullptr)
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
	{
		Background* Stage1 = CreateActor<Background>((int)ORDER::BACKGROUND);
		//Stage1->CreateRendererToScale("Stage1.bmp",float4(MapSizeX_, MapSizeY_), RenderPivot::CENTER, float4(1920.0f, 0.0f));
		Stage1->CreateRendererToScale("Stage1ColMap.bmp", float4(MapSizeX_, MapSizeY_), RenderPivot::CENTER, float4(1920.0f, 0.0f));
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
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	{
		Monster* Waddledi = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* WaddlediRenderer = Waddledi->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(1200.0f, 430.0f));
		GameEngineImage* WaddlediImage = WaddlediRenderer->GetImage();
		WaddlediImage->CutCount(10, 26);
		WaddlediRenderer->CreateAnimation("monster0.bmp", "WaddlediIdel", 7, 13, 0.3f, true);
		WaddlediRenderer->ChangeAnimation("WaddlediIdel");
	}
	
	{
		Monster* WaddleDoo = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* WaddleDooRenderer = WaddleDoo->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(2820.0f, 370.0f));
		GameEngineImage* WaddleDooImage = WaddleDooRenderer->GetImage();
		WaddleDooImage->CutCount(10, 26);
		WaddleDooRenderer->CreateAnimation("monster0.bmp", "WaddleDooIdel", 17, 21, 0.3f, true);
		WaddleDooRenderer->ChangeAnimation("WaddleDooIdel");
	}


	{
		Monster* Sparky = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* SparkyRenderer = Sparky->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(3780.0f, 380.0f));
		GameEngineImage* SparkyImage = SparkyRenderer->GetImage();
		SparkyImage->CutCount(10, 26);
		SparkyRenderer->CreateAnimation("monster0.bmp", "SparkyIdel", 108, 111, 0.3f, true);
		SparkyRenderer->ChangeAnimation("SparkyIdel");
	}

}
