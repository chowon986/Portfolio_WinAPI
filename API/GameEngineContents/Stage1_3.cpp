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
		Background* Stage1_2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_2->CreateRendererToScale("stage1_3.bmp", float4(256.0f, 384.0f), RenderPivot::CENTER, float4(0.0f, -96.0f));

		CreateActor<Player>((int)ORDER::PLAYER);

		//Monster* Box = CreateActor<Monster>((int)ORDER::MONSTER);
		//Box->CreateRendererToScale("Box.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f,120.0f ));

		//Monster* Fire = CreateActor<Monster>((int)ORDER::MONSTER);
		//Fire->CreateRendererToScale("Fire.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));
		//Monster* Tomato = CreateActor<Monster>((int)ORDER::MONSTER);
		//Tomato->CreateRendererToScale("Tomato.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));
		//Monster* Waddledi = CreateActor<Monster>((int)ORDER::MONSTER);
		//Waddledi->CreateRendererToScale("Waddledi.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));
		//Monster* Monster1 = CreateActor<Monster>((int)ORDER::MONSTER);
		//Monster1->CreateRendererToScale("Monster1.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));
		//Monster* Bomb = CreateActor<Monster>((int)ORDER::MONSTER);
		//Bomb->CreateRendererToScale("Bomb.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));
		//Monster* Boxes2 = CreateActor<Monster>((int)ORDER::MONSTER); // 5x5
		//Boxes2->CreateRendererToScale("Boxes2.bmp", float4(130.0f, 24.0f), RenderPivot::CENTER, float4(128.0f, 120.0f));

	}
}

void Level1_2::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1_4");
	}
}