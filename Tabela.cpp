#include <iostream>
#include "Tabela.h"

Tabela::Tabela()
{
	p = new Patrat*[10]();

	for (int i = 0; i < 10; i++)
	{
		p[i] = new Patrat[10]();
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			p[i][j].setX(i);
			p[i][j].setY(j);
			p[i][j].setApasat(false);
			p[i][j].setNava(false);
			p[i][j].setNonav(false);
		}
	}
}

void Tabela::click(int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (x >= (0 + (p[i][j].getX() * 50)) && x <= (50 + (p[i][j].getX() * 50)))
			{
				if (y >= (0 + (p[i][j].getY() * 50)) && y <= (50 + (p[i][j].getY() * 50)))
				{

					if (p[i][j].getApasat() == false)
						p[i][j].setApasat(true);

				}
			}

		}
	}
}

void Tabela::clickNava(int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (x >= (0 + (p[i][j].getX() * 50)) && x < (50 + (p[i][j].getX() * 50)))
			{
				if (y >= (0 + (p[i][j].getY() * 50)) && y < (50 + (p[i][j].getY() * 50)))
				{
					if (p[i][j].getNava() == false)
					{
						p[i][j].setNava(true);
						p[i][j].setNonav(true);

						if (i != 9)
						{
								p[i + 1][j].setNonav(true);
							if (j != 0)
								p[i + 1][j - 1].setNonav(true);
							if (j != 9)
								p[i + 1][j + 1].setNonav(true);
						}

						if (i != 0)
						{
								p[i - 1][j].setNonav(true);
							if (j != 0)
								p[i - 1][j - 1].setNonav(true);
							if (j != 9)
								p[i - 1][j + 1].setNonav(true);
						}

						if (j != 0)
							p[i][j - 1].setNonav(true);
						if (j != 9)
							p[i][j + 1].setNonav(true);

					}
				}
			}
		}
	}
}

bool Tabela::checkNava(int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (x >= (0 + (p[i][j].getX() * 50)) && x < (50 + (p[i][j].getX() * 50)))
			{
				if (y >= (0 + (p[i][j].getY() * 50)) && y < (50 + (p[i][j].getY() * 50)))
				{
					if (p[i][j].getNava() == true)
						return true;
					
				}
			}
		}
	}
	return false;
}

bool Tabela::checkNonav(int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (x >= (0 + (p[i][j].getX() * 50)) && x < (50 + (p[i][j].getX() * 50)))
			{
				if (y >= (0 + (p[i][j].getY() * 50)) && y < (50 + (p[i][j].getY() * 50)))
				{
					if (p[i][j].getNonav() == true)
						return true;				
				}
			}
		}
	}
	return false;
}

bool Tabela::checkApasat(int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (x >= (0 + (p[i][j].getX() * 50)) && x < (50 + (p[i][j].getX() * 50)))
			{
				if (y >= (0 + (p[i][j].getY() * 50)) && y < (50 + (p[i][j].getY() * 50)))
				{
					if (p[i][j].getApasat() == true)
						return true;									
				}
			}
		}
	}
	return false;
}

void Tabela::render()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			p[i][j].render();
		}
	}

	//Tabela Gri.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2d(0, 0);
	glVertex2d(500, 0);
	glVertex2d(500, 500);
	glVertex2d(0, 500);
	glEnd();

	//Linii orizontale la tabela.
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2d(0, 50);
	glVertex2d(500, 50);
	glVertex2d(0, 100);
	glVertex2d(500, 100);
	glVertex2d(0, 150);
	glVertex2d(500, 150);
	glVertex2d(0, 200);
	glVertex2d(500, 200);
	glVertex2d(0, 250);
	glVertex2d(500, 250);
	glVertex2d(0, 300);
	glVertex2d(500, 300);
	glVertex2d(0, 350);
	glVertex2d(500, 350);
	glVertex2d(0, 400);
	glVertex2d(500, 400);
	glVertex2d(0, 450);
	glVertex2d(500, 450);
	glEnd();


	//Linii verticale la tabela.
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2d(50, 0);
	glVertex2d(50, 500);
	glVertex2d(100, 0);
	glVertex2d(100, 500);
	glVertex2d(150, 0);
	glVertex2d(150, 500);
	glVertex2d(200, 0);
	glVertex2d(200, 500);
	glVertex2d(250, 0);
	glVertex2d(250, 500);
	glVertex2d(300, 0);
	glVertex2d(300, 500);
	glVertex2d(350, 0);
	glVertex2d(350, 500);
	glVertex2d(400, 0);
	glVertex2d(400, 500);
	glVertex2d(450, 0);
	glVertex2d(450, 500);
	glEnd();
}

