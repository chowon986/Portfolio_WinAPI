#include "Kirby.h"
#include "BeforeTitleLevel.h"
#include "TitleLevel.h"
#include "IntroStory.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Boss.h"
#include "Cannon.h"
#include "DanceStage.h"
#include "WorldMap.h"
#include "EndingLevel.h"
#include "EndingStory.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>


Kirby::Kirby()
{
}

Kirby::~Kirby()
{
}

void Kirby::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({0, 0 }, { 1280, 720}); // �� ȭ�� ũ��� 1024,576

	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("Portfolio_WinAPI");
	ResourcesDir.Move("AllResources");

	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("Level1", '1');
		GameEngineInput::GetInst()->CreateKey("Level2", '2');
		GameEngineInput::GetInst()->CreateKey("Level3", '3');
		GameEngineInput::GetInst()->CreateKey("Level4", '4');
		GameEngineInput::GetInst()->CreateKey("Boss", '5');
	}

	CreateLevel<BeforeTitleLevel>("BeforeTitle");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<IntroStory>("IntroStory");
	CreateLevel<Level1>("Level1");
	CreateLevel<Cannon>("Cannon");
	CreateLevel<DanceStage>("DanceStage");
	CreateLevel<WorldMap>("WorldMap");
	CreateLevel<Level2>("Level2");
	CreateLevel<Level3>("Level3");
	CreateLevel<Level4>("Level4");
	CreateLevel<Boss>("Boss");
	CreateLevel<EndingStory>("EndingStory");
	CreateLevel<EndingLevel>("Ending");

	ChangeLevel("BeforeTitle");

}

void Kirby::GameLoop()
{

}
void Kirby::GameEnd()
{

}