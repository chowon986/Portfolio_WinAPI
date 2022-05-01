#pragma once
#include <GameEngine/GameEngineActor.h>

enum class AttackEffectState
{
	AttackEffectRight,
	AttackEffectLeft,
	None,
};

class GameEngineImage;
class AttackEffect : public GameEngineActor
{
public:
	AttackEffect();
	~AttackEffect();

	AttackEffect(const AttackEffect& _Other) = delete;
	AttackEffect(AttackEffect&& _Other) noexcept = delete;
	AttackEffect& operator=(const AttackEffect& _Other) = delete;
	AttackEffect& operator=(AttackEffect&& _Other) noexcept = delete;

public:
	void SetState(AttackEffectState _AttackEffectState);
	AttackEffectState GetState();
private:
	void StateUpdate();
	void UpdateAttackEffectRight();
	void UpdateAttackEffectLeft();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	AttackEffectState AttackEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineImage* Image_;
};