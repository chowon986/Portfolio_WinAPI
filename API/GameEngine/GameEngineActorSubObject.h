#pragma once
#include <GameEngine/GameEngineActor.h>

// 엑터가 먼저 -> 랜더러가 그 다음
class GameEngineActorSubObject 
{
	friend GameEngineActor;

public:
	// constrcuter destructer
	GameEngineActorSubObject();
	virtual ~GameEngineActorSubObject();// vitual로 만들었으면 상속을 하겠다는거에요

	// delete Function
	GameEngineActorSubObject(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject(GameEngineActorSubObject&& _Other) noexcept = delete;
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject& operator=(GameEngineActorSubObject&& _Other) noexcept = delete;

	inline GameEngineActor* GetActor()
	{
		return Actor_;
	}

protected:
	inline void SetActor(GameEngineActor* _Actor)
	{
		Actor_ = _Actor;
	}
	

private:
	GameEngineActor* Actor_;

};

