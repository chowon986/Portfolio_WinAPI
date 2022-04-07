#include "Obstruction.h"

Obstruction::Obstruction()
	:HP_(1)
{
}

Obstruction::~Obstruction()
{
}

void Obstruction::SetHP(int _HP)
{
	HP_ = _HP;
}

int Obstruction::GetHP()
{
	return HP_;
}
