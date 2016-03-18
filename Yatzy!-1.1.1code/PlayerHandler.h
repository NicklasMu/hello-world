#pragma once
#include "Player.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
class PlayerHandler
{
	int nrOfPlayers;
	int currentPlayer;
	Player *players;
public:
	PlayerHandler();
	~PlayerHandler();
	PlayerHandler(const PlayerHandler &obj);
	PlayerHandler& operator=(const PlayerHandler& other);
	const string getCurrentPlayerName();
	const int getNrOfPlayers();
	const int getCurrentPlayer();
	void changePlayer();
	void addPlayers(const int nrOfPlayers, string names[]);
	const string getPlayerNameByPos(int pos);
	void setPlayerNameByPos(const int pos, const string name);
};
