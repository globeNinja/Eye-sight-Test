// Graphics Utilities
//
// Open a window
//
// Set up as an object



#include <GL/glut.h>
#include "graphicUtils.h"
#include <ctime>

// FUNCTION FOR TRACKING TIME

double diffclock(clock_t clock1, clock_t clock2)
{
	double diffticks = clock1 - clock2;
	double diffms = (diffticks * 1000) / CLOCKS_PER_SEC;
	return diffms;
}


// CLASS FOR SETTING UP CAMERA - MEMBER FUNCTIONS

Graphicutil::Graphicutil()
{
	windowWidth = 512;
	windowHeight = 512;
}

void Graphicutil::doGraphicsInit()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(200, 200);

	glutCreateWindow("Color Game");
}
