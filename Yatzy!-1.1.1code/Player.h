#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;
class Player
{
	string name;
public:
	Player(void);
	virtual ~Player(void);
	void operator=(const Player &org);
	void setName(const string);
	const string getName();

};
