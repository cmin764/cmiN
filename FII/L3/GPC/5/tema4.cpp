#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include <GL/glut.h>


using namespace std;

#define DIM 500
#define DOM_SCAN 100
#define PI 4 * atan(1.0)
#define EPS 0.00000001
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


class Pixel {
public:
	int x;
	int y;
	Pixel()
	{
		x = y = 0;
	}
	Pixel(int lin, int col)
	{
		x = lin;
		y = col;
	}
};


class Edge {
public:
	Pixel vi, vf;
	Edge(Pixel a, Pixel b)
	{
		vi = a;
		vf = b;
	}
};


struct Intersection  {
	int ymax;
	double xmin;
	double ratio;

	Intersection(int ymax, double xmin, double ratio) :
		ymax(ymax), xmin(xmin), ratio(ratio) {}
};


typedef vector<Edge> vmuc_t;
typedef vector<Intersection> vint_t;
typedef vector<vint_t> mint_t;


bool ssm_comp(const Intersection & first, const Intersection & second)
{
	return first.xmin < second.xmin;
}


class Grid {
public:
	Grid(int, int);
	void write_pixel(const Pixel&);
	void write_pixel(const int&, const int&);
	void write_pixel_border(const int&, const int&);
	void write_pixel_border2(const int&, const int&);

	void show_circle_4(int r);

	void fill_elipse(int, int, int, int);
	void show_elipse_dots(int, int, int, int);
	void draw_elipse(int, int, int, int);

	void poly_read(vmuc_t&, const char[]);
	void draw_poly(vmuc_t& poly);
	void initialize(vmuc_t&, mint_t&);
	void computessm(vmuc_t&, mint_t&, mint_t&);
	void colorize(const mint_t&);
	void adapt(double&, double&);

private:
	int lines;
	int columns;

	float start;
	float endX;
	float endY;
	float len;
	float radius;
};


Grid::Grid(int lin, int col)
{
	glLineWidth(1);
	lines = --lin;
	columns = --col;

	int max_s = max(col, lin);
	len = 2.0 / (max_s + 2);
	radius = len / 4;

	start = -1 + len;
	endX = -1 + (col + 1) * len;
	endY = -1 + (lin + 1) * len;

	if (lin < 1 || col < 1)
		return;

	glColor3f(0, 0, 0);    // black

	for (int i = 0; i <= lin; ++i) {
		float x = start + i * len;
		glBegin(GL_LINES);
		glVertex2f(start, x);
		glVertex2f(endX, x);
		glEnd();
	}

	for (int i = 0; i <= col; ++i) {
		float y = start + i * len;
		glBegin(GL_LINES);
		glVertex2f(y, start);
		glVertex2f(y, endY);
		glEnd();
	}
}

void Grid::write_pixel(const int &myx, const int &myy)
{
	float x = start + myx * len;
	float y = start + myy * len;

	if (x > endX || y > endY || x < start || y < start)
		return;

	glColor3f(0.3, 0.3, 0.3);    // grey

	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 12)
		glVertex2f(x + sin(i) * radius, y + cos(i) * radius);
	glEnd();
}

void Grid::write_pixel(const Pixel &p)
{
	float x = start + p.x * len;
	float y = start + p.y * len;

	if (x > endX || y > endY || x < start || y < start)
		return;

	glColor3f(0.3, 0.3, 0.3);    // grey

	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 6)
		glVertex2f(x + sin(i) * radius, y + cos(i) * radius);
	glEnd();

}

void Grid::write_pixel_border(const int& x, const int& y)
{
	write_pixel(x - 1, y - 1);
	write_pixel(x - 1, y);
	write_pixel(x - 1, y + 1);
	write_pixel(x, y - 1);
	write_pixel(x, y);
	write_pixel(x, y + 1);
	write_pixel(x + 1, y - 1);
	write_pixel(x + 1, y);
	write_pixel(x + 1, y + 1);
}

void Grid::write_pixel_border2(const int &x, const int &y)
{
	write_pixel(x - 1, y);
	write_pixel(x, y);
	write_pixel(x + 1, y);
}

void Grid::show_circle_4(int r)
{
	glLineWidth(5);
	double big_radius = r * len;

	if (big_radius - 1 > endX || big_radius - 1 > endY) {
		cout << "big_radius coord issue" << endl;
		return;
	}

	glColor3f(1, 0, 0);    // red
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < PI / 2; i += PI / 36)
		glVertex2f(start + cos(i) * big_radius, start + sin(i) * big_radius);
	glEnd();

	int x = r;
	int y = 0;
	int d = 1 - r;
	int dV = 3;
	int dNV = 2 * r - 5;

	write_pixel_border2(x, y);
	while (x > y) {
		if (d < 0) {
			d += dV;
			dV += 2;
			dNV -= 2;
		} else {
			d -= dNV;
			dV += 2;
			dNV -= 4;
			x--;
		}

		y++;
		write_pixel_border2(x, y);
	}
}


void Grid::fill_elipse(int x0, int y0, int a, int b)
{
	draw_elipse(a, b, x0, y0);

	int x = 0, y = b;
	double fxpyp = 0;
	double dE, dSE, dS;

	show_elipse_dots(x, y, x0, y0);

	while (a * a * (y - 0.5) > b * b * (x + 1)) {
		dE = b * b * (2 * x + 1);
		dSE = b * b * (2 * x + 1) + a * a * (-2 * y + 1);
		if (fxpyp + dE <= 0) {
			fxpyp += dE;
			x++;
		}
		else if (fxpyp + dSE <= 0) {
			fxpyp += dSE;
			x++;
			y--;
		}
		show_elipse_dots(x, y, x0, y0);
	}

	while (y > 0)
	{
		dS = b * b * (-2 * x + 1);
		dSE = b * b * (2 * x + 1) + a*a*(-2 * y + 1);
		if (fxpyp + dSE <= 0) {
			fxpyp += dSE;
			++x;
			--y;
		} else {
			fxpyp += dS;
			--y;
		}
		show_elipse_dots(x, y, x0, y0);
	}
}

void Grid::show_elipse_dots(int x, int y, int x0, int y0)
{
	for (int i = 0; i <= y; i++) {
		write_pixel(x0 - x, y0 - y + i);
	}
}

void Grid::draw_elipse(int rad_x, int rad_y, int x, int y)
{
	glLineWidth(5);
	double rx = rad_x * len;
	double ry = rad_y * len;

	glColor3f(1, 0, 0);    // red
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 2 * PI; i += PI / 24)
		glVertex2f(start + x * len + cos(i) * rx,
				   start + y * len + sin(i) * ry);
	glEnd();
}


void Grid::poly_read(vmuc_t& poly, const char fname[])
{
	ifstream fin(fname);
	int nr;
	fin >> nr;
	int a, b;
	fin >> a >> b;
	Pixel p1(a, b);
	Pixel p0(p1);
	while (--nr > 0) {
		fin >> a >> b;
		Pixel p2(a, b);
		Edge m(p1, p2);
		poly.push_back(m);
		p1 = p2;
	}
	Edge m(p1, p0);
	poly.push_back(m);  // nu trebuie, pentru ca loop

	// for (auto x : poly) {
	// 	cout << x.vi.x << " " << x.vi.y << endl;
	// 	cout << x.vf.x << " " << x.vf.y << endl;
	// }
}


void Grid::draw_poly(vmuc_t& poly)
{
	// cout << "desenez" << endl;
	glLineWidth(3);
	glColor3f(1, 0, 0); // rosu
	glBegin(GL_LINE_LOOP);

	// glVertex2f(start, start);
	// glVertex2f(start + len, start + len);
	for (auto x : poly) {
		// cout << x.vi.x << " " << x.vi.y << endl;
		glVertex2f(start + x.vi.x * len, start + x.vi.y * len);
	}
	glEnd();
}

void Grid::initialize(vmuc_t& poly, mint_t& lista)
{
	int xm,ym,xM,yM;
	bool change;
	lista.resize(DOM_SCAN);
	for (auto m : poly) {
	// pentru fiecare muchie din poligon ...
		if (m.vi.y != m.vf.y) {
		// ... care nu este orizontala
			ym = min(m.vi.y, m.vf.y);
			yM = max(m.vi.y, m.vf.y);
			xm = (ym == m.vi.y) ? m.vi.x : m.vf.x;
			xM = (yM == m.vi.y) ? m.vi.x : m.vf.x;
			lista[ym].push_back(Intersection(yM, (double)xm,
				double(xm - xM) / (ym - yM)));
		}
	}

	for (int i = 0; i < DOM_SCAN; ++i) {
		change = true;
		while (change) {
			change = false;
			if (lista[i].size() == 0) break;
			for (unsigned int j = 0; j < lista[i].size() - 1; ++j) {
				if (lista[i][j].xmin > lista[i][j+1].xmin) {
					swap(lista[i][j], lista[i][j + 1]);
					change = true;
				}
			}
		}
	}
}


void Grid::computessm(vmuc_t& poly, mint_t& et, mint_t& fin)
{
	vint_t ssm;
	int y;
	fin.resize(DOM_SCAN);
	// et.resize(DOM_SCAN);

	y = -1;
	for (int i = 0; i < DOM_SCAN; ++i) {
		if (et[i].size()) {
			y = i;
			break;
		}
	}

	if (y < 0 || y >= DOM_SCAN) return;

	do {
		ssm.insert(ssm.end(), et[y].begin(), et[y].end());
		for (unsigned int i = 0; i < ssm.size(); ++i) {
			if (ssm[i].ymax == y) {
				ssm.erase(ssm.begin() + i);
				--i;
			}
		}
		sort(ssm.begin(), ssm.end(), ssm_comp);
		fin[y].insert(fin[y].begin(), ssm.begin(), ssm.end());
		++y;

		for (unsigned int i = 0; i < ssm.size(); ++i) {
			if (ssm[i].ratio) {
				ssm[i].xmin += ssm[i].ratio;
			}
		}
	} while (!ssm.empty() || !et[y].empty());
}


bool equal(double a, double b)
{
	return fabs(a - b) < EPS;
}


void Grid::adapt(double & lo, double & hi)
{
	if (not equal(lo, hi)) {
		lo = round(lo);
		if (equal(hi, round(hi))) {
			hi -= 1;
		} else {
			hi = floor(hi);
		}
	}

	lo = (int)lo;
	hi = (int)hi;
}


void Grid::colorize(const mint_t& ssms)
{
	for (unsigned int y = 0; y < ssms.size(); ++y) {
		// cout << "y: " << y << endl;
		// for (auto x : ssms[y]) {
		// 	cout << x.ymax << " " << x.xmin << " " << x.ratio << endl;
 	// 	}
		// cout << endl;

		for (unsigned int i = 0; i < ssms[y].size(); i += 2) {
			double lo, hi;
			lo = ssms[y][i].xmin;
			hi = ssms[y][i + 1].xmin;
			adapt(lo, hi);

			// deseneaza de la lo pana la hi
			while (lo <= hi) {
				write_pixel(lo, y);
				++lo;
			}
		}
	}
}


void Display1()
{
	Grid g(16, 16);
	g.show_circle_4(13);
}


void Display2()
{
	Grid g(29, 29);
	g.fill_elipse(14, 8, 14, 8);
}


void Display3()
{
	Grid g(15, 15);
	vmuc_t poly;
	mint_t et, ssms;

	const char fname[] = "poly.txt";
	g.poly_read(poly, fname);
	g.draw_poly(poly);
	g.initialize(poly, et);
	g.computessm(poly, et, ssms);
	g.colorize(ssms);
}


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	switch(prevKey) {
    case '1':
       Display1();
       break;
    case '2':
       Display2();
       break;
    case '3':
       Display3();
       break;
	default:
	   break;
   }

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

	glutInitWindowSize(DIM, DIM);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow("--- My Grid ---");

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
