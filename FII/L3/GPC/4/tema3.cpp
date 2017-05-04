#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

using namespace std;


#define dim 600

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

#define PI 4 * atan(1.0)

unsigned char prevKey;


class Pixel {
public:
	int x;
	int y;
	Pixel(int lin, int col)
	{
		y = col;
		x = lin;
	}
};



class Grid {
public:
	Grid(int, int);
	void write_pixel(const Pixel&);
	void write_pixel(const int&, const int&);
	void write_pixel_border(const int&, const int&);
	void show_seg3(const Pixel &p1, const Pixel &p2, bool);

private:
	int lines;
	int columns;

	float start;
	float endX;
	float endY;
	float len;
	float radius;

};


Grid::Grid(int l, int c)
{
	lines = --l;
	columns = --c;

	int max_dim = max(c, l);
	len = 2.0 / (max_dim + 2);
	radius = len / 5;

	start = -1 + len;
	endX = -1 + (c + 1)*len;
	endY = -1 + (l + 1)*len;

	if (l < 1 || c < 1)
		return;

	glColor3f(0, 0, 0); // black

	for (int i = 0; i <= l; ++i)
	{
		float x = start + len * i;

		glBegin(GL_LINES);
		glVertex2f(start, x);
		glVertex2f(endX, x);
		glEnd();
	}

	for (int i = 0; i <= c; ++i)
	{
		float y = start + i * len;

		glBegin(GL_LINES);
		glVertex2f(y, start);
		glVertex2f(y, endY);
		glEnd();
	}
}

void Grid::write_pixel(const int &xx, const int &yy)
{
	float y = start + len * yy;
	float x = start + len * xx;

	if (x > endX || y > endY || x < start || y < start)
		return;

	glColor3f(0.5, 0.5, 0.5); // gri

	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 12)
		glVertex2f(x + sin(i) * radius, y + cos(i) * radius);
	glEnd();
}


void Grid::write_pixel(const Pixel &a)
{
	float y = start + len * a.y;
	float x = start + len * a.x;

	if (x > endX || y > endY || x < start || y < start)
		return;

	glColor3f(0.5, 0.5, 0.5); // gri

	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 6)
		glVertex2f(x + sin(i) * radius, y + cos(i) * radius);
	glEnd();

}
void Grid::write_pixel_border(const int& x, const int& y)
{
	write_pixel(x, y);
	write_pixel(x, y+1);
	write_pixel(x+1, y-1);
	write_pixel(x+1, y);
	write_pixel(x+1, y+1);
	write_pixel(x-1, y-1);
	write_pixel(x-1, y);
	write_pixel(x-1, y+1);
	write_pixel(x, y-1);
}

void Grid::show_seg3(const Pixel &p1, const Pixel &p2, bool border=false)
{
	int x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;

	if (p1.x > p2.x) {
		x1 = p2.x;
		y1 = p2.y;
		x2 = p1.x;
		y2 = p1.y;
	}

	glColor3f(1, 0, 0); // red

	glBegin(GL_LINES);
	glVertex2f(start + x1 * len, start + y1 * len);
	glVertex2f(start + x2 * len, start + y2 * len);
	glEnd();


	int dx = x2 - x1, dy = y2 - y1;
	int d = 2 * dy - dx;

	int dE = 2 * dy;
	int dNE = 2 * (dy - dx);
	int dSE = 2 * (-dy - dx);

	int x = x1, y = y1;

	write_pixel(x, y);

	if (y2 > y1) {
		while (x < x2) {
			if (d <= 0) {
				// pcik E
				d += dE;
				++x;
			} else {
				// pick NE
				d += dNE;
				++x;
				++y;
			}
			if (!border)
				write_pixel(x, y);
			else
				write_pixel_border(x, y);
		}
	} else {
		x = x1, y = y1;
		d = -2 * dy - dx;
		dE = -2 * dy;

		while (x < x2) {
			if (d <= 0) {
				// pick E
				d += dE;
				++x;
			} else {
				// pick SE
				d += dSE;
				++x;
				--y;
			}

			if (!border)
				write_pixel(x, y);
			else
				write_pixel_border(x, y);
		}
	}
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	Pixel p1(0, 0);
	Grid g(16, 16);

	Pixel p2(15, 7), p3(0,15), p4(15,10);

	g.show_seg3(p1, p2);
	g.show_seg3(p3, p4, true);

	glFlush();
}

void Init(void)
{

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	prevKey = key;
	if (key == 27)
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
	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}
