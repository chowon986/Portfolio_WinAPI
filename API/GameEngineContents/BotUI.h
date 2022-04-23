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
	GameEngineRenderer* PlayerHPMinus_;
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

