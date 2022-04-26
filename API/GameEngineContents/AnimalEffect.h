#pragma once
#include <GameEngine/GameEngineActor.h>

enum class AnimalEffectState
{
	AnimalEffectRight,
	AnimalEffectLeft,
	None,
};

class AnimalEffect : public GameEngineActor
{
public:
	AnimalEffect();
	~AnimalEffect();

	AnimalEffect(const AnimalEffect& _Other) = delete;
	AnimalEffect(AnimalEffect&& _Other) noexcept = delete;
	AnimalEffect& operator=(const AnimalEffect& _Other) = delete;
	AnimalEffect& operator=(AnimalEffect&& _Other) noexcept = delete;

public:
	void SetState(AnimalEffectState _AnimalEffectState);
	AnimalEffectState GetState();
private:
	void StateUpdate();
	void UpdateAnimalEffectRight();
	void UpdateAnimalEffectLeft();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	AnimalEffectState AnimalEffectState_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineImage* Image_;
};