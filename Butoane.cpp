#include <iostream>
#include "Butoane.h"

Buton::Buton()
{

}

Buton::Buton(char* s, int x1, int y1) :nume(s), x(x1), y(y1)
{

}

void Buton::render()
{
	if (derender == false)
	{

		glColor3f(0.0f, 0.2f, 1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (apasat == true)
		{
			glColor3f(0.0f, 0.6f, 1.0f);
		}

		glBegin(GL_QUADS);

		glVertex2d(x, y);
		glVertex2d(x + 100, y);
		glVertex2d(x + 100, y + 50);
		glVertex2d(x, y + 50);

		glEnd();
		glColor3d(1.0, 1.0, 1.0);
		
		glRasterPos2i(x + 20, y + 20);

		for (int i = 0; i<strlen(nume); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nume[i]);
	}
}

int Buton::getX()
{
	return x;
}

int Buton::getY()
{
	return y;
}

void Buton::click(int xm, int ym)
{
	if (derender == false)
		if ((xm >= x) && (xm <= x + 100))
		{
			if ((ym >= y) && (ym <= y + 50))
			{
				apasat = true;

			}
		}
}
bool Buton::getApasat()
{
	return apasat;
}
void Buton::setApasat(bool a)
{
	apasat = a;
}
bool Buton::getDerender()
{
	return derender;
}
void Buton::setDerender(bool a)
{
	derender = a;
}
void Buton::setNume(char* s)
{
	nume = s;
}
