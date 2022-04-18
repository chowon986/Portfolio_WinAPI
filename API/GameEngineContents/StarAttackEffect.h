#pragma once
#include <GameEngine/GameEngineActor.h>

enum class StarAttackEffectState
{
	AttackStartRight,
	AttackStartLeft,
	AttackEndRight,
	AttackEndLeft,
	None,
};

class StarAttackEffect : public GameEngineActor
{
public:
	StarAttackEffect();
	~StarAttackEffect();

	StarAttackEffect(const StarAttackEffect& _Other) = delete;
	StarAttackEffect(StarAttackEffect&& _Other) noexcept = delete;
	StarAttackEffect& operator=(const StarAttackEffect& _Other) = delete;
	StarAttackEffect& operator=(StarAttackEffect&& _Other) noexcept = delete;

public:
	void SetState(StarAttackEffectState _StarAttackEffectState);
	StarAttackEffectState GetState();
private:
	void StateUpdate();

	void UpdateAttackStartRight();
	void UpdateAttackStartLeft();
	void UpdateAttackEndRight();
	void UpdateAttackEndLeft();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	StarAttackEffectState StarAttackEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
};