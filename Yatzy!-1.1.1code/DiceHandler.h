#pragma once
#include "Dice.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
class DiceHandler
{
	int nrOfDices=5;
	Dice dice[5];
public:
	DiceHandler(void);
	virtual ~DiceHandler(void);
	DiceHandler& operator=(const DiceHandler& obj);
	void throwDice();
	void resetDice();
	int *getDiceValueArray(size_t);
	void setDiceForHolding(const int diceNr);
	const int getNrOfDice();
	const bool getIfDiceIsHold(int diceNr);
};