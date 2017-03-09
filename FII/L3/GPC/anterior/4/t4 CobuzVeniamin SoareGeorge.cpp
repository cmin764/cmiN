
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

using namespace std;

#define dim 500
#define PI 4 * atan(1.0)
#define DEG2RAD PI/180.0

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
	void writePixel_contur2(const int&, const int&);
	void AfisareCerc4(int r);
	void UmplereElipsa(int, int, int, int);
	void AfisarePuncteElipsa(int x, int y,int x0, int y0);
	void DesenareElipsa(int radiusX, int radiusY, int x, int y);


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
	raza = len / 4;

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

	glColor3f(0.3, 0.3, 0.3); // gri

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

	glColor3f(0.3, 0.3, 0.3); // gri

	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 6) 
		glVertex2f(x + sin(i) * raza, y + cos(i) * raza);


	glEnd();

}

void Grila::writePixel_contur(const int& x, const int& y)
{
	writePixel(x - 1, y - 1);
	writePixel(x - 1, y);
	writePixel(x - 1, y + 1);
	writePixel(x, y - 1);
	writePixel(x, y);
	writePixel(x, y + 1);
	writePixel(x + 1, y - 1);
	writePixel(x + 1, y);
	writePixel(x + 1, y + 1);
}

void Grila::writePixel_contur2(const int &x, const int &y)
{
	writePixel(x - 1, y);
	writePixel(x, y);
	writePixel(x + 1, y);
}

void Grila::AfisareCerc4(int r)
{
	glLineWidth(5);	
	double R = r*len;

	if (R-1 > finishX || R-1 > finishY)
	{
		cout << "R > coord!!\n";
		return;
	}
	
	glColor3f(1, 0, 0); // rosu
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < PI / 2; i += PI / 36)
		glVertex2f(start + cos(i) * R, start + sin(i) * R);

	glEnd();

	int x = r, y = 0;
	int d = 1 - r;
	int dV = 3, dNV = 2 * r - 5;

	writePixel_contur2(x, y);
	while (x>y)
	{
		if (d < 0)
		{
			d += dV;
			dV += 2;
			dNV -= 2;
		}
		else
		{
			d -= dNV;
			dV += 2;
			dNV -= 4;
			x--;
		}

		y++;

		writePixel_contur2(x, y);
	}
}


void Grila::UmplereElipsa(int x0, int y0, int a, int b)
{
	DesenareElipsa(a, b, x0, y0);

	/*int xi = 0, x = 0, y = -b;
	double fxpyp = 0;
	double dV, dNV, dN;

	AfisarePuncteElipsa(x, y, x0, y0);

	while (a*a*(y - 0.5) > -b*b*(x + 1))
	{
		dV = -b*b*(2 * x + 1);
		dNV = -b*b*(2 * x + 1) - a*a*(-2 * y + 1);
		if (fxpyp + dV <= 0)
		{
			fxpyp += dV;
			x--;
		}
		else if (fxpyp + dNV <= 0)
		{
			fxpyp += dNV;
			x--;
			y++;
		}
		AfisarePuncteElipsa(x, y, x0, y0);
	}

	while (y < 0)
	{
		dN = -b*b*(-2 * x + 1);
		dNV = -b*b*(2 * x + 1) -a*a*(-2 * y + 1);
		if (fxpyp + dNV <= 0)
		{
			fxpyp += dNV;
			x--; y++;
		}
		else
		{
			fxpyp += dN;
			y++;
		}
		AfisarePuncteElipsa(x, y, x0, y0);
	}*/

	
	int xi = 0, x = 0, y = b;
	double fxpyp = 0;
	double dE, dSE, dS;

	AfisarePuncteElipsa(x, y, x0, y0);
	
	while (a*a*(y - 0.5) > b*b*(x + 1))
	{
		dE = b*b*(2 * x + 1);
		dSE = b*b*(2 * x + 1) + a*a*(-2 * y + 1);
		if (fxpyp + dE <= 0)
		{
			fxpyp += dE;
			x++;
		}
		else if (fxpyp + dSE <= 0)
		{
			fxpyp += dSE;
			x++;
			y--;
		}
		AfisarePuncteElipsa(x, y, x0, y0);
	}

	while (y > 0)
	{
		dS = b*b*(-2 * x + 1);
		dSE = b*b*(2 * x + 1) + a*a*(-2 * y + 1);
		if (fxpyp + dSE <= 0)
		{
			fxpyp += dSE;
			x++; y--;
		}
		else 
		{
			fxpyp += dS;
			y--;
		}
		AfisarePuncteElipsa(x, y, x0, y0);
	}
	
}

void Grila::AfisarePuncteElipsa(int x, int y, int x0, int y0)
{
	//writePixel(x0 + x, y0 + y);

	/*for (int i = 0; i <= y; i++)
	{
		writePixel(x0 + x, y0 + y - i);
	}*/

	for (int i = 0; i <= y; i++)
	{
		writePixel(x0 - x, y0 - y + i);
	}


	/*for (int i = 0; i <= y; i++)
	{
		writePixel(x0 + x, y0 + y - i);
	}*/
}

void Grila::DesenareElipsa(int radiusX, int radiusY, int x, int y)
{
	int i;
	glLineWidth(5);
	double rx = radiusX*len;
	double ry = radiusY*len;

	glColor3f(1, 0, 0); // rosu
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 2*PI; i += PI / 24)
		glVertex2f(start + x*len + cos(i) * rx, start + y*len + sin(i) * ry);

	glEnd();
}

void ex1()
{
	Grila g(16, 16);
	
	g.AfisareCerc4(13);
	
}

void ex2()
{
	Grila g(29, 29);
	g.UmplereElipsa(14, 8, 14, 8);

}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	ex1();
	//ex2();


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