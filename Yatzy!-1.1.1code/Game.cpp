#include "Game.h"
#include <sstream>

Game::Game()
{
	this->scoreBoards = new ScoreBoard[0];
	this->nrOfThrowsLeft = 3;
	this->currentRound = 0;
}

Game::~Game()
{
	delete[] scoreBoards;
}

Game::Game(const Game &obj)
{
	this->ph = obj.ph;
	this->dh = obj.dh;
	this->scoreBoards = new ScoreBoard[this->ph.getNrOfPlayers()];
	for (int k = 0; k > this->ph.getNrOfPlayers(); k++)
	{
		this->scoreBoards[k] = obj.scoreBoards[k];
	}
}

Game& Game::operator=(const Game& obj)
{
	if (&obj == this)
		return *this;

	this->ph = obj.ph;
	this->dh = obj.dh;
	delete[] this->scoreBoards;
	this->scoreBoards = new ScoreBoard[this->ph.getNrOfPlayers()];
	for (int k = 0; k > this->ph.getNrOfPlayers(); k++)
	{
		this->scoreBoards[k] = obj.scoreBoards[k];
	}
	return *this;
}

void Game::drawMenuButton()
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{

	}
	sf::RectangleShape menuButton(sf::Vector2f(100, 50));
	menuButton.setPosition(700, 0);
	menuButton.setFillColor(sf::Color(168, 168, 168));
	sf::Text menuButtonText;
	menuButtonText.setString("Menu");
	menuButtonText.setFont(font);
	menuButtonText.setColor(sf::Color::Black);
	menuButtonText.setCharacterSize(24);
	menuButtonText.setPosition(710, 15);
	this->window.draw(menuButton);
	this->window.draw(menuButtonText);
}

void Game::drawContinueButton()
{
	sf::Text continueButtonText;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{

	}
	continueButtonText.setFont(font);
	continueButtonText.setColor(sf::Color::Black);
	continueButtonText.setCharacterSize(24);
	continueButtonText.setString("Continue");
	continueButtonText.setPosition(610, 500);
	sf::RectangleShape continueButton(sf::Vector2f(120, 50));
	continueButton.setPosition(610, 500);
	this->window.draw(continueButton);
	this->window.draw(continueButtonText);
}
void Game::runGame()
{
	int currentGameStatus = 10;
	int nrOfPlayers=0;
	this->window.create(sf::VideoMode(800, 600), "Yatzy!", sf::Style::Titlebar);
	while (currentGameStatus > 0)
	{
		currentGameStatus = menu();
		switch (currentGameStatus)
		{
		case 1:
			nrOfPlayers = initializeNumberOfPlayers();
			if (nrOfPlayers > 0)
			{
				if (initializePlayers(nrOfPlayers))
				{
					if (playGame())
					{
						if (getWinner())
						{
							currentGameStatus = 10;
						}
						/*else
						{
							return 0;
						}*/
					}
					else
					{
						currentGameStatus = 10;
					}

				}
				else
				{
					currentGameStatus = 10;
				}
			}
			break;
		case 2:
			if (showHighscores())
				;
			else
				currentGameStatus = 0;
			break;
		case 3:
			currentGameStatus = 0;
			break;
		default:
			break;
		}
	}

}

const int Game::getCurrentRound()
{
	return this->currentRound;
}

//Visar en meny grafiskt där den returnerar en integer vars värde
//baseras på vilket objekt användaren klickar på
int Game::menu()
{
	this->window.clear();
	sf::Texture background;
	background.loadFromFile("background1.png");
	sf::Sprite sprite;
	sprite.setTexture(background);
	sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{

	}
	sf::Text titleText;
	titleText.setString("Yatzy!");
	titleText.setFont(font);
	titleText.setColor(sf::Color::White);
	titleText.setCharacterSize(48);
	titleText.setPosition(350, 50);
	sf::RectangleShape menuButton[3];
	for (int k = 0; k < 3; k++)
	{
		menuButton[k].setSize(sf::Vector2f(200, 100));
		menuButton[k].setPosition(300, 150 + k * 150);
		menuButton[k].setFillColor(sf::Color(168, 168, 168));
	}
	sf::Text menuButtonText[3];
	menuButtonText[0].setString("Play Game");
	menuButtonText[1].setString("High Scores");
	menuButtonText[2].setString("Exit Game");
	for (int k = 0; k < 3; k++)
	{
		menuButtonText[k].setFont(font);
		menuButtonText[k].setColor(sf::Color::Black);
		menuButtonText[k].setCharacterSize(28);
		menuButtonText[k].setPosition(325, 175 + k * 150);
	}


	while (this->window.isOpen())
	{
		int mx = 0;
		int my = 0;
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				return 0;
				this->window.close();
				break;
			case sf::Event::MouseButtonReleased:
				mx = sf::Mouse::getPosition(this->window).x;
				my = sf::Mouse::getPosition(this->window).y;
				for (int k = 0; k < 3; k++)
				{
					if (mx > 300 && mx < 500 && my >  150 + k * 150 && my <  250 + k * 150)
					{
						this->window.clear();
						return k+1;
					}
				}
				break;
			default:
				break;
			}
		}
		this->window.clear();
		this->window.draw(sprite);
		this->window.draw(titleText);
		for (int k = 0; k < 3; k++)
		{
			this->window.draw(menuButton[k]);
		}
		for (int k = 0; k < 3; k++)
		{
			this->window.draw(menuButtonText[k]);
		}
		this->window.display();
	}
	return 0;
}
//Funktionen som hanterar sjävla spelet efter spelare har skapats
bool Game::playGame()
{
	this->window.clear();
	int *diceValues = dh.getDiceValueArray(5);
	int mx;
	int my;
	bool scoreAdded = false;
	sf::Texture background;
	background.loadFromFile("background1.png");
	sf::Sprite sprite;
	sprite.setTexture(background);
	sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	sf::Font font;
	sf::String str;
	sf::Text text;
	sf::Text playerNameText;
	sf::Text scoreText[16];
	sf::Text scoreBoardDescription[16];
	sf::String stringSBD[16] = { "Ones","Twos","Threes","Fours","Fives",
		"Sixes","Bonus","Pairs","Two Pairs","Three-in-A-Row","Four-In-A-Row",
		"Small Straight","Big Straight","Full House","Chance","Yazy" };

	if (!font.loadFromFile("arial.ttf"))
	{

	}
	for (int k = 0; k < 16; k++)
	{
		scoreBoardDescription[k].setString(stringSBD[k]);
		scoreBoardDescription[k].setFont(font);
		scoreBoardDescription[k].setColor(sf::Color::White);
		scoreBoardDescription[k].setCharacterSize(16);
		scoreBoardDescription[k].setPosition(105, 100 + k * 30);
	}
	playerNameText.setPosition(300, 175);
	playerNameText.setFont(font);
	playerNameText.setColor(sf::Color::White);
	playerNameText.setCharacterSize(48);
	sf::RenderWindow window;
	sf::RectangleShape scoreBoardShapes[16];
	for (int k = 0; k < 16; k++)
	{
		scoreBoardShapes[k].setSize(sf::Vector2f(50, 30));
		scoreBoardShapes[k].setPosition(50, 100 + k * 30);
		scoreBoardShapes[k].setOutlineThickness(1);
		scoreBoardShapes[k].setOutlineColor(sf::Color(168, 168, 168));
	}
	sf::Text scoreValueText[16];
	for (int k = 0; k < 16; k++)
	{
		scoreValueText[k].setFont(font);
		scoreValueText[k].setColor(sf::Color::Black);
		scoreValueText[k].setCharacterSize(24);
		scoreValueText[k].setPosition(50, 100 + k * 30);
		scoreValueText[k].setString("");
	}
	sf::Texture texture;
	if (!texture.loadFromFile("diceTexture.png"))
	{
		// error...
	}
	sf::RectangleShape dicesShapes[5];
	for (int k = 0; k < 5; k++)
	{
		dicesShapes[k].setSize(sf::Vector2f(50, 50));
		dicesShapes[k].setPosition(350 + k * 75, 300);
		dicesShapes[k].setFillColor(sf::Color(168, 168, 168));
		dicesShapes[k].setTexture(&texture);
		dicesShapes[k].setTextureRect(sf::IntRect(557*(diceValues[k]-1), 0, 557, 557));
	}
	sf::RectangleShape diceHolderPointer[5];
	for (int k = 0; k < 5; k++)
	{
		diceHolderPointer[k].setSize(sf::Vector2f(10, 10));
		diceHolderPointer[k].setPosition(370 + k * 75, 280);
		diceHolderPointer[k].setFillColor(sf::Color(250, 250, 0));
	}
	sf::RectangleShape throwDices(sf::Vector2f(120, 50));
	throwDices.setPosition(400, 500);
	sf::Text throwDiceButtonText;
	sf::Text throwText;
	throwDiceButtonText.setFont(font);
	throwDiceButtonText.setColor(sf::Color::Black);
	throwDiceButtonText.setCharacterSize(24);
	throwDiceButtonText.setPosition(410, 500);
	throwDiceButtonText.setString("Throw");
	throwText.setFont(font);
	throwText.setColor(sf::Color::White);
	throwText.setCharacterSize(24);
	throwText.setPosition(400, 470);
	string result;
	text.setFont(font);
	text.setColor(sf::Color::Red);
	text.setCharacterSize(24);
	while (this->window.isOpen())
	{
		int checkScoreValue = 0;
		string stringName = ph.getCurrentPlayerName();
		playerNameText.setString(stringName);
		string stringThrowText = "Number of Throws Left: ";
		ostringstream convert;
		convert << this->nrOfThrowsLeft;
		result = convert.str();
		stringThrowText += (result);
		throwText.setString(stringThrowText);
		string scoringString="";
		ostringstream convertScore[16];
		for (int k = 0; k < 16; k++)	//Kollar igenom vilka värden som ska visas i poängrutorna
		{
			checkScoreValue = scoreBoards[ph.getCurrentPlayer()].getScore(k);
			if (checkScoreValue > 0)
			{
				convertScore[k] << scoreBoards[ph.getCurrentPlayer()].getScore(k);
				result = convertScore[k].str();
				scoreValueText[k].setString(result);
				result = "";
				convertScore[k].clear();
			}
			else if (!scoreBoards[ph.getCurrentPlayer()].getStatus(k))
			{
				scoreValueText[k].setString("");
			}
			else
			{
				scoreValueText[k].setString("-");
			}
		}
		scoreBoards[ph.getCurrentPlayer()].SetGivingPoints(diceValues);
		scoreBoards[ph.getCurrentPlayer()].setGivingPointsScore(diceValues);
		for (int k = 0; k < 16; k++)			//kollar vilken färg som ska sättas i poängrutorna
		{
			if (scoreBoards[ph.getCurrentPlayer()].getStatus(k))
			{
				scoreBoardShapes[k].setFillColor(sf::Color(168, 168, 168));
			}
			else if (scoreBoards[ph.getCurrentPlayer()].getGivingPoints(k))
			{
				if (this->nrOfThrowsLeft < 3 && scoreAdded == false)
				{
					scoreBoardShapes[k].setFillColor(sf::Color(250, 250, 0));
					convertScore[k] << scoreBoards[ph.getCurrentPlayer()].getGivingPointsScore(k);
					result = convertScore[k].str();
					scoreValueText[k].setString(result);
					result = "";
					convertScore[k].clear();
				}
				else
				{
					scoreBoardShapes[k].setFillColor(sf::Color(255, 250, 250));
				}
			}
			else
			{
				scoreBoardShapes[k].setFillColor(sf::Color(255, 250, 250));
			}
		}
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				delete[] diceValues;
				this->window.close();
				return false;
				break;

			case sf::Event::MouseButtonReleased:
				mx = sf::Mouse::getPosition(this->window).x;
				my = sf::Mouse::getPosition(this->window).y;
				if (mx > 600 && mx < 720 && my > 500 && my < 550) //continue: byter spelare/avslutarspel
				{
					if (scoreAdded == true)
					{
						scoreAdded = false;
						this->nrOfThrowsLeft = 3;
						dh.resetDice();
						ph.changePlayer();
						if (ph.getCurrentPlayer() == 0)
						{
							this->currentRound++;
							if (this->currentRound == 15)
							{
								this->currentRound = 0;
								delete[] diceValues;
								return true;
								//window.close();
							}
						}
					}
				}
				if (mx > 400 && mx < 520 && my > 500 && my < 550) //Kastar tärningar
				{
					if (this->nrOfThrowsLeft > 0 && scoreAdded == false)
					{
						for (int k = 0; k < 12; k++) //animationen
						{
							sf::sleep(sf::seconds(1.0f / 30));
							for (int l = 0; l < 5; l++)
							{
								if (k > 5)
								{
									if (!dh.getIfDiceIsHold(l))
									{
										dicesShapes[l].setTextureRect(sf::IntRect(557 * (k - 6), 0, 557, 557));
									}
								}	
								else
								{
									if (!dh.getIfDiceIsHold(l))
									{
										dicesShapes[l].setTextureRect(sf::IntRect(557 * (k), 0, 557, 557));
									}
								}
								this->window.draw(dicesShapes[l]);
								this->window.display();
							}		
						}
						dh.throwDice();
						delete[] diceValues;
						//diceValues = new int[5];
						diceValues = dh.getDiceValueArray(5);
						for (int k = 0; k < 5; k++) //hämtar texture baserat på tärnings värde
						{
							dicesShapes[k].setTextureRect(sf::IntRect(557 * (diceValues[k] - 1), 0, 557, 557));
						}
						this->nrOfThrowsLeft--;
					}
				}
				for (int k = 0; k < 5; k++)
				{
					if (mx > 350 + k*75 && mx < 350 + k * 75 + 50 && my > 300 && my < 350) //Klicka på tärningar för att "hålla" dom
					{
						if(this->nrOfThrowsLeft < 3 && scoreAdded == false)
						dh.setDiceForHolding(k);
					}
				}
				for (int k = 0; k < 16; k++)
				{
					if (mx > 50 && mx < 100 && my > 100 + k * 30 && my < 100 + k * 30 + 30) //klickla på poängruta för att sätta poäng
					{
						if (this->nrOfThrowsLeft < 3 && scoreAdded == false)
						{
							if (k != 6)
							{
								if (scoreBoards[ph.getCurrentPlayer()].getStatus(k) == false)
								{
									scoreBoards[ph.getCurrentPlayer()].setScores(diceValues, k);
									scoreBoards[ph.getCurrentPlayer()].setGoalMarked(k);
									scoreAdded = true;
								}
							}
						}
					}
				}
				if(mx > 700 && mx < 800 && my > 0 && my < 50)
				{
					scoreAdded = false;
					dh.resetDice();
					while (!ph.getCurrentPlayer() == 0)
					{
						ph.changePlayer();
					}
					this->nrOfThrowsLeft = 3;
					this->currentRound = 0;
					delete[] diceValues;
					return false;
				}
				break;
			}
		}
		this->window.clear(sf::Color(0,102,0));
		this->window.draw(sprite);
		for (int k = 0; k < 16;k++)
		{
			this->window.draw(scoreBoardShapes[k]);
		}
		for (int k = 0; k < 16; k++)
		{
			this->window.draw(scoreBoardDescription[k]);
		}
		for (int k = 0; k < 5; k++)
		{

			this->window.draw(dicesShapes[k]);
		}
		this->window.draw(playerNameText);
		if (this->nrOfThrowsLeft > 0 && scoreAdded == false)
		{
			this->window.draw(throwDices);
			this->window.draw(throwDiceButtonText);
		}
		this->window.draw(throwText);
		for (int k = 0; k < 16; k++)
		{
			this->window.draw(scoreValueText[k]);
		}
		for (int k = 0; k < 5; k++)
		{
			if(dh.getIfDiceIsHold(k) && scoreAdded == false)
				this->window.draw(diceHolderPointer[k]);
		}
		if (scoreAdded == true)
		{
			drawContinueButton();
		}
		drawMenuButton();
		this->window.display();
	}
	return true;
}

//Initsiera spelare för spel, frågar först efter antal spelare frågar efter spelarnas namn
const int Game::initializeNumberOfPlayers()
{
	this->window.clear();
	sf::Texture background;
	background.loadFromFile("background1.png");
	sf::Sprite sprite;
	sprite.setTexture(background);
	sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	sf::String str;
	sf::Text text;
	sf::Text descriptionText;
	sf::Text button1Text;
	sf::Font font;
	int nrOfPlayers=0;
	if (!font.loadFromFile("arial.ttf"))
	{

	}
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(36);
	descriptionText.setFont(font);
	descriptionText.setColor(sf::Color::White);
	descriptionText.setCharacterSize(36);
	descriptionText.setPosition(100, 150);
	int mx;
	int my;
	while (this->window.isOpen())
	{
		//Sätter antal spelare
		sf::Event event;
		descriptionText.setString("Press key(2-6) for number of players");

		while (this->window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				this->window.close();
				return false;
				break;
				
			case sf::Event::MouseButtonReleased:
				mx = sf::Mouse::getPosition(this->window).x;
				my = sf::Mouse::getPosition(this->window).y;
				if (mx > 700 && mx < 800 && my > 0 && my < 50)
				{
					return 0;
				}
				break;
				// key pressed
			case sf::Event::KeyPressed: //kollar efter tangenttryck
				if (event.key.code == sf::Keyboard::Num2)
				{
					nrOfPlayers = 2;
					return nrOfPlayers;
					//this->window.close();
				}
				if (event.key.code == sf::Keyboard::Num3)
				{
					nrOfPlayers = 3;
					return nrOfPlayers;
					//this->window.close();
				}
				if (event.key.code == sf::Keyboard::Num4)
				{
					nrOfPlayers = 4;
					return nrOfPlayers;
					//this->window.close();
				}
				if (event.key.code == sf::Keyboard::Num5)
				{
					nrOfPlayers = 5;
					return nrOfPlayers;
					//this->window.close();
				}
				if (event.key.code == sf::Keyboard::Num6)
				{
					nrOfPlayers = 6;
					return nrOfPlayers;
					//this->window.close();
				}
				break;

				// we don't process other types of events
			default:
				break;
			}
		}
		this->window.clear();
		this->window.draw(sprite);
		this->window.draw(descriptionText);
		drawMenuButton();
		this->window.display();
	}
	return nrOfPlayers;
}

bool Game::initializePlayers(int nrOfPlayers)
{
	this->window.clear();
	sf::Texture background;
	background.loadFromFile("background1.png");
	sf::Sprite sprite;
	sprite.setTexture(background);
	sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	sf::String str;
	sf::Text text;
	sf::Text descriptionText;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{

	}
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(36);
	descriptionText.setFont(font);
	descriptionText.setColor(sf::Color::White);
	descriptionText.setCharacterSize(36);
	descriptionText.setPosition(100, 150);
	this->window.clear();
	string *names;
	string result;
	int mx;
	int my;
	names = new string[nrOfPlayers];
	int k = 0;
	while (this->window.isOpen())
	{	//Sätter namnen på spelarna
		string stringName = "Enter Name of Player ";
		ostringstream convert;  
		convert << k+1;  
		result = convert.str();
		stringName += (result);
		sf::Event event;
		descriptionText.setString(stringName);
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
		text.setPosition(sf::Vector2f(800 / 2.0f, 600 / 2.0f));

		while (this->window.pollEvent(event))
		{
				// check the type of the event...
			switch (event.type)
			{
					// window closed
			case sf::Event::Closed:
				delete[] names;
				this->window.close();
				return false;
				break;

			case sf::Event::TextEntered:
				if ((event.text.unicode < 123 && event.text.unicode>96) || (event.text.unicode < 91 && event.text.unicode>64)) //Speciferar vilka karaktärer som kan användas
				{
						str += static_cast<char>(event.text.unicode);
						text.setString(str);
				}
				if(event.text.unicode == 8) //backspace
				{
					str.erase(str.getSize() - 1, 1);
					text.setString(str);
				}
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Return) 
				{
					names[k] = str;
					str.clear();
					text.setString(str);
					k++;
					if (k == nrOfPlayers)
					{
						k = 0;
						ph.addPlayers(nrOfPlayers, names);
						delete[] scoreBoards;
						this->scoreBoards = new ScoreBoard[nrOfPlayers];
						delete[] names;
						return true;
						//this->window.close();
					}
				}
				break;
				case sf::Event::MouseButtonReleased:
					mx = sf::Mouse::getPosition(this->window).x;
					my = sf::Mouse::getPosition(this->window).y;
					if (mx > 610 && mx < 730 && my > 500 && my < 550) //continue knapp
					{
						names[k] = str;
						str.clear();
						text.setString(str);
						k++;
						if (k == nrOfPlayers)
						{
							k = 0;
							ph.addPlayers(nrOfPlayers, names);
							delete[] scoreBoards;
							this->scoreBoards = new ScoreBoard[nrOfPlayers];
							delete[] names;
							return true;
							//this->window.close();
						}
					}
					if (mx > 700 && mx < 800 && my > 0 && my < 50)
					{
						delete[] names;
						return false;
					}
				break;
			default:
				break;
			}
		}

		this->window.clear();
		this->window.draw(sprite);
		this->window.draw(descriptionText);
		this->window.draw(text);
		drawContinueButton();
		drawMenuButton();
		this->window.display();
		}
	return true;
}

//Visar top 10 highscores
bool Game::showHighscores()
{
	this->window.clear();
	sf::Texture background;
	background.loadFromFile("background1.png");
	sf::Sprite sprite;
	sprite.setTexture(background);
	sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	int nrOfSavedPlayers = 0;
	int counter = 0;
	string *playerNames;
	string *playerScores;
	string temp;
	ifstream iFile("highscore.txt");
	if (iFile.is_open())
	{
		while (getline(iFile, temp))
		{
			counter++;
		}
		iFile.close();
	}
	playerNames = new string[counter];
	playerScores = new string[counter];
	counter = 0;
	ifstream iFile2("highscore.txt");
	if (iFile2.is_open())
	{
		while (iFile2 >> playerNames[counter] >> playerScores[counter])
		{
			counter++;
		}
		iFile2.close();
	}

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{

	}
	sf::Text *highScoreText;
	highScoreText = new sf::Text[counter];

	string *highScoreString;
	highScoreString = new string[counter];
	ostringstream *convert;
	convert = new ostringstream[counter];
	for (int k = 0; k < counter; k++)
	{
		convert[k] << k + 1;
		highScoreString[k] += convert[k].str();
		highScoreString[k] += ".     ";
		highScoreString[k] += playerNames[k];
		highScoreString[k] += ":    ";
		highScoreString[k] += playerScores[k];
		highScoreText[k].setString(highScoreString[k]);
		highScoreText[k].setFont(font);
		highScoreText[k].setColor(sf::Color::White);
		highScoreText[k].setCharacterSize(20);
		highScoreText[k].setPosition(200, 100 + k * 40);
	}
	sf::Text highScoreTitleText;
	highScoreTitleText.setString("Top 10 High Scores");
	highScoreTitleText.setFont(font);
	highScoreTitleText.setColor(sf::Color::White);
	highScoreTitleText.setCharacterSize(28);
	highScoreTitleText.setPosition(300, 10);

	while (this->window.isOpen())
	{
		int mx=0;
		int my=0;
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				delete[] playerNames;
				delete[] playerScores;
				delete[] highScoreString;
				delete[] highScoreText;
				delete[] convert;
				return false;
				//this->window.close();
				break;
			case sf::Event::MouseButtonReleased:
				mx = sf::Mouse::getPosition(this->window).x;
				my = sf::Mouse::getPosition(window).y;
				if (mx > 700 && mx < 800 && my > 0 && my < 50) //menu knapp
				{
					//this->window.close();
					delete[] playerNames;
					delete[] playerScores;
					delete[] highScoreString;
					delete[] highScoreText;
					delete[] convert;
					return true;
				}
				break;
			default:
				break;
			}
		}
		this->window.clear();
		this->window.draw(sprite);
		for (int k = 0; k < counter; k++)
		{
			this->window.draw(highScoreText[k]);
		}
		this->window.draw(highScoreTitleText);
		drawMenuButton();
		this->window.display();
	}
	delete[] playerNames;
	delete[] playerScores;
	delete[] highScoreString;
	delete[] highScoreText;
	delete[] convert;
	return true;
}
//visar listan över spelare och rankar dem efter poäng, vinnaren högst upp
//använder bubble sort för att sortera spelarna
bool Game::getWinner()
{
	this->window.clear();
	sf::Texture background;
	background.loadFromFile("background1.png");
	sf::Sprite sprite;
	sprite.setTexture(background);
	sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	int *temp;
	temp = new int[ph.getNrOfPlayers()];
	string holdName;
	string holdName2;
	int winner=0;
	int hold=0;
	string *winnerName;
	winnerName = new string[ph.getNrOfPlayers()];
	string *winnerScoreString;
	winnerScoreString = new string[ph.getNrOfPlayers()];
	for (int k = 0; k < ph.getNrOfPlayers(); k++)
	{
		winnerScoreString[k] = "With a score of: ";
	}
	string result = "";
	int j = 0;
	for (int k = 0; k < ph.getNrOfPlayers(); k++)
	{
		temp[k] = this->scoreBoards[k].getTotalScore();
	}
	bool swapped = true;
	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < ph.getNrOfPlayers() - j; i++)
		{
			if (temp[i] < temp[i + 1])
			{
				hold = temp[i];
				holdName = ph.getPlayerNameByPos(i);
				holdName2 = ph.getPlayerNameByPos(i + 1);
				temp[i] = temp[i + 1];
				ph.setPlayerNameByPos(i, holdName2);
				temp[i + 1] = hold;
				ph.setPlayerNameByPos(i + 1, holdName);
				swapped = true;
			}
		}
	}
	saveToHighScore(temp);
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{

	}
	ostringstream *convert;
	convert = new ostringstream[ph.getNrOfPlayers()];
	ostringstream *convert2;
	convert2 = new ostringstream[ph.getNrOfPlayers()];
	for (int k = 0; k < ph.getNrOfPlayers(); k++)
	{
		convert2[k] << k+1;
		winnerName[k] += convert2[k].str();
		winnerName[k] += ". ";
		winnerName[k] += ph.getPlayerNameByPos(k);
		convert[k] << temp[k];
		result = convert[k].str();
		winnerScoreString[k] += (result);
	}
	sf::Text *winnerNameDisplay;
	winnerNameDisplay = new sf::Text[ph.getNrOfPlayers()];
	sf::Text *winnerScoreDisplay;
	winnerScoreDisplay = new sf::Text[ph.getNrOfPlayers()];
	for (int k = 0; k < ph.getNrOfPlayers(); k++)
	{
		winnerNameDisplay[k].setString(winnerName[k]);
		winnerNameDisplay[k].setFont(font);
		winnerNameDisplay[k].setColor(sf::Color::White);
		winnerNameDisplay[k].setCharacterSize(24);
		winnerNameDisplay[k].setPosition(200, 100 + k * 50);
		winnerScoreDisplay[k].setString(winnerScoreString[k]);
		winnerScoreDisplay[k].setFont(font);
		winnerScoreDisplay[k].setColor(sf::Color::White);
		winnerScoreDisplay[k].setCharacterSize(24);
		winnerScoreDisplay[k].setPosition(400, 100 + k * 50);
	}

	while (this->window.isOpen())
	{
		int mx = 0;
		int my = 0;
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				//this->window.close();
				delete[] temp;
				delete[] winnerName;
				delete[] winnerScoreString;
				delete[] convert;
				delete[] convert2;
				delete[] winnerNameDisplay;
				delete[] winnerScoreDisplay;
				return false;
				break;
			case sf::Event::MouseButtonReleased:
				mx = sf::Mouse::getPosition(window).x;
				my = sf::Mouse::getPosition(window).y;
				if (mx > 700 && mx < 800 && my > 0 && my < 50)
				{
					//this->window.close();
					delete[] temp;
					delete[] winnerName;
					delete[] winnerScoreString;
					delete[] convert;
					delete[] convert2;
					delete[] winnerNameDisplay;
					delete[] winnerScoreDisplay;
					return true;
				}
				break;
			default:
				break;
			}
		}
		this->window.clear();
		this->window.draw(sprite);
		for (int k = 0; k < ph.getNrOfPlayers(); k++)
		{
			this->window.draw(winnerNameDisplay[k]);
		}
		for (int k = 0; k < ph.getNrOfPlayers(); k++)
		{
			this->window.draw(winnerScoreDisplay[k]);
		}
		drawMenuButton();
		this->window.display();
	}
	delete[] temp;
	delete[] winnerName;
	delete[] winnerScoreString;
	delete[] convert;
	delete[] convert2;
	delete[] winnerNameDisplay;
	delete[] winnerScoreDisplay;
	return true;
}

//Sparar spelarna till en txt fil för highscore om de har tillräckligt med poäng flr top 10
void Game::saveToHighScore(int playerScoreList[])
{
	int nrOfSavedPlayers=0;
	int counter = 0;
	string *nameList;
	int *scoreList;
	string temp;
	ifstream iFile ("highscore.txt");
	if (iFile.is_open())
	{
		while (getline(iFile, temp)) //räknar antal spelare i txt fil
		{
			counter++;
		}
		iFile.close();
	}
	nrOfSavedPlayers = (counter + this->ph.getNrOfPlayers()); //ny array med spelarna från highscore listan
	if (counter < 1)										//och spelarna från föregångna spelet 
	{
		nameList = new string[nrOfSavedPlayers];
		scoreList = new int[nrOfSavedPlayers];
		for (int k = counter; k < nrOfSavedPlayers; k++)
		{
			nameList[k] = ph.getPlayerNameByPos(k - counter);
			scoreList[k] = playerScoreList[k - counter];
		}
		ofstream oFile;
		oFile.open("highscore.txt");
		if (nrOfSavedPlayers > 10)
		{
			nrOfSavedPlayers = 10;
		}
		for (int k = 0; k < nrOfSavedPlayers; k++)
		{
			oFile << nameList[k];
			oFile << "   ";
			oFile << scoreList[k];
			oFile << endl;
		}
		oFile.close();
	}
	else
	{
		nameList = new string[nrOfSavedPlayers];
		scoreList = new int[nrOfSavedPlayers];
		counter = 0;
		ifstream iFile2("highscore.txt");
		if (iFile2.is_open())
		{
			while (iFile2 >> nameList[counter] >> scoreList[counter])
			{
				counter++;
			}
			iFile2.close();
		}
		for (int k = (counter); k < nrOfSavedPlayers; k++)
		{
			nameList[k] = ph.getPlayerNameByPos(k - counter);
			scoreList[k] = playerScoreList[k - counter];
		}
		bool swapped = true;
		int j = 0;
		int holdScore = 0;
		string holdName = "";
		while (swapped) {
			swapped = false;
			j++;
			for (int i = 0; i < nrOfSavedPlayers - j; i++)
			{
				if (scoreList[i] < scoreList[i + 1])
				{
					holdScore = scoreList[i];
					holdName = nameList[i];
					scoreList[i] = scoreList[i + 1];
					nameList[i] = nameList[i + 1];
					scoreList[i + 1] = holdScore;
					nameList[i + 1] = holdName;
					swapped = true;
				}
			}
		}

		ofstream oFile;
		oFile.open("highscore.txt");
		if (nrOfSavedPlayers > 10)
		{
			nrOfSavedPlayers = 10;
		}
		for (int k = 0; k < nrOfSavedPlayers; k++)
		{
			oFile << nameList[k];
			oFile << "   ";
			oFile << scoreList[k];
			oFile << endl;
		}
		oFile.close();
	}	
	delete[] nameList;
	delete[] scoreList;
}