#include "Boxes.h"

//initializes all box variables
Boxes::Boxes(int boxIndex, float elemSize, vector<float> getBoxpos, vector<float> getBoxcolor, int chosenBox)
{
	boxNum = boxIndex;
	boxHalf = elemSize / 2.0f;
	//change to pushback init
	boxPosition.push_back(getBoxpos[0]);
	boxPosition.push_back(getBoxpos[1]);
	boxPosition.push_back(getBoxpos[2]);
	//needs to change to procedurally assign color
	boxColor.push_back(getBoxcolor[0]);
	boxColor.push_back(getBoxcolor[1]);
	boxColor.push_back(getBoxcolor[2]);

	correctBox = chosenBox;
	targetHit = false;
	boxtempLeft = boxPosition[0] - boxHalf;
	boxtempRight = boxPosition[0] + boxHalf;
	boxtempTop = boxPosition[1] + boxHalf;
	boxtempBottom = boxPosition[1] - boxHalf;
}

//using opengl to draw box shape using glrectf
void Boxes::drawBox()
{
	glLoadIdentity();
	glPushMatrix();
		glTranslatef(boxPosition[0], boxPosition[1], boxPosition[2]);
		glColor3f(boxColor[0], boxColor[1], boxColor[2]);
		//left bottom and right top vertices
		glRectf(-boxHalf, -boxHalf, boxHalf, boxHalf);
	glPopMatrix();
}

//computes intersection from mouse left-click
void Boxes::boxComputeintersection(float mouseX, float mouseY)
{
	if ((mouseX > boxtempLeft) && (mouseX < boxtempRight) && (mouseY > boxtempBottom) && (mouseY < boxtempTop) && (boxNum == correctBox))
	{
		targetHit = true;
	}

	return;
}