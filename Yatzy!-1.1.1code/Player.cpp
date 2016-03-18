#include "Player.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;
Player::Player(void)
{

	this->name = "Player";
	
}
Player::~Player(void)
{

}
void Player::operator=(const Player &org)
{
	this->name = org.name;
}
void Player::setName(string name)
{
	this->name = name;
}
const string Player::getName()
{
	return this->name;
}
