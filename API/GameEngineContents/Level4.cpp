#include "Level4.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Waddledi.h"
#include "Background.h"
#include "ContentsEnum.h"

Level4::Level4()
{
}

Level4::~Level4()
{
}


void Level4::Loading()
{
	// Ŀ��
	// ������Ÿ
	CreateActor<Background>((int)ORDER::BACKGROUND);
	CreateActor<Background>((int)ORDER::BACKGROUND);
	CreateActor<Waddledi>((int)ORDER::MONSTER);

}

void Level4::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Boss");
	}
}