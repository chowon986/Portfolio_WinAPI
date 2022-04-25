#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Player.h"

// Ό³Έν :
class GameEngineRenderer;
class GameEngineImage;
class Player;
enum class KirbyClass;
class BotUI : public GameEngineActor
{
public:
	// constrcuter destructer
	BotUI();
	~BotUI();

	// delete Function
	BotUI(const BotUI& _Other) = delete;
	BotUI(BotUI&& _Other) noexcept = delete;
	BotUI& operator=(const BotUI& _Other) = delete;
	BotUI& operator=(BotUI&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Render() override;
	void Update() override;

	float MinusHP_;
	GameEngineRenderer* HP10_;
	GameEngineRenderer* HP9_;
	GameEngineRenderer* HP8_;
	GameEngineRenderer* HP7_;
	GameEngineRenderer* HP6_;
	GameEngineRenderer* HP5_;
	GameEngineRenderer* HP4_;
	GameEngineRenderer* HP3_;
	GameEngineRenderer* HP2_;
	GameEngineRenderer* HP1_;
	GameEngineRenderer* HP0_;

	GameEngineRenderer* PlayerUI_;
	GameEngineRenderer* PlayerHP_;
	GameEngineRenderer* PlayerHPCount1_;
	GameEngineRenderer* PlayerHPCount2_;
	GameEngineRenderer* HPNumberLeft_;
	GameEngineRenderer* HPNumberRight_;
	GameEngineImage* PlayerHPCountNum_;
	Player* Player_;
public:
	void SetPlayer(Player* _Player) { Player_ = _Player; }
};

