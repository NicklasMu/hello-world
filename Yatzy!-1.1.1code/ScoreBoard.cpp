#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	for (int k = 0; k < 16; k++)
	{
		this->scores[k] = 0;
		this->statuses[k] = false;
		this->givingPoints[k] = false;
		this->givingPointsScore[k] = 0;
	}
}
ScoreBoard::~ScoreBoard()
{

}
ScoreBoard& ScoreBoard::operator=(const ScoreBoard& obj)
{
	for (int k = 0; k < 16; k++)
	{
		this->scores[k] = obj.scores[k];;
		this->statuses[k] = obj.statuses[k];
		this->givingPoints[k] = obj.givingPoints[k];
		this->givingPointsScore[k] = obj.givingPointsScore[k];
	}
	return *this;
}
void ScoreBoard::setScores(int diceValues[5], int pos) 	//playing rules for game aswell as marking score
{
	int result = 0;
	result = scoreProtocol(diceValues, pos);
	this->scores[pos] = result;
	
}
void ScoreBoard::setGoalMarked(const int pos)
{
	for (int k = 0; k < 16; k++)
	{
		if (!statuses[k])
		{

			if (k == pos)
			{
				this->statuses[k] = true;
			}
		}
	}
	if (this->statuses[0] && this->statuses[1] && this->statuses[2] && this->statuses[3] && this->statuses[4] && this->statuses[5] && !this->statuses[6])
	{	//Kollar om bonuspoäng har uppnåts eller inte
		int bonusScore = 0;
		for (int k = 0; k < 6; k++)
		{
			bonusScore = bonusScore + this->scores[k];
		}
		if (bonusScore > 62)
		{
			this->scores[6] = 50;
		}
		else
		{
			this->scores[6] = 0;
		}
		this->statuses[6] = true;
	}
}

const int ScoreBoard::getTotalScore()
{
	int totalScore = 0;
	for (int k = 0; k < 16; k++)
	{
		totalScore = totalScore + this->scores[k];
	}
	return totalScore;
}

const bool ScoreBoard::getStatus(int pos)
{
	bool statusReturn = false;
	for (int k = 0; k < 16; k++)
	{
		if (pos == k)
		{
			statusReturn = this->statuses[k];
		}
	}
	return statusReturn;
}

const int ScoreBoard::getScore(int pos)
{
	int scoreReturn = 0;
	for (int k = 0; k < 16; k++)
	{
		if (pos == k)
		{
			scoreReturn = this->scores[k];
		}
	}
	return scoreReturn;
}

void ScoreBoard::SetGivingPoints(int diceValues[5])
{
	int result = 0;
	for (int k = 0; k < 16; k++)
	{
		result = scoreProtocol(diceValues, k);
		if (result > 0)
			this->givingPoints[k] = true;
		else
			this->givingPoints[k] = false;
	}

}

const bool ScoreBoard::getGivingPoints(int pos)
{
	bool givingPointsReturn = false;
	for (int k = 0; k < 16; k++)
	{
		if (pos == k)
		{
			givingPointsReturn = this->givingPoints[k];
		}
	}
	return givingPointsReturn;
}

const int ScoreBoard::scoreProtocol(int diceValues[5], int pos)
{
	int result=0;
	if (pos >= 0 && pos < 6)
	{
		result=xOfAKindProtocol(diceValues, pos);
	}
	else if (pos > 6 && pos < 16)
	{
		result=specialScoreProtocol(diceValues, pos);
	}
	return result;
}

const int ScoreBoard::xOfAKindProtocol(int diceValues[5], int pos)
{
	int ones = 0;
	int twos = 0;
	int threes = 0;
	int fours = 0;
	int fives = 0;
	int sixes = 0;
	int result = 0;

		if (pos == 0) //ones
		{
			for (int l = 0; l < 5; l++)
			{
				if (diceValues[l] == 1)
				{
					ones++;
				}
			}
			result = ones;
			return result;
		}
		else if (pos == 1) //twos
		{
			for (int l = 0; l < 5; l++)
			{
				if (diceValues[l] == 2)
				{
					twos++;
				}
			}
			result = twos * 2;
			return result;
		}
		else if (pos == 2) //threes
		{
			for (int l = 0; l < 5; l++)
			{
				if (diceValues[l] == 3)
				{
					threes++;
				}
			}
			result = threes * 3;
			return result;
		}
		else if (pos == 3) //fours
		{
			for (int l = 0; l < 5; l++)
			{
				if (diceValues[l] == 4)
				{
					fours++;
				}
			}
			result = fours * 4;
			return result;
		}
		else if (pos == 4) //fives
		{
			for (int l = 0; l < 5; l++)
			{
				if (diceValues[l] == 5)
				{
					fives++;
				}
			}
			result = fives * 5;
			return result;
		}
		else if (pos == 5) //sixes
		{
			for (int l = 0; l < 5; l++)
			{
				if (diceValues[l] == 6)
				{
					sixes++;
				}
			}
			result = sixes * 6;
			return result;
		}
	return result;
}

const int ScoreBoard::specialScoreProtocol(int diceValues[5], int pos)
{
	int ones = 0;
	int twos = 0;
	int threes = 0;
	int fours = 0;
	int fives = 0;
	int sixes = 0;
	int result = 0;
	int subResult1 = 0;
	int subResult2 = 0;
	if (pos == 7) //one pair
	{
		for (int l = 0; l < 5; l++)
		{
			if (diceValues[l] == 1)
				ones++;
			if (diceValues[l] == 2)
				twos++;
			if (diceValues[l] == 3)
				threes++;
			if (diceValues[l] == 4)
				fours++;
			if (diceValues[l] == 5)
				fives++;
			if (diceValues[l] == 6)
				sixes++;
		}
		if (ones > 1)
			result = 2;
		if (twos > 1)
			result = 4;
		if (threes > 1)
			result = 6;
		if (fours > 1)
			result = 8;
		if (fives > 1)
			result = 10;
		if (sixes > 1)
			result = 12;
		return result;
	}
	else if (pos == 8) //two pair
	{
		for (int l = 0; l < 5; l++)
		{
			if (diceValues[l] == 1)
				ones++;
			if (diceValues[l] == 2)
				twos++;
			if (diceValues[l] == 3)
				threes++;
			if (diceValues[l] == 4)
				fours++;
			if (diceValues[l] == 5)
				fives++;
			if (diceValues[l] == 6)
				sixes++;
		}
		if (ones > 1)
			subResult1 = 2;
		if (twos > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 4;
			else
				subResult1 = 4;
		}
		if (threes > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 6;
			else
				subResult1 = 6;
		}
		if (fours > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 8;
			else
				subResult1 = 8;
		}
		if (fives > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 10;
			else
				subResult1 = 10;
		}
		if (sixes > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 12;
		}
		return result;
	}
	else if (pos == 9) //three in a row
	{
		for (int l = 0; l < 5; l++)
		{
			if (diceValues[l] == 1)
				ones++;
			if (diceValues[l] == 2)
				twos++;
			if (diceValues[l] == 3)
				threes++;
			if (diceValues[l] == 4)
				fours++;
			if (diceValues[l] == 5)
				fives++;
			if (diceValues[l] == 6)
				sixes++;
		}
		if (ones > 2)
			result = 3;
		if (twos > 2)
			result = 6;
		if (threes > 2)
			result = 9;
		if (fours > 2)
			result = 12;
		if (fives > 2)
			result = 15;
		if (sixes > 2)
			result = 18;
		return result;
	}
	else if (pos == 10) //four in a row
	{
		for (int l = 0; l < 5; l++)
		{
			if (diceValues[l] == 1)
				ones++;
			if (diceValues[l] == 2)
				twos++;
			if (diceValues[l] == 3)
				threes++;
			if (diceValues[l] == 4)
				fours++;
			if (diceValues[l] == 5)
				fives++;
			if (diceValues[l] == 6)
				sixes++;
		}
		if (ones > 3)
			result = 4;
		if (twos > 3)
			result = 8;
		if (threes > 3)
			result = 12;
		if (fours > 3)
			result = 16;
		if (fives > 3)
			result = 20;
		if (sixes > 3)
			result = 24;
		return result;
	}
	else if (pos == 11) //small straight
	{
		for (int l = 0; l < 5; l++)
		{
			if (diceValues[l] == 1)
				ones++;
			if (diceValues[l] == 2)
				twos++;
			if (diceValues[l] == 3)
				threes++;
			if (diceValues[l] == 4)
				fours++;
			if (diceValues[l] == 5)
				fives++;
			if (diceValues[l] == 6)
				sixes++;
		}
		if (ones == 1 && twos == 1 && threes == 1 && fours == 1 && fives == 1)
		{
			result = 15;
		}
		return result;
	}
	else if (pos == 12) //big straight
	{
		for (int l = 0; l < 5; l++)
		{
			if (diceValues[l] == 1)
				ones++;
			if (diceValues[l] == 2)
				twos++;
			if (diceValues[l] == 3)
				threes++;
			if (diceValues[l] == 4)
				fours++;
			if (diceValues[l] == 5)
				fives++;
			if (diceValues[l] == 6)
				sixes++;
		}
		if (twos == 1 && threes == 1 && fours == 1 && fives == 1 && sixes == 1)
		{
			result = 20;
		}
		return result;
	}
	else if (pos == 13) //full house
	{
		for (int l = 0; l < 5; l++)
		{
			if (diceValues[l] == 1)
				ones++;
			if (diceValues[l] == 2)
				twos++;
			if (diceValues[l] == 3)
				threes++;
			if (diceValues[l] == 4)
				fours++;
			if (diceValues[l] == 5)
				fives++;
			if (diceValues[l] == 6)
				sixes++;
		}
		if (ones > 2)
		{
			subResult1 = 3;
		}
		else if (ones > 1)
		{
			subResult2 = 2;
		}
		if (twos > 2)
		{
			if (subResult2 > 0)
				result = subResult2 + 6;
			else
				subResult1 = 6;
		}
		else if (twos > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 4;
			else
				subResult2 = 4;
		}
		if (threes > 2)
		{
			if (subResult2 > 0)
				result = subResult2 + 9;
			else
				subResult1 = 9;
		}
		else if (threes > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 6;
			else
				subResult2 = 6;
		}
		if (fours > 2)
		{
			if (subResult2 > 0)
				result = subResult2 + 12;
			else
				subResult1 = 12;
		}
		else if (fours > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 8;
			else
				subResult2 = 8;
		}
		if (fives > 2)
		{
			if (subResult2 > 0)
				result = subResult2 + 15;
			else
				subResult1 = 15;
		}
		else if (fives > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 10;
			else
				subResult2 = 10;
		}
		if (sixes > 2)
		{
			if (subResult2 > 0)
				result = subResult2 + 18;
			else
				subResult1 = 18;
		}
		else if (sixes > 1)
		{
			if (subResult1 > 0)
				result = subResult1 + 12;
			else
				subResult2 = 12;
		}
		return result;
	}
	else if (pos == 14) //chance
	{
		for (int l = 0; l < 5; l++)
		{
			result = result + diceValues[l];
		}
		return result;
	}
	else if (pos == 15) //yatzy
	{
		for (int l = 0; l < 5; l++)
		{
			if (diceValues[l] == 1)
				ones++;
			if (diceValues[l] == 2)
				twos++;
			if (diceValues[l] == 3)
				threes++;
			if (diceValues[l] == 4)
				fours++;
			if (diceValues[l] == 5)
				fives++;
			if (diceValues[l] == 6)
				sixes++;
		}
		if (ones > 4)
			result = 50;
		if (twos > 4)
			result = 50;
		if (threes > 4)
			result = 50;
		if (fours > 4)
			result = 50;
		if (fives > 4)
			result = 50;
		if (sixes > 4)
			result = 50;
		return result;
	}
	return result;
}

void ScoreBoard::setGivingPointsScore(int diceValues[5])
{
	for (int k = 0; k < 16; k++)
	{
		this->givingPointsScore[k] = scoreProtocol(diceValues, k);
	}
}

const int ScoreBoard::getGivingPointsScore(int pos)
{
	return this->givingPointsScore[pos];
}