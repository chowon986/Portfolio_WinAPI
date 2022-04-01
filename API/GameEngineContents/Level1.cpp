#include "Level1.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
////#include "Waddledi.h"
//#include "Waddledu.h"
//#include "Sparky.h"
//#include "Box.h"
//#include "Fire.h"
//#include "Brontobert.h"
//#include "BigBox.h"
//#include "Monster1.h"
//#include "Tomato.h"
//#include "Bomb.h"
//#include "Background.h"
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
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1_2");
	}

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
		Stage1->CreateRendererToScale("Stage1.bmp",float4(MapSizeX_, MapSizeY_), RenderPivot::CENTER, float4(1920.0f, 0.0f));
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
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
	}

	Monster* Waddledi = CreateActor<Monster>((int)ORDER::MONSTER);
	GameEngineRenderer* WaddlediRenderer = Waddledi->CreateRendererToScale("walkwaddledi.bmp", float4(115.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 150.0f));
	GameEngineImage* WaddlediImage = WaddlediRenderer->GetImage();
	WaddlediImage->CutCount(5, 1);
	WaddlediRenderer->CreateAnimation("walkwaddledi.bmp", "WalkWaddledi", 0, 4, 0.1f, true);
	WaddlediRenderer->ChangeAnimation("WalkWaddledi");
	

	Monster* Waddledu = CreateActor<Monster>((int)ORDER::MONSTER);
	GameEngineRenderer* WaddleduRenderer= Waddledu->CreateRendererToScale("waddledu.bmp", float4(150.0f, 100.0f), RenderPivot::CENTER, float4(500.0f, 100.0f));
	GameEngineImage* WaddleduImage = WaddleduRenderer->GetImage();
	//WaddleduImage->CutCount();
	//WaddleduRenderer->CreateAnimation();
	//WaddleduRenderer->ChangeAnimation();

	Monster* Sparky = CreateActor<Monster>((int)ORDER::MONSTER);
	Sparky->CreateRendererToScale("Sparky.bmp", float4(141.0f, 122.0f), RenderPivot::CENTER, float4(128.0f, 80.0f));

}
