//
//Description: This is a color game that tests the vision of the player
//
//Author: Ng Wei Bin
//Date: 11/04/2020
//
//input: Mouse left-click to select box. Additional options in mouse right-click
//
//output: In-game statistics such as current score and high scores. Description of how well then player did in the test.

#include <iostream>
#include <vector>
#include <ctime>
#include <string>

using namespace std;

#include <GL/freeglut.h>


//include user defined classes
#include "graphicUtils.h"
#include "Boxes.h"
#include "GamePlay.h"

//initialize global functions
void drawScene();
void displayString(string s);
void drawStatistics();
void drawEndStatistics();
void handleResize(int w, int h);
void mousebutton(int button, int state, int x, int y);
void cleanup();
void handleKeypress(unsigned char key, int x, int y);
void createMenu();
void myMenu(int selectValue);
void moveWorld();


// Initialize global variables
int gDrawMode = 1;
int readWidth = 0; 
int readHeight = 0;

clock_t gPastTime = (clock_t) 0.0;

const float MINIMUM_MILLISECOND_UPDATE = 0.01f;


//define global objects for glut implementation
Graphicutil *setGraphic = new Graphicutil;
GamePlay *myGame = new GamePlay;

vector < Boxes* > gBoxes;



int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	setGraphic->doGraphicsInit();
	myGame->setGridposition();
	glutMouseFunc(mousebutton);

	createMenu();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutIdleFunc(moveWorld);
	glutMainLoop();

	return 0;
}

//depicts the elements of the scene
void drawScene()
{
	// Clear information from last draw
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (gDrawMode == 1)
	{
		
		for (size_t i = 0; i < gBoxes.size(); i++)
		{
			gBoxes[i]->drawBox();
		}
		drawStatistics();
		// don't wait - start processing buffered OpenGL routines - without this you may not see what is current
		//glFlush();
	}

	if (gDrawMode == 2)
	{
		drawEndStatistics();
		//glFlush();
	}


	// Sends the scene to the screen, without this you will have a blank screen - comment it out and try it
	glutSwapBuffers();

}

//converts each letter in a string to a character in glut
void displayString(string s)
{
	void* font = GLUT_BITMAP_HELVETICA_18;
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	return;
}

//runtime statistics of the player
void drawStatistics()
{
	string s;
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(-0.2f, 0.9f);
		s = "Time Left: ";
		displayString(s);
		s = to_string((int)(myGame->gameTimeleft));
		displayString(s);
		glRasterPos2f(-0.1f, -0.9f);
		s = "Errors: ";
		displayString(s);
		s = to_string((int)(myGame->errorCount));
		displayString(s);
	glPopMatrix();
}

//game over statistics of the player
void drawEndStatistics()
{
	string s;
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(-0.2f, 0.9f);
		s = "GAME OVER";
		displayString(s);
		glRasterPos2f(-0.5f, 0.1f);
		s = "Current Score: ";
		displayString(s);
		s = to_string(myGame->currentScore);
		displayString(s);
		glRasterPos2f(-0.5f, -0.1f);
		s = "High Score: ";
		displayString(s);
		s = to_string(myGame->highScore);
		displayString(s);
		glRasterPos2f(-0.9f, -0.5f);
		s = myGame->gameEndmsg();
		displayString(s);
	glPopMatrix();

	//new highscore
	if (myGame->isChampion)
	{
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			glRasterPos2f(-0.15f, 0.3f);
			s = "New Best!";
			displayString(s);
		glPopMatrix();
		glPushMatrix();
			glBegin(GL_LINE_LOOP);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.25f, 0.75f, 0.0f);
			glVertex3f(-0.25f, 0.4f, 0.0f);
			glVertex3f(0.25f, 0.4f, 0.0f);
			glVertex3f(0.25f, 0.75f, 0.0f);
			glVertex3f(0.0f, 0.5f, 0.0f);
			glVertex3f(-0.25f, 0.75f, 0.0f);
			glEnd();
		glPopMatrix();
	}
}

//export the handleresize to global variable to remap mouse
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	readWidth = w;
	readHeight = h;
	float aspect = (float)w / (float)h;
	float top = 2.0 / 2.0;
	float bottom = -top;
	float right = (2.0f * aspect) / 2.0f;
	float left = -right;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, 0.0, 1.0);
}

//mouse is remapped from reading grid size to orthogonal cartesian point
void mousebutton(int button, int state, int x, int y)
{
	float remapx = readWidth / 2.0f;
	float remapy = readHeight / 2.0f;
	float newx, newy;
	int mousePrevcorrect = myGame->correctCount;
	

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		myGame->mouseAttempt++;
		newx = (x / remapx)-1;
		newy = (2 - y / remapy)-1;

		for (size_t i = 0; i < gBoxes.size(); i++)
		{
			gBoxes[i]->boxComputeintersection(newx, newy);
			if (gBoxes[i]->targetHit)
			{
				myGame->correctCount++;
				myGame->currentScore++;
			}
		}
		
		if ((myGame->correctCount > mousePrevcorrect) )
		{
			myGame->currentLevel += 1;
			myGame->setGridposition();
			if (myGame->startGame == 0)
			{
				myGame->startGame = 1;
				myGame->gameTimeGet = gPastTime;
			}
			if (myGame->currentScore > myGame->highScore)
			{
				myGame->highScore = myGame->currentScore;
				myGame->isChampion = true;
			}
		}
		//error checking
		if ((myGame->mouseAttempt > myGame->correctCount) && (myGame->startGame ==1))
		{
			myGame->errorCount++;
			//transfer error and equalize score count
			myGame->mouseAttempt-=1;
			myGame->startTimer -= 2;
		}
	}
}

//deletes all pointers and releases memory
void cleanup()
{
	delete myGame;
	delete setGraphic;
	for (size_t i = 0; i < gBoxes.size(); i++)
	{
		delete gBoxes[i];
	}
	gBoxes.clear();
}

//esc key closes the game
void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27: // Escape Key
			cleanup();
			exit(0);
	}
}

//right click menu
void createMenu()
{
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Play Again", 1);
	glutAddMenuEntry("Exit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//1: resets game 2: exists the game
void myMenu(int selectValue)
{
	switch (selectValue)
	{
	case 1:
		gDrawMode = 1;
		myGame->resetGameValues();
		myGame->gameTimeGet = gPastTime;
		myGame->setGridposition();
		glutPostRedisplay();
		break;
	case 2:
		cleanup();
		exit(0);
		break;
	}
}

//this function calculates the time
void moveWorld()
{
	double elapsedTime;
	int currentTime;

	if (gPastTime == 0)
	{
		gPastTime = clock();
	}
	else
	{
		currentTime = clock();
		elapsedTime = double(diffclock(currentTime, gPastTime)) / 1000.0;

		if (elapsedTime > MINIMUM_MILLISECOND_UPDATE)
		{
			gPastTime = currentTime;
			if (myGame->startGame == 1)
			{
				myGame->gameTotalTime = gPastTime - myGame->gameTimeGet;
				myGame->gameTimeleft = (clock_t)(myGame->startTimer - (myGame->gameTotalTime / 1000.0));
				//throw out negative values
				if (myGame->gameTimeleft < 0)
				{
					myGame->gameTimeleft = 0;
				}
				glutPostRedisplay();
			}
			else
			{
				myGame->gameTimeleft = 20;
				glutPostRedisplay();
			}

			if (myGame->gameTimeleft == 0)
			{
				//no time left, go to results page
				gDrawMode = 2;
				glutPostRedisplay();
			}
		}
	}

}