#pragma once
#include <GameEngine/GameEngineLevel.h>
//#include <GameEngineBase/GameEngineSound.h>

class Player;
class BotUI;
class GameEngineCollision;
class GameEngineImage;
class Level1 : public GameEngineLevel
{
public:
	Level1();
	~Level1();

	Level1(const Level1& _Other) = delete;
	Level1(Level1&& _Other) noexcept = delete;
	Level1& operator=(const Level1& _Other) = delete;
	Level1& operator=(Level1&& _Other) noexcept = delete;



protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	Player* Star_;
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* DoorCol1_2;
	GameEngineImage* ColMapImage_;
	float4 StartPos_;
	//GameEngineSoundPlayer BgmPlayer;


private:
};

