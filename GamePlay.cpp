#include "GamePlay.h"

GamePlay::GamePlay()
{
	//start level as 1
	currentLevel = 1;
	
	gameRows = 0;
	gameColumns = 0;

	gameSize = 0.75;
	gapSize = 0.02f;
	
	setBoxpos.assign(VECTOR, 0.0);
	setBoxcolor.assign(VECTOR, 0.0);
	setBoxLightcolor.assign(VECTOR, 0.0);

	//initialize game values here
	correctCount = 0;
	mouseAttempt = 0;
	errorCount = 0;
	highScore = 0;
	currentScore = 0;
	startGame = 0;
	gameTimeleft = 0;
	gameTimeGet = 0;
	startTimer = 20;
	isChampion = false;
	gameTotalTime = 0;
}

//set the positional data for boxes and add to global vector
void GamePlay::setGridposition()
{
	for (size_t i = 0; i < gBoxes.size(); i++)
	{
		delete gBoxes[i];
	}
	gBoxes.clear();
	gameRows = currentLevel + 1;
	gameColumns = gameRows;

	int totalBoxes, randomElem;
	totalBoxes = gameRows * gameColumns;
	//seed a new random number whenever grid is reset
	srand((unsigned int)time(0));
	//will always return random 0-1 value regardless of compiler
	setBoxcolor[0] = ((float)rand() / RAND_MAX);
	setBoxcolor[1] = ((float)rand() / RAND_MAX);
	setBoxcolor[2] = ((float)rand() / RAND_MAX);

	changeSaturation(setBoxcolor, 0.75f, setBoxLightcolor);
	
	randomElem = rand() % totalBoxes;

	int elemCounter = 0;
	float boxSize, startxVal, startyVal;
	boxSize = ((gameSize * 2.0f)/gameRows) - gapSize;

	//start from top left
	startxVal = (-gameSize) + (boxSize / 2.0f) + gapSize;
	startyVal = gameSize - (boxSize / 2.0f) - gapSize;
	for (int row = 0; row < gameRows; row++)
	{
		for (int column = 0; column < gameColumns; column++)
		{
			
			setBoxpos[0] = startxVal +((boxSize + gapSize) * column);
			setBoxpos[1] = startyVal - ((boxSize + gapSize) * row);
			//elem rand here
			if (elemCounter == randomElem)
			{
				gBoxes.push_back(new Boxes(elemCounter, boxSize, setBoxpos, setBoxLightcolor, randomElem));
			}
			else
			{
				gBoxes.push_back(new Boxes(elemCounter, boxSize, setBoxpos, setBoxcolor, randomElem));
			}
			
			elemCounter++;
		}
	}
}

//changes saturation, function provided by Darel Rex Finley
void GamePlay::changeSaturation(vector<float> colorInput, float changeInput, vector<float>& colorOutput)
{
	//  The "change" parameter works like this:
	//    0.0 creates a black-and-white image.
	//    0.5 reduces the color saturation by half.
	//    1.0 causes no change.
	//    2.0 doubles the color saturation.
	float changeP, percR, percG, percB, redVal, greenVal, blueVal;

	redVal = colorInput[0];
	greenVal = colorInput[1];
	blueVal = colorInput[2];

	percR = 1.0f;
	percG = 1.0f;
	percB = 1.0f;


	changeP = sqrt((redVal * redVal * percR) + (greenVal * greenVal * percG) + (blueVal * blueVal * percB));

	colorOutput[0] = changeP + (redVal - changeP) * changeInput;
	colorOutput[1] = changeP + (greenVal - changeP) * changeInput;
	colorOutput[2] = changeP + (blueVal - changeP) * changeInput;
}

void GamePlay::resetGameValues()
{
	correctCount = 0;
	mouseAttempt = 0;
	errorCount = 0;
	currentScore = 0;
	startGame = 0;
	gameTimeleft = 0;
	gameTimeGet = 0;
	startTimer = 20;
	gameTotalTime = 0;
	currentLevel = 1;
	isChampion = false;
}

string GamePlay::gameEndmsg()
{
	if (currentScore < 3)
	{
		return("Oh no! Better luck next time.");
	}
	else if (currentScore > 3 && currentScore < 9)
	{
		return("You're pretty good! But I think you can do better!");
	}
	else
	{
		return("Nasa called, they want their AI back!");
	}
}