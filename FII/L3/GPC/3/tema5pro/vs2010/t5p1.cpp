#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>

#include "glut.h"

// dimensiunea ferestrei in pixeli
#define dim 300
// numarul maxim de iteratii pentru testarea apartenentei la mult.Julia-Fatou
#define NRITER_JF 5000
// modulul maxim pentru testarea apartenentei la mult.Julia-Fatou
#define MODMAX_JF 10000000
// ratii ptr. CJuliaFatou
#define RX_JF 0.01
#define RY_JF 0.01

unsigned char prevKey;

class CComplex {
public:
  CComplex() : re(0.0), im(0.0) {}
  CComplex(double re1, double im1) : re(re1 * 1.0), im(im1 * 1.0) {}
  CComplex(const CComplex &c) : re(c.re), im(c.im) {}
	~CComplex() {}

  CComplex &operator=(const CComplex &c) 
  {
    re = c.re;
    im = c.im;
    return *this;
  }

  double getRe() {return re;}
  void setRe(double re1) {re = re1;}
  
  double getIm() {return im;}
  void setIm(double im1) {im = im1;}

  double getModul() {return sqrt(re * re + im * im);}

  int operator==(CComplex &c1)
  {
    return ((re == c1.re) && (im == c1.im));
  }

  CComplex pow2() 
  {
    CComplex rez;
    rez.re = powl(re * 1.0, 2) - powl(im * 1.0, 2);
    rez.im = 2.0 * re * im;
    return rez;
  }

	friend CComplex operator+(const CComplex &c1, const CComplex &c2);
	friend CComplex operator*(CComplex &c1, CComplex &c2);

	void print(FILE *f) 
	{
		fprintf(f, "%.20f%+.20f i", re, im);
	}

private:
  double re, im;
};

CComplex operator+(const CComplex &c1, const CComplex &c2) 
{
	CComplex rez(c1.re + c2.re, c1.im + c2.im);
	return rez;
}

CComplex operator*(CComplex &c1, CComplex &c2) 
{
	CComplex rez(c1.re * c2.re - c1.im * c2.im,
                c1.re * c2.im + c1.im * c2.re);
	return rez;
}

class CJuliaFatou {
public:
  CJuliaFatou()
  {
    // m.c se initializeaza implicit cu 0+0i

    m.nriter = NRITER_JF;
    m.modmax = MODMAX_JF;
  }
  
  CJuliaFatou(CComplex &c)
  {
    m.c = c;
    m.nriter = NRITER_JF;
    m.modmax = MODMAX_JF;
  }
  
  ~CJuliaFatou() {}

  void setmodmax(double v) {assert(v <= MODMAX_JF); m.modmax = v;}
  double getmodmax() {return m.modmax;}

  void setnriter(int v) {assert(v <= NRITER_JF); m.nriter = v;}
  int getnriter() {return m.nriter;}

  // testeaza daca x apartine multimii Julia-Fatou Jc
  // returneaza 0 daca apartine, -1 daca converge finit, +1 daca converge infinit
  int isIn(CComplex &x)
  {
    int rez = 0;
    // tablou in care vor fi memorate valorile procesului iterativ z_n+1 = z_n * z_n + c
    CComplex z0,z1;

    z0 = x;
    for (int i = 1; i < m.nriter; i++)
    {
      z1 = z0 * z0 + m.c;
      if (z1 == z0) 
      {
        // x nu apartine m.J-F deoarece procesul iterativ converge finit
        rez = -1;
        break;
      }
      else if (z1.getModul() > m.modmax)
      {
        // x nu apartine m.J-F deoarece procesul iterativ converge la infinit
        rez = 1;
        break;
      }
      z0 = z1;
    }

    return rez;
  }

  // afisarea multimii J-F care intersecteaza multimea argument
  void display(double xmin, double ymin, double xmax, double ymax)
  {
    glPushMatrix();
    glLoadIdentity();

//    glTranslated((xmin + xmax) * 1.0 / (xmin - xmax), (ymin + ymax)  * 1.0 / (ymin - ymax), 0);
//    glScaled(1.0 / (xmax - xmin), 1.0 / (ymax - ymin), 1);
    // afisarea propriu-zisa
    glBegin(GL_POINTS); 
    for(double x = xmin; x <= xmax; x+=RX_JF)
      for(double y = ymin; y <= ymax; y+=RY_JF) 
      {
        CComplex z(x, y);
        int r = isIn(z);
//        z.print(stdout);
        if (r == 0) 
        {
//          fprintf(stdout, "   \n");
          glVertex3d(x,y,0);
        }
        else if (r == -1)
        {
//          fprintf(stdout, "   converge finit\n");
        }
        else if (r == 1)
        {
//          fprintf(stdout, "   converge infinit\n");
        }
      }
    fprintf(stdout, "STOP\n");
    glEnd();

    glPopMatrix();
  }

private:
  struct SDate {
    CComplex c;
    // nr. de iteratii
    int nriter;
    // modulul maxim
    double modmax;
  } m;
};

// multimea Julia-Fatou pentru z0 = 0 si c = -0.12375+0.056805i
void Display1() {
  CComplex c(-0.12375, 0.056805);
  CJuliaFatou cjf(c);

  glColor3f(1.0, 0.1, 0.1);
  cjf.setnriter(30);
  cjf.display(-0.8, -0.4, 0.8, 0.4);
}

// multimea Julia-Fatou pentru z0 = 0 si c = -0.012+0.74i
void Display2() {
  CComplex c(-0.012, 0.74);
  CJuliaFatou cjf(c);

  glColor3f(1.0, 0.1, 0.1);
  cjf.setnriter(30);
  cjf.display(-1, -1, 1, 1);
}

void Init(void) {

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

//   glPointSize(3);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
  switch(prevKey) {
  case '1':
    glClear(GL_COLOR_BUFFER_BIT);
    Display1();
    break;
  case '2':
    glClear(GL_COLOR_BUFFER_BIT);
    Display2();
    break;
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


