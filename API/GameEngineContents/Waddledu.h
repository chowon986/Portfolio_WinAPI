#pragma once
#include "Monster.h"

class Waddledu : public Monster
{
public:
	Waddledu();
	~Waddledu();

	Waddledu(const Waddledu& _Other) = delete;
	Waddledu(Waddledu&& _Other) noexcept = delete;
	Waddledu& operator=(const Waddledu& _Other) = delete;
	Waddledu& operator=(Waddledu&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};