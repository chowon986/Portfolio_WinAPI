#pragma once
#include <GameEngine/GameEngineActor.h>

class Background : public GameEngineActor
{
public:
	Background();
	~Background();

	Background(const Background& _Other) = delete;
	Background(Background&& _Other) noexcept = delete;
	Background& operator=(const Background& _Other) = delete;
	Background& operator=(Background&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;
	
	
private:


};

