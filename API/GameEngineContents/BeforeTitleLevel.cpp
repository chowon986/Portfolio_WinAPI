#include "BeforeTitleLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "VideoPlayer.h"
#include <GameEngineBase/GameEngineWindow.h>

BeforeTitleLevel::BeforeTitleLevel()
	:BeforeTitleVideo_(nullptr)
{
}

BeforeTitleLevel::~BeforeTitleLevel()
{
}


void BeforeTitleLevel::Loading()
{

}

void BeforeTitleLevel::LevelChangeStart()
{
	BeforeTitleVideo_ = CreateActor<VideoPlayer>();
	BeforeTitleVideo_->SetInfo("intro_frame_", 0, 400, 30.0f);
	
}

void BeforeTitleLevel::Update()
{
	if (true == BeforeTitleVideo_->IsVideoFinished())
	{
			GameEngine::GetInst().ChangeLevel("Title");
	}
}