#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	game.runGame();
	/*while (gameStatusCheck > 0)
	{ 
		gameStatusCheck = game.menu();
		switch (gameStatusCheck)
		{
		case 1:
			if (game.initializePlayers())
			{
				if (game.playGame())
				{
					if (game.getWinner())
					{
						gameStatusCheck = 10;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					gameStatusCheck = 0;
				}

			}
			else
			{
				gameStatusCheck = 0;
			}
		break;
	case 2:
		if (game.showHighscores())
			;
		else
			gameStatusCheck = 0;
		break;
	default:
		break;
		}
	}*/
	return 0;
}



