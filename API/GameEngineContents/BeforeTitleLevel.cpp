#include "BeforeTitleLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "VideoPlayer.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>


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


void BeforeTitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BeforeTitleVideo_ = CreateActor<VideoPlayer>();
	BeforeTitleVideo_->SetInfo("intro_frame_", 0, 400, 30.0f);

	BgmPlayer = GameEngineSound::SoundPlayControl("BeforeTitle.mp3");
}


void BeforeTitleLevel::Update()
{
	if (true == BeforeTitleVideo_->IsVideoFinished())
	{
		BgmPlayer.Stop();
		GameEngine::GetInst().ChangeLevel("Title");
	}
	if (0 >= GetCameraPos().x)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = 0;
		SetCameraPos(CurCameraPos);
	}

	if (0 >= GetCameraPos().y)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = 0;
		SetCameraPos(CurCameraPos);
	}

	float CameraRectX = 768;
	float CameraRectY = 576;

	if (GetMapSizeX() <= GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = static_cast<int>(GetCameraPos().ix() - (GetCameraPos().ix() + CameraRectX - GetMapSizeX()));
		SetCameraPos(CurCameraPos);
	}

	if (GetMapSizeY() <= GetCameraPos().y + CameraRectY)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = static_cast<int>(GetCameraPos().iy() - (GetCameraPos().iy() + CameraRectY - GetMapSizeY()));
		SetCameraPos(CurCameraPos);
	}
}