#include "Level1.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Waddledi.h"
#include "Waddledu.h"
#include "Sparky.h"
#include "Box.h"
#include "Fire.h"
#include "Brontobert.h"
#include "BigBox.h"
#include "Monster1.h"
#include "Tomato.h"
#include "Bomb.h"
#include "Background.h"
#include "ContentsEnum.h"

Level1::Level1()
{
}

Level1::~Level1()
{
}


void Level1::Loading()
{
	//Ä¿ºñ
	Background* Back = CreateActor<Background>((int)ORDER::BACKGROUND);

	CreateActor<Player>((int)ORDER::PLAYER); 
	CreateActor<Waddledi>((int)ORDER::MONSTER);
	CreateActor<Waddledu>((int)ORDER::MONSTER);
	CreateActor<Sparky>((int)ORDER::MONSTER);
	////////////////////////////
	CreateActor<Background>((int)ORDER::BACKGROUND);
	CreateActor<Box>((int)ORDER::MONSTER);
	CreateActor<Fire>((int)ORDER::MONSTER);
	CreateActor<Box>((int)ORDER::MONSTER); // 1 x 5
	CreateActor<Brontobert>((int)ORDER::MONSTER);
	CreateActor<BigBox>((int)ORDER::MONSTER);
	CreateActor<Monster1>((int)ORDER::MONSTER);
	//////////////////////////
	CreateActor<Box>((int)ORDER::MONSTER);
	CreateActor<Fire>((int)ORDER::MONSTER);
	CreateActor<Tomato>((int)ORDER::MONSTER);
	CreateActor<Waddledi>((int)ORDER::MONSTER);
	CreateActor<Monster1>((int)ORDER::MONSTER);
	CreateActor<Bomb>((int)ORDER::MONSTER);
	CreateActor<Box>((int)ORDER::MONSTER); // 5 x 5
}

void Level1::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Cannon");
	}
}