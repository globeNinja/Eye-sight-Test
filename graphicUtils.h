#pragma once

#include <ctime>

double diffclock(clock_t clock1, clock_t clock2);

class Graphicutil
{
public:
	int windowHeight;
	int windowWidth;


	Graphicutil();
	void doGraphicsInit();
};

