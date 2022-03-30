#include "Level1_2.h"
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

Level1_2::Level1_2()
{
}

Level1_2::~Level1_2()
{
}


void Level1_2::Loading()
{
	{

	}
}

void Level1_2::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1_3");
	}
}

void Level1_2::LevelChangeStart()
{
	Background* Stage1_2 = CreateActor<Background>((int)ORDER::BACKGROUND);
	Stage1_2->CreateRendererToScale("stage1_2.bmp", float4(1440.0f, 192.0f), RenderPivot::CENTER, float4(592.0f, 0.0f));

	//Monster* Box = CreateActor<Monster>((int)ORDER::MONSTER);
	////Box->CreateRendererToScale("Box.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f,120.0f ));

	//Monster* Fire = CreateActor<Monster>((int)ORDER::MONSTER);
	//Fire->CreateRendererToScale("Fire.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));

	//Monster* Boxes = CreateActor<Monster>((int)ORDER::MONSTER); // 1 * 5
	//Boxes->CreateRendererToScale("Boxes.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));

	//Monster* Brontobert = CreateActor<Monster>((int)ORDER::MONSTER);
	//Brontobert->CreateRendererToScale("Brontobert.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));

	//Monster* BigBox = CreateActor<Monster>((int)ORDER::MONSTER);
	//BigBox->CreateRendererToScale("BigBox.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));

	//Monster* Monster1 = CreateActor<Monster>((int)ORDER::MONSTER);
	//Monster1->CreateRendererToScale("Monster1.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));
}
