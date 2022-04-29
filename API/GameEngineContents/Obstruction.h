#pragma once
#include "GameEngine/GameEngineActor.h"

class Player;
class GameEngineRenderer;
class GameEngineCollision;
class Obstruction : public GameEngineActor
{
public:
	Obstruction();
	~Obstruction();
	Obstruction(const Obstruction& _Other) = delete;
	Obstruction(Obstruction&& _Other) noexcept = delete;
	Obstruction& operator=(const Obstruction& _Other) = delete;
	Obstruction& operator=(Obstruction&& _Other) noexcept = delete;

public:
	void SetPlayer(Player* _Player) { Player_ = _Player; }
	Player* GetPlayer() { return Player_; }
	void Start();
	void Update();
private:

protected:
	virtual void ColUpdate();
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	Player* Player_;
};

