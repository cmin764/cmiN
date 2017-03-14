
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

// dimensiunea ferestrei in pixeli
#define dim 300
#define pi 4 * atan(1.0)

using namespace std;

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
   double xmax, ymax, xmin, ymin;
   double a = 1, b = 2;
   double ratia = 0.05;
   double t;

   // calculul valorilor maxime/minime ptr. x si y
   // aceste valori vor fi folosite ulterior la scalare
   xmax = a - b - 1;
   xmin = a + b + 1;
   ymax = ymin = 0;
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = a + b * cos(t);
      xmax = (xmax < x1) ? x1 : xmax;
      xmin = (xmin > x1) ? x1 : xmin;

      x2 = a - b * cos(t);
      xmax = (xmax < x2) ? x2 : xmax;
      xmin = (xmin > x2) ? x2 : xmin;

      y1 = a * tan(t) + b * sin(t);
      ymax = (ymax < y1) ? y1 : ymax;
      ymin = (ymin > y1) ? y1 : ymin;

      y2 = a * tan(t) - b * sin(t);
      ymax = (ymax < y2) ? y2 : ymax;
      ymin = (ymin > y2) ? y2 : ymin;
   }

   xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
   ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1; // x2, y2;
      x1 = (a + b * cos(t)) / xmax;
    //   x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
    //   y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   glBegin(GL_LINE_STRIP);
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x2, y2;
    //   x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
    //   y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x2,y2);
   }
   glEnd();
}

// graficul functiei
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$,
void Display2() {
   double xmax = 8 * pi;
   double ymax = exp(1.1);
   double ratia = 0.05;

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);
   for (double x = 0; x < xmax; x += ratia) {
      double x1, y1;
      x1 = x / xmax;
      y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();
}

void Display3() {
	double y = 0;
    double ratio = 0.05;
    auto dist = [](auto arg) { return fabs(round(arg) - arg); };

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x <= 100; x += ratio)
	{
		if (x == 0)
			y = 1;
		else
			y = dist(x) / x;
		glVertex2f(x / 25, y);
	}
	glEnd();
}

void Display4()
{
    double a = 0.3, b = 0.2;
	double ratio = 0.05;
	double x = 0, y = 0;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -pi; t <= pi; t += ratio)
	{
		x = 2 * (a * cos(t) + b) * cos(t);
		y = 2 * (a * cos(t) + b) * sin(t);

		glVertex2f(x / 1.1, y / 1.1);
	}
	glEnd();

}

void Display5() {
    double x = 0, y = 0;
	double ratio = 0.01;
	double a = 0.2;
	int cnt = 0, idx = 0;
    double _x, _y;

    // cream lobul

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0, 1.0); // albastru
	glVertex2f(-0.979, 0.957);

	for (double t = -pi / 2; t <= pi / 2; t += ratio)
	{
		if (!(t == pi / 6 || t == -pi / 6)) {
			x = (a / (4 * pow(cos(t), 2) - 3));
			y = ((a * sin(t) / cos(t)) / (4 * pow(cos(t), 2) - 3));

            ++cnt;
		}
        // selectia cadranului I
		if (x >= -1 && x <= 0 && y <= 1 && y >= 0) {
			glVertex2f(x, y);
		}
	}
	glEnd();

	_x = 0;
	_y = 0.957;

    for (double t = -pi / 2; t <= pi / 2; t += ratio)
	{
		if (!(t == pi / 6 || t == -pi / 6)) {
			x = (a / (4 * pow(cos(t), 2) - 3));
			y = ((a * sin(t) / cos(t)) / (4 * pow(cos(t), 2) - 3));

            ++cnt;
		}
		if (x >= -1 && x <= 0 && y <= 1 && y >= 0) {
			glVertex2f(x, y);
		}

		if (y > 0.25 && (y >= 0 && y <= 0.957 && x <= 0 && x >= -0.979))
		{

		    ++idx;
			if (!(idx % 2)) {
				glBegin(GL_TRIANGLES);
				glColor3f(1.0, 0, 0);
				glVertex2f(_x, _y);
				glVertex2f(x, y);
				glVertex2f(-0.979, 0.957);
				glEnd();
			} else {
                // cout << x << " " << y << endl;
				_x = x;
				_y = y;
				glEnd();
			}
		}
		else if (y <= 0.25 && ( x >= -1 && x <= 0 && y >= 0 && y <= 1)) {
			++idx;

			if (!(idx % 4)) {
				glBegin(GL_TRIANGLES);
				glColor3f(1.0, 1.0, 1.0);
				glVertex2f(_x, _y);
				glVertex2f(x, y);
				glVertex2f(-0.979, 0.957);
				glEnd();
			} else if (!(idx % 3)) {
                // cout << x << " " << y << endl;
				_x = x;
				_y = y;
				glEnd();
			}
		}
	}

}

void Display6()
{
	double x = 0, y = 0;
	double a = 0.1, b = 0.2;
    double ratio = 0.05;

	glColor3f(1, 0.1, 0.1); // red colour
	glBegin(GL_LINE_STRIP);
	for (double t = -10; t < 10; t += ratio) {
		x = a * t - b * sin(t);
		y = a - b * cos(t);
		glVertex2f(x / 1.2, y / 1.2);
	}
	glEnd();
}

void Display7()
{
	double x = 0, y = 0;
    double ratio = 0.05;
	double big_radius = 0.1, radius = 0.3;

	glColor3f(1, 0.1, 0.1);

	glBegin(GL_LINE_STRIP);
	for (double t = 0; t < 2 * pi; t += ratio) {
        double rap = radius / big_radius;
		x = (radius + big_radius) * cos(
                rap * t) -
                radius * cos(t + (rap * t));
		y = (radius + big_radius) * sin(
                rap * t) -
                radius * sin(t + (rap * t));

		glVertex2f(x, y);
	}
	glEnd();
}

void Display8()
{
	double x = 0, y = 0;
    double ratio = 0.05;
	double big_radius = 0.1, radius = 0.3;

	glColor3f(1, 0.1, 0.1);

    double t;
	glBegin(GL_LINE_STRIP);
	for (t = 0; t <= 2 * pi + ratio; t += ratio) {
        double rap = radius / big_radius;
		x = (radius - big_radius) * cos(
                rap * t) -
                radius * cos(t - (rap * t));
		y = (radius - big_radius) * sin(
                rap * t) -
                radius * sin(t - (rap * t));

		glVertex2f(x, y);
	}

    glVertex2f(x, y);

	glEnd();
}

void Display9()
{
    double x = 0, y = 0;
	double ratio = 0.01;
	double a = 0.4;
	double radius = 0;

	glColor3f(1, 0.1, 0.1);

    double t;

    // +
    glBegin(GL_LINE_STRIP);
    int count = 0;
	for (t = -(pi / 4); t <= pi / 4; t += ratio) {

		radius = a * sqrt(2 * cos(2 * t));
		x = radius * cos(t);
		y = radius * sin(t);
		glVertex2f(x, y);
        ++count;
	}
    cout << count << endl;
    glEnd();

    glBegin(GL_LINE_STRIP);
    count = 0;
    // -
    for (t = -(pi / 4); t <= pi / 4; t += ratio) {

		radius = -a * sqrt(2 * cos(2 * t));
		x = radius * cos(t);
		y = radius * sin(t);
		glVertex2f(x, y);
        ++count;
	}
    cout << count << endl;

	glEnd();
}

void Display0()
{
    double x = 0, y = 0;
	double ratio = 0.05;
	double a = 0.02;
	double radius = 0;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 2.90; t += ratio)
	{

		radius = a * exp(1 + t);
		x = radius * cos(t);
		y = radius * sin(t);
		glVertex2f(x, y);
	}
	glEnd();
}

void Init(void)
{

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
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
   case '4':
	   Display4();
	   break;
   case '5':
	   Display5();
	   break;
   case '6':
	   Display6();
	   break;
   case '7':
	   Display7();
	   break;
   case '8':
	   Display8();
	   break;
   case '9':
	   Display9();
	   break;
   case '0':
	   Display0();
   default:
      break;
   }

   glFlush();
}

void Reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
   prevKey = key;
   if (key == 27) // escape
      exit(0);
   glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

   glutInit(&argc, argv);

   glutInitWindowSize(dim, dim);

   glutInitWindowPosition(100, 100);

   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   glutCreateWindow (argv[0]);

   Init();

   glutReshapeFunc(Reshape);

   glutKeyboardFunc(KeyboardFunc);

   glutMouseFunc(MouseFunc);

   glutDisplayFunc(Display);

   glutMainLoop();

   return 0;
}
