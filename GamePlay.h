#pragma once


#include <iostream>
#include <vector>
#include <ctime>
#include <math.h>
#include "Boxes.h"
using namespace std;


// Grab access to the global list of pointers to objects
extern vector< Boxes* > gBoxes;

class GamePlay
{
private:
	const int VECTOR = 3;
public:
	float gameSize;
	float gapSize;
	int gameRows;
	int gameColumns;
	int currentLevel;

	bool isChampion;

	int mouseAttempt;
	int errorCount;
	int correctCount;
	int highScore;
	int currentScore;
	int startGame;
	int startTimer;
	clock_t gameTimeleft;
	clock_t gameTimeGet;
	clock_t gameTotalTime;

	vector<float> setBoxpos;
	vector<float> setBoxcolor;
	vector<float> setBoxLightcolor;

	GamePlay();
	//void computeGamelevel();
	void setGridposition();
	void changeSaturation(vector<float> colorInput, float changeInput, vector<float>& colorOutput);
	void resetGameValues();
	string gameEndmsg();
};

