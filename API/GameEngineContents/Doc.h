#pragma once
#include "Monster.h"

class Doc : public Monster
{
public:
	Doc();
	~Doc();

	Doc(const Doc& _Other) = delete;
	Doc(Doc&& _Other) noexcept = delete;
	Doc& operator=(const Doc& _Other) = delete;
	Doc& operator=(Doc&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
