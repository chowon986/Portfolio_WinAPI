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

	void DelayOff();

protected:

private:
	void Start() override;
	void Render() override;
	void Update() override;

	float DelayTime_;
	float ElapsedTime_;
	GameEngineRenderer* HP_;
	GameEngineRenderer* BossHP_;


	GameEngineRenderer* MonsterUI_;
	GameEngineRenderer* MonsterHP_;
	GameEngineRenderer* MonsterHPCount1_;
	GameEngineRenderer* MonsterHPCount2_;
	GameEngineRenderer* HPNumberLeft_;
	GameEngineRenderer* HPNumberRight_;
	GameEngineImage* HPCountNum_;
	Monster* Monster_;
	
	bool PendingOff_;
public:
	void SetMonster(Monster* _Monster) { Monster_ = _Monster; }
};

