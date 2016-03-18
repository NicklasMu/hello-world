#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

class ScoreBoard
{

	int scores[16];
	bool statuses[16];
	bool givingPoints[16];
	int givingPointsScore[16];

public:
	ScoreBoard();
	~ScoreBoard();
	ScoreBoard& operator=(const ScoreBoard& obj);
	void setScores(int diceValues[5], int pos);
	void setGoalMarked(const int pos);
	const int getTotalScore();
	const bool getStatus(int pos);
	const int getScore(int pos);
	void SetGivingPoints(int diceValues[5]);
	const bool getGivingPoints(int pos);
	const int scoreProtocol(int diceValues[5], int pos);
	const int xOfAKindProtocol(int diceValues[5], int pos);
	const int specialScoreProtocol(int diceValues[5], int pos);
	void setGivingPointsScore(int diceValues[5]);
	const int getGivingPointsScore(int pos);


};

