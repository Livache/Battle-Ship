#ifndef PATRATE_H
#define PATRATE_H

#include <GL/freeglut.h>

class Patrat
{
private:
	int x, y;
	bool nava;
	bool apasat;
	bool nonav;

public:
	Patrat();
	Patrat(bool nav,bool nonav, bool ap, int x, int y);

	int getX();	
	int getY();
	
	void setX(int xn);
	void setY(int yn);
	
	void setNava(bool n);
	bool getNava();

	void setApasat(bool a);
	bool getApasat();
	
	bool getNonav();
	void setNonav(bool n);

	void render();
	
};

#endif