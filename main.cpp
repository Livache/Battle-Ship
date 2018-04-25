#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <GL/freeglut.h>
#include "Tabela.h"
#include "Butoane.h"
#include "YourIP.h"
#include "ConexiuneClient.h"
#include "ConexiuneHost.h"
//#include "Patrate.h"
using namespace std;

int HEIGHT = 600;
int WIDTH = 800;
bool direc = false;
bool d1 = 1, d2 = 0;
bool myTurn = 0;

sockaddr_in hint;
SOCKET listening;

sockaddr_in client;
SOCKET clientSocket;

SOCKET sock;

int clientSize = sizeof(client);

char buff[4096];
char buff2[4096];
char buff3[4096];
char res[4096];

char ip[15];
char *ip2;
int z = 0;

string myIpAddress;
string ipAddress;
string xs;
string ys;
string turn;
string result;

const float ASPECT = float(WIDTH) / HEIGHT;

Tabela tab;
Tabela tab2;
Buton start("Start", 300, 300);
Buton exit1("Exit", 300, 100);
Buton host("Host", 300, 300);
Buton join("Join", 300, 200);
Buton patru("Nava4", 650, 500);
Buton save("Save", 650, 100);
Buton trei1("Nava3", 650, 440);
Buton trei2("Nava3", 650, 380);
Buton trei3("Nava3", 650, 320);
Buton directie("Orizontal", 650, 100);
Buton directie2("Vertical", 650, 160);
Buton next1("Next", 530, 100);
Buton delet("Delete", 200, 530);
Buton acc("Save", 200, 460);
Buton doi("Nava2", 650, 260);


const char *nume = "Atacati.";

int patrate = 0;

const char *Conexiune;

void displaymeniu();
void joc2();
void displayfinal();
void mousefinal(int button, int state, int x, int y);

void Mouse3(int button, int state, int x, int y)
{
	//cout << "Dummy" << endl;
}

void Mouse2(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT&&state == GLUT_DOWN)
	{

		if (x > 0 && x < 500 && (HEIGHT - y)>0 && (HEIGHT - y) < 500)
		{
			if (x == 450 || x == 400 || x == 350 || x == 300 || x == 250 || x == 200 || x == 150 || x == 100 || x == 50)
			{
				x = x + 1;
			}
			if (HEIGHT - y == 450 || HEIGHT - y == 400 || HEIGHT - y == 350 || HEIGHT - y == 300 || HEIGHT - y == 250 || HEIGHT - y == 200 || HEIGHT - y == 150 || HEIGHT - y == 100 || HEIGHT - y == 50)
			{
				y = y + 1;
			}

			
			if (tab2.checkApasat(x, HEIGHT - y) != true)
			{
				
				xs = to_string(x);
				ys = to_string(HEIGHT - y);
				

				tab2.click(x, HEIGHT - y);

				if (Conexiune == "Host")
				{
					//cout << "SERVER>" << endl;
					//cout << "x=" << xs.c_str() << endl << "HEIGHT-y=" << ys.c_str();
					send(clientSocket, xs.c_str(), xs.length(), 0);
					send(clientSocket, ys.c_str(), ys.length(), 0);
					ZeroMemory(res, 4096);
					recv(clientSocket, res, 4096, 0);

				}
				else
				{
					//cout << "CLIENT>" << endl;
					//cout << "x=" << xs.c_str() << endl << "HEIGHT-y=" << ys.c_str();
					send(sock, xs.c_str(), xs.length(), 0);
					send(sock, ys.c_str(), ys.length(), 0);
					//send(sock, turn.c_str(), turn.length(), 0);
					ZeroMemory(res, 4096);
					recv(sock, res, 4096, 0);
				}

				
				//trimite la celalalt player coordonatele

				//recv(sock, res, 4096, 0);

				//primeste rezultat
				//daca da atac din nou daca nu ataca celalalt player
				if (strcmp(res, "HIT") == 0)
				{
					

					


					tab2.clickNava(x, HEIGHT - y);
					patrate++;

					if (patrate == 15)
					{
						turn = to_string(2);
						//cout << "Trimit 2 ca am castigat" << endl;
					}
					else
						turn = to_string(myTurn);
					nume = "HIT!";
					joc2();
					Sleep(500);
					glutMouseFunc(Mouse3);
					nume = "Atacati!";

					if (Conexiune == "Host")
					{
						send(clientSocket, turn.c_str(), turn.length(), 0);
					}
					else
					{
						send(sock, turn.c_str(), turn.length(), 0);
					}

				}
				else
				{


					

					nume = "MISS!";
					joc2();
					Sleep(500);
					glutMouseFunc(Mouse3);
					nume = "Asteptati.";
					myTurn = 0;
					turn = to_string(myTurn);
					if (Conexiune == "Host")
					{
						send(clientSocket, turn.c_str(), turn.length(), 0);
					}
					else
					{
						send(sock, turn.c_str(), turn.length(), 0);
					}



				}
			}
			else
				nume = "Ai atacat aici deja. Mai incearca.";




			glutDisplayFunc(joc2);
			glutPostRedisplay();

		}
	}
}
void joc2()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);         


										  
	glutPostRedisplay();
	if (myTurn == 1)
	{
		//nume = "Atacati.";
		glutMouseFunc(Mouse2);
		//tab2 e aia goala a oponentului
		tab2.render();

		if (patrate == 15)
		{
			nume = "Ati castigat!";


		

			glutMouseFunc(mousefinal);
			glutDisplayFunc(displayfinal);

		}

		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2i(25, HEIGHT - 50);
		for (int i = 0; i<strlen(nume); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nume[i]);
		glFlush();



	}
	else
	{
		glutMouseFunc(Mouse3);
		nume = "Asteptati.";
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2i(25, HEIGHT - 50);
		for (int i = 0; i<strlen(nume); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nume[i]);
		//tab e a ta.
		tab.render();
		glFlush();
		
		do
		{
			ZeroMemory(buff, 4096);
			ZeroMemory(buff2, 4096);
			ZeroMemory(buff3, 4096);

			if (Conexiune == "Join")
			{
				
				int byteReceived1 = recv(sock, buff, 4096, 0);
				int byteReceived2 = recv(sock, buff2, 4096, 0);
				

				//cout << endl;
				//cout << "SERVER> " << string(buff, 0, byteReceived1).c_str() << endl;
				//cout << "SERVER> " << string(buff2, 0, byteReceived2).c_str() << endl;




				long int X, Y;
				char *pEnd;

				X = strtol(buff, &pEnd, 10);
				Y = strtol(buff2, &pEnd, 10);


				if (X == 1001 && Y == 1001)
				{
					nume = "Ati pierdut!";
					glutMouseFunc(mousefinal);
					glutDisplayFunc(displayfinal);
					break;
				}


				//cout << "SERVER> X=" << X << endl;
				//cout << "SERVER> Y=" << Y << endl;


				if (tab.checkNava(X, Y) == true)
				{
					result = "HIT";
					tab.click(X, Y);
				}
				else
				{
					result = "MISS";
					tab.click(X, Y);
				}
				glFlush();
				//cout << "SERVER> " << result << endl;
				send(sock, result.c_str(), result.length(), 0);

				int byteReceived3 = recv(sock, buff3, 4096, 0);
				//cout << "SERVER> " << string(buff3, 0, byteReceived3).c_str() << endl;


			}
			else
			{
				int byteReceived1 = recv(clientSocket, buff, 4096, 0);
				int byteReceived2 = recv(clientSocket, buff2, 4096, 0);

				/*cout << endl;
				cout << "CLIENT> " << string(buff, 0, byteReceived1).c_str() << endl;
				cout << "CLIENT> " << string(buff2, 0, byteReceived2).c_str() << endl;*/


				long int X, Y;
				char *pEnd;

				X = strtol(buff, &pEnd, 10);
				Y = strtol(buff2, &pEnd, 10);

				if (X == 1001 && Y == 1001)
				{
					nume = "Ati pierdut!";
					glutMouseFunc(mousefinal);
					glutDisplayFunc(displayfinal);
					break;
				}
				//cout << "X=" << X << " Y=" << Y << endl;

				//cout << "CLIENT> X=" << X << endl;
				//cout << "CLIENT> Y=" << Y << endl;

				if (tab.checkNava(X, Y) == true)
				{
					result = "HIT";
					tab.click(X, Y);
				}
				else
				{
					result = "MISS";
					tab.click(X, Y);
				}
				glFlush();

				//cout << "CLIENT> " << result.c_str() << endl;
				send(clientSocket, result.c_str(), result.length(), 0);

				int byteReceived3 = recv(clientSocket, buff3, 4096, 0);
				//cout << "CLIENT> " << string(buff3, 0, byteReceived3).c_str() << endl;


			}

			
			
		} while (strcmp(buff3, "1") == 0);
		

		if (strcmp(buff3, "2") == 0)
		{
			cout << "Primesc 2 ca am pierdut!" << endl;
			nume = "Ati pierdut!";
			glutMouseFunc(mousefinal);
			glutDisplayFunc(displayfinal);

		}
		else
			nume = "Atacati.";

		myTurn = 1;

	}

	




	

}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT&&state == GLUT_DOWN)
	{
		
		patru.click(x, HEIGHT - y);			
		trei1.click(x, HEIGHT - y);
		trei2.click(x, HEIGHT - y);
		trei3.click(x, HEIGHT - y);
		doi.click(x, HEIGHT - y);

		directie.click(x, HEIGHT - y);
		directie2.click(x, HEIGHT - y);

		next1.click(x, HEIGHT - y);

		if (directie.getApasat() == true)
		{
			directie.setApasat(false);
			d1 = 1;
			d2 = 0;
			

		}
		if (directie2.getApasat() == true)
		{
			directie2.setApasat(false);
			d1 = 0;
			d2 = 1;
		}

		if (next1.getApasat() == true)
		{
			if (patru.getDerender() == true && trei1.getDerender() == true && trei2.getDerender() == true && trei3.getDerender() == true && doi.getDerender() == true)
			{

				//send ready;

				if (Conexiune == "Host")
				{
					send(clientSocket, "Ready", 5, 0);
				}
				else
				{
					send(sock, "Ready", 5, 0);
				}

				char ready[200];

				ZeroMemory(ready, 200);

				if (Conexiune == "Host")
				{
					recv(clientSocket, ready, 200, 0);
				}
				else
				{
					recv(sock, ready, 200, 0);
				}

				





				//glutMouseFunc(Mouse2);
				glutDisplayFunc(joc2);
			}
			else
				next1.setApasat(false);
		}

		if (patru.getApasat() == true)
		{

			if (d1)
			{
				if ((HEIGHT - y) > 0 && (HEIGHT - y) < 500)
				{
					if (x < 350)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x + 50, HEIGHT - y) && !tab.checkNonav(x + 100, HEIGHT - y) && !tab.checkNonav(x + 150, HEIGHT - y))
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x + 50, HEIGHT - y);
							tab.clickNava(x + 100, HEIGHT - y);
							tab.clickNava(x + 150, HEIGHT - y);
							patru.setApasat(false);
							patru.setDerender(true);
						}

					}
					if (x>350 && x<500)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x - 50, HEIGHT - y) && !tab.checkNonav(x - 100, HEIGHT - y) && !tab.checkNonav(x - 150, HEIGHT - y))
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x - 50, HEIGHT - y);
							tab.clickNava(x - 100, HEIGHT - y);
							tab.clickNava(x - 150, HEIGHT - y);
							patru.setApasat(false);
							patru.setDerender(true);

						}

					}

				}
			}
			if (d2)
			{
				if ((x) > 0 && (x) < 500)
				{
					if ((HEIGHT - y) < 350)
					{

						if (!tab.checkNonav(x, HEIGHT - y))
							if (!tab.checkNonav(x, HEIGHT - y + 50))
								if (!tab.checkNonav(x, HEIGHT - y + 100))
									if (/*!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x, HEIGHT - y + 50) && !tab.checkNonav(x, HEIGHT - y + 100) &&*/ !tab.checkNonav(x, HEIGHT - y + 150))
									{
										tab.clickNava(x, HEIGHT - y);
										tab.clickNava(x, HEIGHT - y + 50);
										tab.clickNava(x, HEIGHT - y + 100);
										tab.clickNava(x, HEIGHT - y + 150);
										patru.setApasat(false);
										patru.setDerender(true);
									}
					}
					if ((HEIGHT - y)>350 && (HEIGHT - y)<500)
					{
						//cout << tab.checkNonav(x, HEIGHT - y) << " " << tab.checkNonav(x, (HEIGHT - y) - 50) << " " << tab.checkNonav(x, (HEIGHT - y) - 100) << " " << tab.checkNonav(x, (HEIGHT - y) - 150);
						if (!tab.checkNonav(x, HEIGHT - y))
							if (!tab.checkNonav(x, (HEIGHT - y) - 50))
								if (!tab.checkNonav(x, (HEIGHT - y) - 100))
									if (!tab.checkNonav(x, (HEIGHT - y) - 150))
									{
										tab.clickNava(x, HEIGHT - y);
										tab.clickNava(x, HEIGHT - y - 50);
										tab.clickNava(x, HEIGHT - y - 100);
										tab.clickNava(x, HEIGHT - y - 150);
										patru.setApasat(false);
										patru.setDerender(true);
									}

					}
				}

			}


			//patru.setApasat(false);
		}


		if (trei1.getApasat() == true)
		{

			if (d1)
			{
				if ((HEIGHT - y) > 0 && (HEIGHT - y) < 500)
				{
					if (x < 400)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x + 50, HEIGHT - y) && !tab.checkNonav(x + 100, HEIGHT - y) /*&& !tab.checkNonav(x + 150, HEIGHT - y)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x + 50, HEIGHT - y);
							tab.clickNava(x + 100, HEIGHT - y);
							//tab.clickNava(x + 150, HEIGHT - y);
							trei1.setApasat(false);
							trei1.setDerender(true);
						}

					}
					if (x>400 && x<500)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x - 50, HEIGHT - y) && !tab.checkNonav(x - 100, HEIGHT - y) /*&& !tab.checkNonav(x - 150, HEIGHT - y)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x - 50, HEIGHT - y);
							tab.clickNava(x - 100, HEIGHT - y);
							//tab.clickNava(x - 150, HEIGHT - y);
							trei1.setApasat(false);
							trei1.setDerender(true);

						}

					}

				}
			}
			if (d2)
			{
				if ((x) > 0 && (x) < 500)
				{
					if ((HEIGHT - y) < 400)
					{

						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x, HEIGHT - y + 50) && !tab.checkNonav(x, HEIGHT - y + 100) /*&& !tab.checkNonav(x, HEIGHT - y + 150)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x, HEIGHT - y + 50);
							tab.clickNava(x, HEIGHT - y + 100);
							//tab.clickNava(x, HEIGHT - y + 150);
							trei1.setApasat(false);
							trei1.setDerender(true);
						}
					}
					if ((HEIGHT - y)>400 && (HEIGHT - y)<500)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x, HEIGHT - y - 50) && !tab.checkNonav(x, HEIGHT - y - 100) /*&& !tab.checkNonav(x, HEIGHT - y - 150)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x, HEIGHT - y - 50);
							tab.clickNava(x, HEIGHT - y - 100);
							//tab.clickNava(x, HEIGHT - y - 150);
							trei1.setApasat(false);
							trei1.setDerender(true);
						}

					}
				}

			}


			//trei1.setApasat(false);
		}

		if (trei2.getApasat() == true)
		{

			if (d1)
			{
				if ((HEIGHT - y) > 0 && (HEIGHT - y) < 500)
				{
					if (x < 400)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x + 50, HEIGHT - y) && !tab.checkNonav(x + 100, HEIGHT - y)  /* && !tab.checkNonav(x + 150, HEIGHT - y)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x + 50, HEIGHT - y);
							tab.clickNava(x + 100, HEIGHT - y);
							//tab.clickNava(x + 150, HEIGHT - y);
							trei2.setApasat(false);
							trei2.setDerender(true);
						}

					}
					if (x>400 && x<500)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x - 50, HEIGHT - y) && !tab.checkNonav(x - 100, HEIGHT - y)  /* && !tab.checkNonav(x - 150, HEIGHT - y)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x - 50, HEIGHT - y);
							tab.clickNava(x - 100, HEIGHT - y);
							//tab.clickNava(x - 150, HEIGHT - y);
							trei2.setApasat(false);
							trei2.setDerender(true);

						}

					}

				}
			}
			if (d2)
			{
				if ((x) > 0 && (x) < 500)
				{
					if ((HEIGHT - y) < 400)
					{

						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x, HEIGHT - y + 50) && !tab.checkNonav(x, HEIGHT - y + 100) /* && !tab.checkNonav(x, HEIGHT - y + 150)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x, HEIGHT - y + 50);
							tab.clickNava(x, HEIGHT - y + 100);
							//tab.clickNava(x, HEIGHT - y + 150);
							trei2.setApasat(false);
							trei2.setDerender(true);
						}
					}
					if ((HEIGHT - y)>400 && (HEIGHT - y)<500)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x, HEIGHT - y - 50) && !tab.checkNonav(x, HEIGHT - y - 100) /* && && !tab.checkNonav(x, HEIGHT - y - 150)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x, HEIGHT - y - 50);
							tab.clickNava(x, HEIGHT - y - 100);
							//tab.clickNava(x, HEIGHT - y - 150);
							trei2.setApasat(false);
							trei2.setDerender(true);
						}

					}
				}

			}


			//trei2.setApasat(false);
		}

		if (trei3.getApasat() == true)
		{

			if (d1)
			{
				if ((HEIGHT - y) > 0 && (HEIGHT - y) < 500)
				{
					if (x < 400)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x + 50, HEIGHT - y) && !tab.checkNonav(x + 100, HEIGHT - y)/* && !tab.checkNonav(x + 150, HEIGHT - y)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x + 50, HEIGHT - y);
							tab.clickNava(x + 100, HEIGHT - y);
							//tab.clickNava(x + 150, HEIGHT - y);
							trei3.setApasat(false);
							trei3.setDerender(true);
						}

					}
					if (x>400 && x<500)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x - 50, HEIGHT - y) && !tab.checkNonav(x - 100, HEIGHT - y)/* && !tab.checkNonav(x - 150, HEIGHT - y)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x - 50, HEIGHT - y);
							tab.clickNava(x - 100, HEIGHT - y);
							//tab.clickNava(x - 150, HEIGHT - y);
							trei3.setApasat(false);
							trei3.setDerender(true);

						}

					}

				}
			}
			if (d2)
			{
				if ((x) > 0 && (x) < 500)
				{
					if ((HEIGHT - y) < 400)
					{

						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x, HEIGHT - y + 50) && !tab.checkNonav(x, HEIGHT - y + 100) /*&& !tab.checkNonav(x, HEIGHT - y + 150)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x, HEIGHT - y + 50);
							tab.clickNava(x, HEIGHT - y + 100);
							//tab.clickNava(x, HEIGHT - y + 150);
							trei3.setApasat(false);
							trei3.setDerender(true);
						}
					}
					if ((HEIGHT - y)>400 && (HEIGHT - y)<500)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x, HEIGHT - y - 50) && !tab.checkNonav(x, HEIGHT - y - 100) /*&& && !tab.checkNonav(x, HEIGHT - y - 150)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x, HEIGHT - y - 50);
							tab.clickNava(x, HEIGHT - y - 100);
							//tab.clickNava(x, HEIGHT - y - 150);
							trei3.setApasat(false);
							trei3.setDerender(true);
						}

					}
				}

			}


			//trei3.setApasat(false);
		}


		if (doi.getApasat() == true)
		{

			if (d1)
			{
				if ((HEIGHT - y) > 0 && (HEIGHT - y) < 500)
				{
					if (x < 450)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x + 50, HEIGHT - y) /*&& !tab.checkNonav(x + 100, HEIGHT - y) && !tab.checkNonav(x + 150, HEIGHT - y)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x + 50, HEIGHT - y);
							//tab.clickNava(x + 100, HEIGHT - y);
							//tab.clickNava(x + 150, HEIGHT - y);
							doi.setApasat(false);
							doi.setDerender(true);
						}

					}
					if (x>450 && x<500)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x - 50, HEIGHT - y) /*&& !tab.checkNonav(x - 100, HEIGHT - y) && !tab.checkNonav(x - 150, HEIGHT - y)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x - 50, HEIGHT - y);
							//tab.clickNava(x - 100, HEIGHT - y);
							//tab.clickNava(x - 150, HEIGHT - y);
							doi.setApasat(false);
							doi.setDerender(true);

						}

					}

				}
			}
			if (d2)
			{
				if ((x) > 0 && (x) < 500)
				{
					if ((HEIGHT - y) < 450)
					{

						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x, HEIGHT - y + 50) /*&& !tab.checkNonav(x, HEIGHT - y + 100) && !tab.checkNonav(x, HEIGHT - y + 150)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x, HEIGHT - y + 50);
							//tab.clickNava(x, HEIGHT - y + 100);
							//tab.clickNava(x, HEIGHT - y + 150);
							doi.setApasat(false);
							doi.setDerender(true);
						}
					}
					if ((HEIGHT - y)>450 && (HEIGHT - y)<500)
					{
						if (!tab.checkNonav(x, HEIGHT - y) && !tab.checkNonav(x, HEIGHT - y - 50) /*&& !tab.checkNonav(x, HEIGHT - y - 100) && !tab.checkNonav(x, HEIGHT - y - 150)*/)
						{
							tab.clickNava(x, HEIGHT - y);
							tab.clickNava(x, HEIGHT - y - 50);
							//tab.clickNava(x, HEIGHT - y - 100);
							//tab.clickNava(x, HEIGHT - y - 150);
							doi.setApasat(false);
							doi.setDerender(true);
						}

					}
				}

			}



		}

		
	}

}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	//gluOrtho2D(-400.0, 400.0, -300.0, 300.0);
}

void displayjoc() {
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);         

	const char *nume = "Alegeti navetele.";
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2i(25, HEIGHT - 50);
	for (int i = 0; i<strlen(nume); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nume[i]);

	// Pentru desenarea tabelei de joc. 
	tab.render();

	// Pentru desenarea butonului care iti permite plasarea navetei de 4 spatii.
	patru.render();

	// Pentru desenarea butonului care iti permite plasarea celor 3 navete de 3 spatii.
	trei1.render();
	trei2.render();
	trei3.render();

	doi.render();

	// Pentru desenarea butonului care va arata directia navetei.
	directie.render();
	directie2.render();

	next1.render();


	glFlush(); 


}

void MouseMeniu(int button, int state, int x, int y)
{
	cout << "MouseFunc.";
	if (button == GLUT_LEFT&&state == GLUT_DOWN)
	{
		
		exit1.click(x, HEIGHT - y);
		if (exit1.getApasat() == true)
		{
			exit(EXIT_SUCCESS);
		}

		host.click(x, HEIGHT - y);
		if (host.getApasat() == true)
		{
			glutMouseFunc(Mouse);
			glutDisplayFunc(displayjoc);
			start.setNume("Start");
			start.setApasat(false);
			Conexiune = "Host";
			myTurn = 1;
			initSocketHost(myIpAddress,hint,listening,clientSocket,client,sock);
		}
		join.click(x, HEIGHT - y);
		if (join.getApasat() == true)
		{
			glutMouseFunc(Mouse);
			glutDisplayFunc(displayjoc);
			start.setNume("Start");
			start.setApasat(false);
			Conexiune = "Join";
			myTurn = 0;
			initSocketClient(ipAddress,hint,listening,clientSocket,client,sock);

		}
		delet.click(x, HEIGHT - y);
		if (delet.getApasat() == true)
		{
			z--;
			delet.setApasat(false);
		}

		acc.click(x, HEIGHT - y);
		if (acc.getApasat() == true)
		{
			ip2 = new char[z];
			for (int i = 0; i < z; i++)
				ip2[i] = ip[i];
			string IP(ip2);

			ipAddress = IP;
			//cout << endl;
			//cout << "ipAddress:" << ipAddress.c_str();
			//cout << endl;
		}



	}

}

void Keyboard(unsigned char k, int x, int y)
{
	cout << "KeyboardFunc.";

	if (k == 27)
	{
		exit(0);
	}
	/*if (k == 'a')
	{
		glutFullScreen();
	}*/
	if (k == '1')
	{
		ip[z] = '1';
		z++;

		//displaymeniu();
	}
	if (k == '2')
	{
		ip[z] = '2';
		z++;

	}
	if (k == '3')
	{
		ip[z] = '3';
		z++;

	}
	if (k == '4')
	{
		ip[z] = '4';
		z++;

	}
	if (k == '5')
	{
		ip[z] = '5';
		z++;

	}
	if (k == '6')
	{
		ip[z] = '6';
		z++;
	}
	if (k == '7')
	{
		ip[z] = '7';
		z++;

	}
	if (k == '8')
	{
		ip[z] = '8';
		z++;

	}
	if (k == '9')
	{
		ip[z] = '9';
		z++;

	}
	if (k == '0')
	{
		ip[z] = '0';
		z++;

	}
	if (k == '.')
	{
		ip[z] = '.';
		z++;


	}
	if (k == GLUT_KEY_DELETE)
	{
		z--;

	}
	cout << "z=" << z;
	if (z > 15)
		z = 15;
	cout << "z=" << z;
	glutPostRedisplay();
}

void displayfinal()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2i(25, HEIGHT - 50);
	for (int i = 0; i<strlen(nume); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nume[i]);

	exit1.render();

	glFlush();
}

void mousefinal(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT&&state == GLUT_DOWN)
	{
		exit1.click(x, HEIGHT - y);
		if (exit1.getApasat() == true)
		{
			if (Conexiune == "Host")
			{
				finalizeSocketHost(clientSocket);
			}
			else
				finalizeSocketClient(sock);
			exit(EXIT_SUCCESS);
		}
	}

}



void displaymeniu()
{
	cout << "Display.";

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2i(25, HEIGHT - 50);

	for (int i = 0; i < z; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ip[i]);
	}

	glRasterPos2i(450, HEIGHT - 50);

	for (int i = 0; i < myIpAddress.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, myIpAddress[i]);
	}

	const char * text = "Ip-ul Local";

	glRasterPos2i(450, HEIGHT - 20);

	for (int i = 0; i < strlen(text); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}

	//start.render();
	delet.render();
	acc.render();
	//info.render();
	host.render();
	if (acc.getApasat() == true)
		join.render();



	exit1.render();


	glFlush();

}

void reshapeScene(GLint width, GLint height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int w = height * ASPECT;           // w is width adjusted for aspect ratio
	int left = (width - w) / 2;
	glViewport(0, 0, width, height);       // fix up the viewport to maintain aspect ratio
	gluOrtho2D(0, width, 0, height);   // only the window is changing, not the camera
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	IPv4 myIp;

	getMyIP(myIp);



	myIpAddress.append(to_string(myIp.b1));
	myIpAddress.append(".");
	myIpAddress.append(to_string(myIp.b2));
	myIpAddress.append(".");
	myIpAddress.append(to_string(myIp.b3));
	myIpAddress.append(".");
	myIpAddress.append(to_string(myIp.b4));

	cout << "myIPADDRESS:" << myIpAddress.c_str();

	glutInit(&argc, argv);                 // Initialize GLUT
										   //glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
	glutInitWindowSize(800, 600);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Battle Ship"); // Create a window with the given title
	init();
	glutDisplayFunc(displaymeniu); // Register display callback handler for window re-paint
	glutReshapeFunc(reshapeScene);
	glutMouseFunc(MouseMeniu);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();           // Enter the event-processing loop





	return 0;
}