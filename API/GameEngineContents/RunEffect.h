#pragma once
#include <GameEngine/GameEngineActor.h>

enum class RunEffectState
{
	RunEffectRight,
	RunEffectLeft,
	None,
};

class RunEffect : public GameEngineActor
{
public:
	RunEffect();
	~RunEffect();

	RunEffect(const RunEffect& _Other) = delete;
	RunEffect(RunEffect&& _Other) noexcept = delete;
	RunEffect& operator=(const RunEffect& _Other) = delete;
	RunEffect& operator=(RunEffect&& _Other) noexcept = delete;

public:
	void SetState(RunEffectState _RunEffectState);
	RunEffectState GetState();
private:
	void StateUpdate();
	void UpdateRunEffectRight();
	void UpdateRunEffectLeft();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	RunEffectState RunEffectState_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineImage* Image_;
};