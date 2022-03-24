#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineMath.h"
#include "GameEngineDebug.h"

class GameEngineWindow
{
private:
	static GameEngineWindow* Inst_; 

public:
	// 싱글톤 : 단 한개만 만들 수 있다.
	// 생성자, 멤버 변수가 private이기 때문에 생성 불가
	inline static GameEngineWindow& GetInst()
	{
		return *Inst_; // 값
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	void RegClass(HINSTANCE _hInst); // window 생성을 위한 기본 설정
	void CreateGameWindow(HINSTANCE _hInst, const std::string& _Title); // window 생성
	void ShowGameWindow(); // 생성된 window 표출
	void MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)());

	void SetWindowScaleAndPosition(float4 _Pos, float4 _Scale);

	void Off();

	static inline HDC GetHDC()
	{
		return Inst_->HDC_;
	}

	static inline float4 GetScale()
	{
		return Inst_->Scale_;
	}


protected:

private:
	std::string Title_;
	bool WindowOn_;
	HINSTANCE hInst_;
	HWND hWnd_;
	HDC HDC_;
	float4 Scale_;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

};

