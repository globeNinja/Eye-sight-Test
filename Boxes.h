#pragma once

#include <GL/freeglut.h>
#include <vector>


using namespace std;
extern int correctCount;

//this class draws the box and stores the information of each box
class Boxes
{
public:
	vector<float> boxPosition;
	vector<float> boxColor;
	float boxtempLeft, boxtempRight, boxtempTop, boxtempBottom;

	int boxNum;
	float boxHalf;

	int correctBox;
	bool targetHit;

	//declare class functions
	Boxes(int boxIndex, float elemSize, vector<float> getBoxpos, vector<float> getBoxcolor, int chosenBox);
	void drawBox();
	void boxComputeintersection(float mouseX, float mouseY);
};

