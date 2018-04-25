#ifndef TABELA_H
#define TABELA_H

#include <GL/freeglut.h>
#include "Patrate.h"

class Tabela
{
private:
	Patrat **p;
	
public:
	Tabela();

	void click(int x, int y);
	void clickNava(int x, int y);

	bool checkNava(int x, int y);
	bool checkNonav(int x, int y);
	bool checkApasat(int x, int y);

	void render();
};

#endif
