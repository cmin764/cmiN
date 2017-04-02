#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

using namespace std;


#define dim 600

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a < b ? a : b)

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
	void put_pixel(const Pixel&);
	void put_pixel(const int&, const int&);
	void put_pixel_stroke(const int&, const int&);
	void show_seg3(const Pixel &p1, const Pixel &p2, bool);

private:
	int lines;
	int columns;

	float begin;
	float end_my_x;
	float end_my_y;
	float length;
	float radius;

};


Grid::Grid(int l, int c)
{
	lines = --l;
	columns = --c;

	int max_dim = max(c, l);
	length = 2.0 / (max_dim + 2);
	radius = length / 5;

	begin = -1 + length;
	end_my_x = -1 + (c + 1)*length;
	end_my_y = -1 + (l + 1)*length;

	if (l < 1 || c < 1)
		return;

	glColor3f(0, 0, 0); // black

	for (int i = 0; i <= l; ++i)
	{
		float x = begin + length * i;

		glBegin(GL_LINES);
		glVertex2f(begin, x);
		glVertex2f(end_my_x, x);
		glEnd();
	}

	for (int i = 0; i <= c; ++i)
	{
		float y = begin + i * length;

		glBegin(GL_LINES);
		glVertex2f(y, begin);
		glVertex2f(y, end_my_y);
		glEnd();
	}
}

void Grid::put_pixel(const int &xx, const int &yy)
{
	float y = begin + length * yy;
	float x = begin + length * xx;

	if (x > end_my_x || y > end_my_y || x < begin || y < begin)
		return;

	glColor3f(0.5, 0.5, 0.5); // gri

	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 12)
		glVertex2f(x + sin(i) * radius, y + cos(i) * radius);
	glEnd();
}


void Grid::put_pixel(const Pixel &a)
{
	float y = begin + length * a.y;
	float x = begin + length * a.x;

	if (x > end_my_x || y > end_my_y || x < begin || y < begin)
		return;

	glColor3f(0.5, 0.5, 0.5); // gri

	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 6)
		glVertex2f(x + sin(i) * radius, y + cos(i) * radius);
	glEnd();

}
void Grid::put_pixel_stroke(const int& x, const int& y)
{
	put_pixel(x, y);
	put_pixel(x, y+1);
	put_pixel(x+1, y-1);
	put_pixel(x+1, y);
	put_pixel(x+1, y+1);
	put_pixel(x-1, y-1);
	put_pixel(x-1, y);
	put_pixel(x-1, y+1);
	put_pixel(x, y-1);
}

void Grid::show_seg3(const Pixel &p1, const Pixel &p2, bool stroke=false)
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
	glVertex2f(begin + x1 * length, begin + y1 * length);
	glVertex2f(begin + x2 * length, begin + y2 * length);
	glEnd();


	int dx = x2 - x1, dy = y2 - y1;
	int d = 2 * dy - dx;

	int dE = 2 * dy;
	int dNE = 2 * (dy - dx);
	int dSE = 2 * (-dy - dx);

	int x = x1, y = y1;

	put_pixel(x, y);

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
			if (!stroke)
				put_pixel(x, y);
			else
				put_pixel_stroke(x, y);
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

			if (!stroke)
				put_pixel(x, y);
			else
				put_pixel_stroke(x, y);
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
	if (key == 27)    // Esc
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
