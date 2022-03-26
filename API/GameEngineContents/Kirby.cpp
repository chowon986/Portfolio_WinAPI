#include "Kirby.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "IntroStoryLevel.h"
#include "EndingStoryLevel.h"

#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>


Kirby::Kirby()
{
}

Kirby::~Kirby()
{
}

void Kirby::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({0, 0 }, { 1280, 720}); // 내 화면 크기는 1024,576

	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("Portfolio_WinAPI");
	ResourcesDir.Move("AllResources");

	// 모든 파일들을 가져와라(자식 경로까지는 찾지 않음)
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	CreateLevel<IntroStoryLevel>("IntroStory");
	ChangeLevel("Play");
	//ChangeLevel("Play");
}

void Kirby::GameLoop()
{

}
void Kirby::GameEnd()
{

}