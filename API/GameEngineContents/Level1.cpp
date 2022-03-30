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

Level1::Level1()
{
}

Level1::~Level1()
{
}


void Level1::Loading()
{
	{
		Background* Stage1 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1->CreateRendererToScale("stage1.bmp", float4(1536.0f, 192.0f), RenderPivot::CENTER, float4(640.0f, 0.0f));
	}

	{
		CreateActor<Player>((int)ORDER::PLAYER);

	}

	Monster* WaddleDi = CreateActor<Monster>((int)ORDER::MONSTER);
	WaddleDi->CreateRendererToScale("walkwaddledi.bmp",float4(130.0f,24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));
	
	Monster* Waddledu = CreateActor<Monster>((int)ORDER::MONSTER);
	Waddledu->CreateRendererToScale("waddledu.bmp", float4(150.0f, 100.0f), RenderPivot::CENTER, float4(500.0f, 100.0f));

	Monster* Sparky = CreateActor<Monster>((int)ORDER::MONSTER);
	Sparky->CreateRendererToScale("Sparky.bmp", float4(141.0f, 122.0f), RenderPivot::CENTER, float4(128.0f, 80.0f));

}

void Level1::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1_2");
	}
}