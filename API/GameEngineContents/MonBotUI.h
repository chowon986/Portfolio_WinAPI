#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Monster.h"

class GameEngineRenderer;
class GameEngineImage;
class Monster;
class MonBotUI : public GameEngineActor
{
public:
	// constrcuter destructer
	MonBotUI();
	~MonBotUI();

	// delete Function
	MonBotUI(const MonBotUI& _Other) = delete;
	MonBotUI(MonBotUI&& _Other) noexcept = delete;
	MonBotUI& operator=(const MonBotUI& _Other) = delete;
	MonBotUI& operator=(MonBotUI&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Render() override;
	void Update() override;

	float MinusHP_;
	GameEngineRenderer* HP2_;
	GameEngineRenderer* HP1_;
	GameEngineRenderer* HP0_;

	GameEngineRenderer* BossHP10_;
	GameEngineRenderer* BossHP9_;
	GameEngineRenderer* BossHP8_;
	GameEngineRenderer* BossHP7_;
	GameEngineRenderer* BossHP6_;
	GameEngineRenderer* BossHP5_;
	GameEngineRenderer* BossHP4_;
	GameEngineRenderer* BossHP3_;
	GameEngineRenderer* BossHP2_;
	GameEngineRenderer* BossHP1_;
	GameEngineRenderer* BossHP0_;


	GameEngineRenderer* MonsterUI_;
	GameEngineRenderer* MonsterHP_;
	GameEngineRenderer* MonsterHPCount1_;
	GameEngineRenderer* MonsterHPCount2_;
	GameEngineRenderer* HPNumberLeft_;
	GameEngineRenderer* HPNumberRight_;
	GameEngineImage* HPCountNum_;
	Monster* Monster_;
public:
	void SetMonster(Monster* _Monster) { Monster_ = _Monster; }
};

