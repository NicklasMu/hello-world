#include "PlayerHandler.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
PlayerHandler::PlayerHandler(void)
{
	this->nrOfPlayers = 0;
	this->currentPlayer = 0;
	this->players = new Player[this->nrOfPlayers];
}
PlayerHandler::~PlayerHandler()
{
	delete[] players;
}
PlayerHandler::PlayerHandler(const PlayerHandler &obj)
{
	this->nrOfPlayers = obj.nrOfPlayers;
	this->players = new Player[this->nrOfPlayers];
	for (int k = 0; k < this->nrOfPlayers; k++)
	{
		this->players[k] = obj.players[k];
	}

}
PlayerHandler& PlayerHandler::operator=(const PlayerHandler& obj)
{
	if (&obj == this)
		return *this;
	this->nrOfPlayers = obj.nrOfPlayers;
	this->currentPlayer = obj.currentPlayer;
	delete[] this->players;
	this->players = new Player[this->nrOfPlayers];
	for (int k = 0; k < this->nrOfPlayers; k ++)
	{
		this->players[k] = obj.players[k];
	}
	return *this;
}
const string PlayerHandler::getCurrentPlayerName()
{
	string currentPlayerName;
	currentPlayerName = this->players[this->currentPlayer].getName();
	return currentPlayerName;
}
const int PlayerHandler::getNrOfPlayers()
{
	return this->nrOfPlayers;
}

const int PlayerHandler::getCurrentPlayer()
{
	return this->currentPlayer;
}

void PlayerHandler::changePlayer()
{
	this->currentPlayer = this->currentPlayer + 1;
	if (this->currentPlayer == this->nrOfPlayers)
		this->currentPlayer = 0;
}

void PlayerHandler::addPlayers(const int nrOfPlayers, string names[])
{
	if (this->nrOfPlayers > 0)
	{
		delete[] players;
		this->nrOfPlayers = nrOfPlayers;
		this->players = new Player[nrOfPlayers];
		for (int k = 0; k < nrOfPlayers; k++)
		{
			this->players[k].setName(names[k]);
		}
		this->currentPlayer = 0;
	}
	else
	{
		delete[] players;
		this->nrOfPlayers = nrOfPlayers;
		this->players = new Player[nrOfPlayers];
		for (int k = 0; k < nrOfPlayers; k++)
		{
			this->players[k].setName(names[k]);
		}
	}
}

const string PlayerHandler::getPlayerNameByPos(int pos)
{
	string playerNameByPosReturn;
	playerNameByPosReturn = this->players[pos].getName();
	return playerNameByPosReturn;
}

void PlayerHandler::setPlayerNameByPos(const int pos, const string name)
{
	for (int k = 0; k < this->nrOfPlayers; k++)
	{
		if (k == pos)
		{
			this->players[k].setName(name);
		}
	}
}
