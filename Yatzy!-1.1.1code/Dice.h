#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;
class Dice
{
	int value;
	bool holdStatus;
public:
	Dice(void);
	virtual ~Dice(void);
	Dice& operator=(const Dice& obj);
	void setRandomValueNr();
	const int getValueOfDice();
	void setHoldStatus(const bool holdStatus);
	const bool getHoldStatus();
};