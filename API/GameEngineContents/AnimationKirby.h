#pragma once
#include <GameEngine/GameEngineActor.h>
#include "CharacterBase.h"
#include <string>
#include <GameEngineBase/GameEngineSound.h>

enum class AnimationKirbyClass
{
	DANCE,
	STAR,
};

class AnimationKirby : public CharacterBase
{

public:
	AnimationKirby();
	~AnimationKirby();

	AnimationKirby(const AnimationKirby& _Other) = delete;
	AnimationKirby(AnimationKirby&& _Other) noexcept = delete;
	AnimationKirby& operator=(const AnimationKirby& _Other) = delete;
	AnimationKirby& operator=(AnimationKirby&& _Other) noexcept = delete;
	
public:
	void SetAnimationKirbyClass(AnimationKirbyClass _Class);
	AnimationKirbyClass GetClass();
	GameEngineRenderer* GetRenderer();
	void ClassUpdate();
protected:

private:
	GameEngineRenderer* DanceRenderer_;
	GameEngineRenderer* StarRenderer_;
	GameEngineRenderer* WorldMapRenderer_;
	GameEngineCollision* StarCol_;
	GameEngineImage* DanceImage_;
	GameEngineImage* StarImage_;
	GameEngineImage* WorldMapImage_;

	GameEngineImage* ColMapImage_;
	GameEngineLevel* Level_;
	AnimationKirbyClass Class_;
	float4 StartPos_;
	float4 Dir_;
	float Speed_;
	float Time_;


	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	void CheckCollision();

	void UpdateDance();
	void UpdateStar();
};
