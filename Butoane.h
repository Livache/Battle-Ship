#ifndef BUTOANE_H
#define BUTOANE_H

#include <string.h>
#include <GL/freeglut.h>


class Buton
{
private:
	char *nume;
	int x;
	int y;
	bool apasat = false;
	bool derender = false;

public:

	Buton();
	Buton(char* s, int x1, int y1);

	void render();

	int getX();
	int getY();

	bool getApasat();
	void setApasat(bool a);

	bool getDerender();
	void setDerender(bool a);

	void setNume(char* s);

	void click(int xm, int ym);

};

#endif
