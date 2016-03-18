#include "DiceHandler.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
DiceHandler::DiceHandler(void)
{
	srand(time(NULL));
	for (int k = 0; k < this->nrOfDices; k++)
	{
		if(!dice[k].getHoldStatus())
		dice[k].setRandomValueNr();
	}
}
DiceHandler::~DiceHandler(void)
{
}
DiceHandler& DiceHandler::operator=(const DiceHandler& obj)
{
	for (int k = 0; k < 5; k++)
	{
		this->dice[k] = obj.dice[k];
	}
	return *this;
}
void DiceHandler::throwDice()
{
	for (int k = 0; k<this->nrOfDices; k++)
	{
		if (!dice[k].getHoldStatus())
		dice[k].setRandomValueNr();
	}
}
void DiceHandler::resetDice()
{
	for (int k = 0; k < this->nrOfDices; k++)
	{
		dice[k].setHoldStatus(false);
	}
}

int * DiceHandler::getDiceValueArray(size_t)
{
	int *diceValues = new int[5];
	for (int k = 0; k<this->nrOfDices; k++)
	{
		diceValues[k] = this->dice[k].getValueOfDice();
	}
	return diceValues;
}

void DiceHandler::setDiceForHolding(int diceNr)
{
	for (int k = 0; k < this->nrOfDices; k++)
	{
		if (k == diceNr) 
		{
			if (dice[k].getHoldStatus())
				dice[k].setHoldStatus(false);
			else
				dice[k].setHoldStatus(true);
		}
	}
}

const int DiceHandler::getNrOfDice()
{
	return this->nrOfDices;
}

const bool DiceHandler::getIfDiceIsHold(int diceNr)
{
	bool holdStatusReturn;
	for (int k = 0; k < this->nrOfDices; k++)
	{
		if (k == diceNr)
		{
			holdStatusReturn = dice[k].getHoldStatus();
		}
	}
	return holdStatusReturn;
}