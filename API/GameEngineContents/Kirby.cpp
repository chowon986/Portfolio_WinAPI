#include "Kirby.h"
#include "BeforeTitleLevel.h"
#include "TitleLevel.h"
#include "IntroStory.h"
#include "Level1.h"
#include "Level1_2.h"
#include "Level1_3.h"
#include "Level1_4.h"
#include "Level2.h"
#include "Level2_2.h"
#include "Level2_3.h"
#include "Level2_4.h"
#include "Level3.h"
#include "Level3_2.h"
#include "Level3_3.h"
#include "Level4.h"
#include "Boss.h"
#include "Cannon.h"
#include "DanceStage.h"
#include "WorldMap.h"
#include "EndingLevel.h"
#include "EndingStory.h"
#include "GameOver.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>


Kirby::Kirby()
{
}

Kirby::~Kirby()
{
}

void Kirby::GameInit()
{
    GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 0, 0 }, { 768, 576 });

    {
        GameEngineDirectory ResourcesDir;
        ResourcesDir.MoveParent("API");
        ResourcesDir.Move("Resources");
        ResourcesDir.Move("Image");

        std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

        for (size_t i = 0; i < AllImageFileList.size(); i++)
        {
            GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
        }
    }

    //{
    //    GameEngineDirectory ResourcesDir;
    //    ResourcesDir.MoveParent("API");
    //    ResourcesDir.Move("Resources");
    //    ResourcesDir.Move("Sound");

    //    std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

    //    for (size_t i = 0; i < AllImageFileList.size(); i++)
    //    {
    //        GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
    //    }
    //}


    if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
    {
        GameEngineInput::GetInst()->CreateKey("LevelChange", VK_RETURN);
        GameEngineInput::GetInst()->CreateKey("Level1", '9');
    }

    CreateLevel<BeforeTitleLevel>("BeforeTitle");
    CreateLevel<TitleLevel>("Title");
    CreateLevel<IntroStory>("IntroStory");
    CreateLevel<Level1>("Level1");
    CreateLevel<Level1_2>("Level1_2");
    CreateLevel<Level1_3>("Level1_3");
    CreateLevel<Level1_4>("Level1_4");
    CreateLevel<Cannon>("Cannon");
    CreateLevel<DanceStage>("DanceStage");
    CreateLevel<WorldMap>("WorldMap");
    CreateLevel<Level2>("Level2");
    CreateLevel<Level2_2>("Level2_2");
    CreateLevel<Level2_3>("Level2_3");
    CreateLevel<Level2_4>("Level2_4");
    CreateLevel<Level3>("Level3");
    CreateLevel<Level3_2>("Level3_2");
    CreateLevel<Level3_3>("Level3_3");
    CreateLevel<Level4>("Level4");
    CreateLevel<Boss>("Boss");
    CreateLevel<EndingStory>("EndingStory");
    CreateLevel<EndingLevel>("Ending");
    CreateLevel<GameOver>("GameOver");

    ChangeLevel("Level1");

}

void Kirby::GameLoop()
{

}
void Kirby::GameEnd()
{

}