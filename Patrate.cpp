#include <iostream>
#include "Patrate.h"

Patrat::Patrat() :nava(false), apasat(false),nonav(false), x(0), y(0)
{

}

Patrat::Patrat(bool nav, bool nonav, bool ap, int x, int y) : nava(nav), nonav(nonav), apasat(ap), x(x), y(y)
{

}

int Patrat::getX()
{
	return x;
}

int Patrat::getY()
{
	return y;
}

void Patrat::setX(int xn)
{
	x = xn;
}

void Patrat::setY(int yn)
{
	y = yn;
}

void Patrat::setNava(bool n)
{
	nava = n;
}

bool Patrat::getNava()
{
	return nava;
}

void Patrat::setApasat(bool a)
{
	apasat = a;
}

bool Patrat::getApasat()
{
	return apasat;
}

bool Patrat::getNonav()
{
	return nonav;
}

void Patrat::setNonav(bool n)
{
	nonav = n;
}

void Patrat::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	if (nava == true && nonav == true)
		glColor3f(0.2f, 1.0f, 0.0f);//verde

	if (apasat == false && nava == false)
		glColor3f(0.0f, 0.2f, 1.0f);//albastru
	else
	{
		if (nava == true && apasat == false)
			glColor3f(0.2f, 1.0f, 0.0f);//verde

		if (apasat == true && nava == false)
			glColor3f(0.6f, 0.2f, 0.0f);//portocaliu
		
		if (apasat == true && nava == true)
			glColor3f(1.0f, 0.0f, 0.0f);//rosu
		
	}
	
	glBegin(GL_QUADS);
	glVertex2d(0 + (x * 50), 0 + (y * 50));
	glVertex2d(50 + (x * 50), 0 + (y * 50));
	glVertex2d(50 + (x * 50), 50 + (y * 50));
	glVertex2d(0 + (x * 50), 50 + (y * 50));
	glEnd();

}