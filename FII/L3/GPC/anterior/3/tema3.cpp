
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

using namespace std;

#define dim 500
#define PI 4 * atan(1.0)

unsigned char prevKey;

float max(float a, float b)
{
	return a > b ? a : b;
}

float min(float a, float b)
{
	return a < b ? a : b;
}


class Pixel 
{
public:
	int x;
	int y;
	Pixel(int line, int col)
	{
		x = line;
		y = col;
	}
};



class Grila
{
public:
	Grila(int, int);
	void writePixel(const Pixel&);
	void writePixel(const int&, const int&);
	void writePixel_contur(const int&, const int&);
	void afisareSegmentDreapta3(const Pixel &p1, const Pixel &p2, bool);


private:
	int lines;
	int cols;


	float start;
	float finishX;
	float finishY;
	float len;
	float raza;

};


Grila::Grila(int l, int c)
{
	lines = --l;
	cols = --c;

	int max_s = max(c, l);
	len = 2.0 / (max_s + 2);
	raza = len / 5;

	start = -1 + len;
	finishX = -1 + (c + 1)*len;
	finishY = -1 + (l + 1)*len;
	
	if (l < 1 || c < 1)
		return;

	glColor3f(0, 0, 0); // negru
	
	for (int i = 0; i <= l; i++)
	{
		float x = start + i*len;
		glBegin(GL_LINES);
		glVertex2f(start, x);
		glVertex2f(finishX, x);
		glEnd();
	}

	for (int i = 0; i <= c; i++)
	{
		float y = start + i*len;
		glBegin(GL_LINES);
		glVertex2f(y, start);
		glVertex2f(y, finishY);
		glEnd();
	}

}

void Grila::writePixel(const int &xx, const int &yy)
{
	float x = start + xx*len;
	float y = start + yy*len;

	if (x > finishX || y > finishY || x < start || y < start)
		return;

	glColor3f(0.5, 0.5, 0.5); // gri

	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 12)
		glVertex2f(x + sin(i) * raza, y + cos(i) * raza);


	glEnd();
}


void Grila::writePixel(const Pixel &a)
{
	float x = start + a.x*len;
	float y = start + a.y*len;

	if (x > finishX || y > finishY || x < start || y < start)
		return;

	glColor3f(0.5, 0.5, 0.5); // gri

	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 6) 
		glVertex2f(x + sin(i) * raza, y + cos(i) * raza);


	glEnd();

}
void Grila::writePixel_contur(const int& x, const int& y)
{
	writePixel(x-1, y-1);
	writePixel(x-1, y);
	writePixel(x-1, y+1);
	writePixel(x, y-1);
	writePixel(x, y);
	writePixel(x, y+1);
	writePixel(x+1, y-1);
	writePixel(x+1, y);
	writePixel(x+1, y+1);
}

void Grila::afisareSegmentDreapta3(const Pixel &p1, const Pixel &p2, bool contur = false)
{
	int x0 = p1.x, y0 = p1.y, xn = p2.x, yn = p2.y;

	if (p1.x > p2.x)
	{
		x0 = p2.x;
		y0 = p2.y;
		xn = p1.x;
		yn = p1.y;
	}

	glColor3f(1, 0, 0); // rosu
	glBegin(GL_LINES);
	glVertex2f(start + x0*len, start + y0*len);
	glVertex2f(start + xn*len, start + yn*len);
	glEnd();
	

	int dx = xn - x0, dy = yn - y0;
	int d = 2 * dy - dx;
	int dE = 2 * dy;
	int dNE = 2 * (dy - dx);
	int dSE = 2 * (-dy - dx);

	
	int x = x0, y = y0;

	writePixel(x, y);

	if (yn > y0)
	{
		while (x < xn)
		{			
			if (d <= 0)
			{			
				// alegem E
				d += dE;
				x++;
			}
			else
			{
				//alegem NE
				d += dNE;
				x++;
				y++;
			}
			if (!contur)
				writePixel(x, y);
			else
				writePixel_contur(x, y);
		}
	}
	else
	{
		x = x0, y = y0;
		d = - 2 * dy - dx;
		dE = - 2 * dy;

		while (x < xn)
		{
			
			if (d <= 0)
			{
				// alegem E
				d += dE;
				x++;
			}
			else
			{
				//alegem SE
				d += dSE;
				x++;
				y--;
			}

			if (!contur)
				writePixel(x, y);
			else
				writePixel_contur(x, y);
		}
	}

}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	Pixel p1(0, 0);
	Grila g(16, 16);

	//g.writePixel(p1);


	Pixel p2(15, 7), p3(0,15), p4(15,10);

	g.afisareSegmentDreapta3(p1, p2);
	g.afisareSegmentDreapta3(p3, p4, true);


	glFlush();
}

void Init(void)
{

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Reshape(int w, int h) 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) 
{
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(">>> Grila <<<");

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}