
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
   double xmax, ymax, xmin, ymin;
   double a = 1, b = 2;
   double pi = 4 * atan(1.0);
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
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   glBegin(GL_LINE_STRIP); 
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x2,y2);
   }
   glEnd();
}

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
   double pi = 4 * atan(1.0);
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
	double ratia = 0.05;
	double y = 0;
	
	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x <= 100; x += ratia) 
	{
		if (x == 0)
			y = 1;
		else
			y = (fabs(round(x) - x)) / x;
		glVertex2f(x / 25, y);
	}
	glEnd();
}

void Display4()
{
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double x = 0, y = 0;
	double a = 0.3, b = 0.2;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -pi; t <= pi; t += ratia) 
	{
		x = 2 * (a * cos(t) + b) * cos(t);
		y = 2 * (a * cos(t) + b) * sin(t);

		glVertex2f(x / 1.1, y / 1.1);
	}
	glEnd();

}

void Display5() {
	double pi = 4 * atan(1.0);
	double ratia = 0.01;
	double x = 0, y = 0;
	double oldX, oldY;
	double a = 0.2;
	int count = 0, i = 0;
	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex2f(-0.979, 0.957);
	for (double t = -pi / 2; t <= pi / 2; t += ratia) 
	{
		if ((t != pi / 6) && (t != -pi / 6)) 
		{
			x = (a / (4 * cos(t)*cos(t) - 3));
			y = ((a* sin(t) / cos(t)) / (4 * cos(t) * cos(t) - 3));
			count++;
		}
		if (x <= 0 && y >= 0 && y <= 1 && x >= -1) 
		{
			glVertex2f(x, y);
			//cout << x << ", " << y << endl;
		}
	}
	glEnd();

	oldX = 0;
	oldY = 0.957;

	for (double t = -pi / 2; t <= pi / 2; t += ratia) 
	{
		
		if ((t != pi / 6) && (t != -pi / 6)) 
		{
			x = (a / (4 * cos(t)*cos(t) - 3));
			y = ((a* sin(t) / cos(t)) / (4 * cos(t) * cos(t) - 3));
			count++;
		}
		if ((x <= 0 && y >= 0 && y <= 0.957 && x >= -0.979) && y>0.25 )
		{
			
			i++;
			if (i % 2 == 0) 
			{
				glBegin(GL_TRIANGLES);
				glColor3f(1, 0, 0);
				
				glVertex2f(oldX, oldY);
				glVertex2f(x, y);
				glVertex2f(-0.979, 0.957);
				glEnd();
			}else 
			{
				printf("x: %f\t\ty:%f\n", x, y);
				oldX = x;
				oldY = y;
				glEnd();
			}
		}
		else if ((x <= 0 && y >= 0 && y <= 1 && x >= -1) &&(y<=0.25))
		{
			i++;
			if (i % 4 == 0)
			{
				glBegin(GL_TRIANGLES);
				glColor3f(1, 1, 1);

				glVertex2f(oldX, oldY);
				glVertex2f(x, y);
				glVertex2f(-0.979, 0.957);
				glEnd();
			}
			else if (i % 3 == 0)
			{
				printf("x: %f\t\ty:%f\n", x, y);
				oldX = x;
				oldY = y;
				glEnd();
			}
		}
	}

}

void Display6()
{
	double ratia = 0.05;
	double x = 0, y = 0;
	double a = 0.1, b = 0.2;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -10; t < 10; t += ratia) 
	{
		x = a * t - b * sin(t);
		y = a - b * cos(t);

		glVertex2f(x / 1.2, y / 1.2);
	}
	glEnd();
}

void Display7()
{
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double x = 0, y = 0;
	double R = 0.1, r = 0.3;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t < 2 * pi; t += ratia) 
	{
		x = (r + R) * cos((r / R)*t) - r * cos(t + ((r / R) * t));
		y = (r + R) * sin((r / R)*t) - r * sin(t + ((r / R) * t));

		glVertex2f(x, y);
	}
	glEnd();
}

void Display8()
{
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double x = 0, y = 0;
	double R = 0.1, r = 0.3;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 2 * pi; t += ratia) 
	{
		x = (r - R) * cos((r / R)*t) - r * cos(t - ((r / R) * t));
		y = (r - R) * sin((r / R)*t) - r * sin(t - ((r / R) * t));

		glVertex2f(x, y);
	}
	glEnd();
}

void Display9()
{
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double x = 0, y = 0;
	double a = 0.4;
	double r = 0;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -(pi / 4) - ratia; t <= pi / 4; t += ratia) 
	{

		r = -a * sqrt(2 * cos(2 * t));
		x = r * cos(t);
		y = r * sin(t);
		glVertex2f(x, y);
	}
	for (double t = -(pi / 4) - ratia ; t <= pi / 4; t += ratia) 
	{

		r = a * sqrt(2 * cos(2 * t));
		x = r * cos(t);
		y = r * sin(t);
		glVertex2f(x, y);
	}
	glEnd();
}

void Display0()
{
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double x = 0, y = 0;
	double a = 0.02;
	double r = 0;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 2.90; t += ratia) 
	{

		r = a * exp(1 + t);
		x = r * cos(t);
		y = r * sin(t);
		glVertex2f(x, y);
	}
	glEnd();
}

void Init(void) 
{

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

//   glPointSize(4);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) 
{
   glClear(GL_COLOR_BUFFER_BIT);

   switch(prevKey) 
   {
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

int main(int argc, char** argv) 
{

	int horizontal = 0;
	int vertical = 0;
	GetDesktopResolution(horizontal, vertical);

   glutInit(&argc, argv);
   
   glutInitWindowSize(dim, dim);

   glutInitWindowPosition((int)(horizontal - dim) / 2, (int)(vertical - dim) / 2);

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
