#include "Kirby.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
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
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	// ���� ����
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("Portfolio_WinAPI");
	ResourcesDir.Move("AllResources");

	// ��� ���ϵ��� �����Ͷ�(�ڽ� ��α����� ã�� ����)
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");
}

void Kirby::GameLoop()
{

}
void Kirby::GameEnd()
{

}