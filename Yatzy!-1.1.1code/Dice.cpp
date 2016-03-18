#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Dice.h"
Dice::Dice(void)
{
	this->value = 1;
}
Dice::~Dice(void)
{

}
Dice& Dice::operator=(const Dice& obj)
{
	this->holdStatus = obj.holdStatus;
	this->value = obj.value;
	return *this;
}
void Dice::setRandomValueNr()
{
	this->value = rand() % 6 + 1;
}
const int Dice::getValueOfDice()
{
	return this->value;
}

void Dice::setHoldStatus(bool holdStatus)
{
	this->holdStatus = holdStatus;
}

const bool Dice::getHoldStatus()
{
	return this->holdStatus;
}