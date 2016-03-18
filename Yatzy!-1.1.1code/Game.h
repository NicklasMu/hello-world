#pragma once
#include <iostream>
#include <stdlib.h>
#include "DiceHandler.h"
#include "PlayerHandler.h"
#include "ScoreBoard.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;

class Game
{
	PlayerHandler ph;
	DiceHandler dh;
	ScoreBoard *scoreBoards;
	int currentRound;
	int nrOfThrowsLeft;
	sf::RenderWindow window;
public:
	Game();
	~Game();
	Game(const Game &obj);
	Game& operator=(const Game& obj);
	sf::Font getFont();
	void drawMenuButton();
	void drawContinueButton();
	void runGame();
	const int getCurrentRound();
	int menu();
	bool playGame();
	const int initializeNumberOfPlayers();
	bool initializePlayers(int nrOfPlayers);
	bool showHighscores();
	bool getWinner();
	void saveToHighScore(int playerScoreList[]);
};