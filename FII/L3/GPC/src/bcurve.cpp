#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <algorithm>

//#define highprec

#ifdef highprec
  typedef double Float;
  #define glVertex2 glVertex2d
  #define glVertex3 glVertex3d
#else
  typedef float Float;
  #define glVertex2 glVertex2f
  #define glVertex3 glVertex3f
#endif

using namespace std;

struct Point {
  Float v[3];


  Point(Float v0 = 0, Float v1 = 0, Float v2 = 0) {
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
  }

  inline Float& operator[](size_t idx) {
    return v[idx];
  }
  inline const Float& operator[](unsigned int idx) const {
    return v[idx];
  }
  inline Point& operator+=(const Point& rhs) {
    for(unsigned int ii = 0; ii < 3; ++ii)
      v[ii] += rhs[ii];
    return *this;
  }
  inline Point& operator-=(const Point& rhs) {
    for(unsigned int ii = 0; ii < 3; ++ii)
      v[ii] -= rhs[ii];
    return *this;
  }
  inline Point& operator*=(const Float& rhs) {
    for(unsigned int ii = 0; ii < 3; ++ii)
      v[ii] *= rhs;
    return *this;
  }
  inline Point& operator/=(const Float& rhs) {
    for(unsigned int ii = 0; ii < 3; ++ii)
      v[ii] /= rhs;
    return *this;
  }
};

inline Point operator+(Point lhs, const Point& rhs) {
  lhs += rhs;
  return lhs;
}
inline Point operator-(Point lhs, const Point& rhs) {
  lhs -= rhs;
  return lhs;
}
inline Point operator*(Point lhs, const Float& rhs) {
  lhs *= rhs;
  return lhs;
}
inline Point operator/(Point lhs, const Float& rhs) {
  lhs /= rhs;
  return lhs;
}

inline bool operator==(const Point& lhs, const Point& rhs) {
  for(unsigned int ii = 0; ii < 3; ++ii)
    if(lhs[ii] != rhs[ii]) return false;
  return true;
}

inline bool operator!=(const Point& lhs, const Point& rhs) {
  return !(lhs == rhs);
}

inline Float distance(Point lhs, Point rhs, Float lebesgue = 2) {
  Float sum = 0;
  Point diff = rhs - lhs;
  for(size_t ii = 0; ii < 3; ++ii) {
    sum += pow(diff[ii], lebesgue);
  }
  return(pow(sum, Float(1) / lebesgue));
}

inline Float norm(Point p, Float lebesgue = 2) {
  return distance(Point(), p, lebesgue);
}

inline Point rotate(Point point, Float angle) {
  Point out;
  out[0] = point[0] * cos(angle) - point[1] * sin(angle);
  out[1] = point[0] * sin(angle) + point[1] * cos(angle);
  return out;
}

//last pressed key
unsigned char g_key;
//the positions of the control points
vector<Point> g_points;
//maximum distance between the point and where the mouse clicks in order to consider the mouse clicking on that point
Float g_maxDist=0.05;
//is the mouse pressed?
bool g_mPress = false;
//which point has the mouse selected
int g_pointSel = -1;
//fractal recursion depth
unsigned int g_fracRec = 8;

Point g_screen;

void initPoints() {
  g_points.resize(4);
  g_points[0] = Point(-0.5, 0);
  g_points[1] = Point(0, 0.25);
  g_points[2] = Point(0, -0.25);
  g_points[3] = Point(0.5, 0);
}

void initPoints2() {
  initPoints();
  g_points[0] = Point(-0.5, 0);
  g_points[1] = Point(0, 0.5);
  g_points[2] = Point(0, 0.5);
  g_points[3] = Point(0.5, 0);
}

void init(void) {
   glClearColor(0.0, 0.0, 0.0, 0.0);
   // glShadeModel(GL_FLAT);
   initPoints();
   g_key = '1';
   g_pointSel = -1;
}

//each point alongside the bezier line is the hierarchical _weighted_ arithmetic mean of the control points. The side the weights 'pulls towards' changes as line is drawn, progressively.
//Further reading: barycentric coordinates.
Point bezier(Point a, Point b, Point c, Point d, Float t) {
  Point ab, bc, cd, abc, bcd;
  Float s;
  s = 1-t;
  ab = a * s + b * t;
  bc = b * s + c * t;
  cd = c * s + d * t;
  abc = ab * s + bc * t;
  bcd = bc * s + cd * t;
  return(abc * s + bcd *t);
}

void displayPoints() {
   //increase point size, and draw them
   glPointSize(7.0);
   for (int ii = 0; ii < 4; ++ii) {
     glColor3f(0.9 * Float(ii) / Float(3) , 0.9 * Float(3 - ii) /Float(3), 0.1);
     glBegin(GL_POINTS);
       glVertex2(g_points[ii][0], g_points[ii][1]);
     glEnd();
   }
   //draw the selected point differently
   if(-1 < g_pointSel) {
     glColor3f(0.3, 0.2, 1);
     glBegin(GL_POINTS);
       glVertex2(g_points[g_pointSel][0], g_points[g_pointSel][1]);
     glEnd();
     glColor3f(0.9, 0.9, 0.1);
   }
}


void old_drawRecFractal(Point beg, Point end, unsigned int ttl) {
  if(0 == ttl) {
    glBegin(GL_LINES);
      glVertex2(beg[0], beg[1]);
      glVertex2(end[0], end[1]);
    glEnd();
  } else {
    // cout<<"In-between";
    Point mid, mid1, mid2, deltaD;
    mid = (beg + end) / 2;
    deltaD = (end - mid) / Float(3);
    mid1 = Point(mid[0] - deltaD[1], mid[1] + deltaD[0]);
    mid2 = Point(mid[0] + deltaD[1], mid[1] - deltaD[0]);

    --ttl;//!!
    old_drawRecFractal(beg, mid1, ttl);
    old_drawRecFractal(mid1, mid2, ttl);
    old_drawRecFractal(mid2, end, ttl);
  }
}

inline bool moreThanAPixel(const Point& beg, const Point& end, const Point& screen) {
  Float delta = norm(end - beg);
  Float pixelSize = 2 / norm(screen);
  if (delta < pixelSize) return false;
  else return true;
}

unsigned int drawRecFractal(Point beg, Point end, Point offB, Point offC, unsigned int ttl) {
  if(0 == ttl || !moreThanAPixel(beg, end, g_screen)) {
    glBegin(GL_LINES);
      glVertex2(beg[0], beg[1]);
      glVertex2(end[0], end[1]);
    glEnd();
    return(ttl);
  } else {
    // cout<<"In-between";
    Point mid1, mid2, diff;
    Float length, angle;
    unsigned int maxDepth = 0;
    length = distance(beg, end);
    diff = end - beg;
    angle = atan2(diff[1], diff[0]);

    --ttl;//!!
    mid1 = beg + rotate(offB, angle) * length;
    mid2 = mid1 + rotate(offC, angle) * length;
    maxDepth = max(maxDepth, drawRecFractal(beg,  mid1, offB, offC, ttl));
    maxDepth = max(maxDepth, drawRecFractal(mid1, mid2, offB, offC, ttl));
    maxDepth = max(maxDepth, drawRecFractal(mid2, end,  offB, offC, ttl));
    return(maxDepth);
  }
}


void display1();
void display2();
void display3();

void display1() {
   Float di, r = 0.001;
   Point p;
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINE_STRIP);
   //iterate through all points of the Bezier line
     for (di = 0; di <= 1+r; di+=r) {
       p = bezier(g_points[0], g_points[1], g_points[2], g_points[3], di);
       glVertex2(p[0], p[1]);
     }
   glEnd();
   displayPoints();
}

void display2() {
  glColor3f(0.4, 0.4, 0.4);
  glBegin(GL_LINE_STRIP);
    glVertex2(g_points[0][0], g_points[0][1]);
    glVertex2(g_points[1][0], g_points[1][1]);
    glVertex2(g_points[2][0], g_points[2][1]);
    glVertex2(g_points[3][0], g_points[3][1]);
  glEnd();
  displayPoints();
  display3();
}

void display3() {
  Float angle, length;
  Point a, b, c, d, tmp, offB, offC;
  a = g_points[0];
  b = g_points[1];
  c = g_points[2];
  d = g_points[3];
  //the main direction of the line is established between its ends
  tmp = d - a;
  angle = atan2(tmp[1], tmp[0]);

  length = distance(a, d);
  offB = rotate(b - a, -angle) / length;
  offC = rotate(c - b, -angle) / length;


  glColor3f(1, 1, 1);
  drawRecFractal(a, d, offB, offC, g_fracRec);
}

void display0() {
  Float r, t, inc = 0.01, screenRatio = 1, x, y, freq = 20, offset = 0.75, amplitude = 0.1;
  if(g_screen[0])
    screenRatio = g_screen[1] / g_screen[0];
  glColor3f(0.2, 0.2, 0.2);
  r = offset;
  glBegin(GL_LINE_LOOP);
    for(t = 0; t < 2 * M_PI; t += inc) {
      x = r * cos(t);
      y = r * sin(t);
      if(screenRatio > 1)
	y /= screenRatio;
      else
	x *= screenRatio;
      glVertex2(x, y);
    }
  glEnd();

  glBegin(GL_LINE_LOOP);
    for(t = 0; t < 2 * M_PI; t += inc) {
      glColor3f(t / (2 * M_PI), 0, 1 - t / (2 * M_PI));
      r = offset + amplitude * sin(freq * t);
      x = r * cos(t);
      y = r * sin(t);
      if(screenRatio > 1)
	y /= screenRatio;
      else
	x *= screenRatio;
      glVertex2(x, y);
    }
  glEnd();

}


void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  switch(g_key) {
    case '1': display1(); break;
    case '2': display2(); break;
    case '3': display3(); break;
    case '0': display0(); break;
  }
  glutSwapBuffers();
}

void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   g_screen[0] = w;
   g_screen[1] = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-1.0, 1.0, (GLfloat)h/(GLfloat)w,
               (GLfloat)h/(GLfloat)w, -1.0, 1.0);
   else
      glOrtho((GLfloat)w/(GLfloat)h,
               (GLfloat)w/(GLfloat)h, -1.0, 1.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keys(unsigned char key, int x, int y) {
  if('0' <= key && '9' >= key) {
    g_key = key;
    glutPostRedisplay();
  }

  if(27 == key) exit(0);

  if('r' == key) {//reset
    initPoints();
    glutPostRedisplay();
  }
  if('t' == key) {//second reset
    initPoints2();
    glutPostRedisplay();
  }
  if('+' == key && 1000 >= g_fracRec) {
    ++g_fracRec; //eh, random limit
    glutPostRedisplay();
  }
  if('-' == key && 1 <= g_fracRec) {
    --g_fracRec;
    glutPostRedisplay();
  }
}

Float scale(int c, int length) {
  return(-1.0 + Float(c) * 2.0 / Float(length));
}

int getSel(Point p) {
  //check if the distance given falls within the activation radius of any of the control points
  Float minDist = 5, dist;
  int index = -1;
  //if multiple points are grouped together, activate only (the last) one
  for(int i = 0; i < 4; ++i) {
    dist = distance(g_points[i], p);
    if (dist < minDist) {
      minDist = dist;
      index = i;
    }
  }
  if(minDist <= g_maxDist) {
    return(index);
  }
  else {
    return(-1);
  }
}


void mouse(int button, int state, int x, int y) {
  Float dx, dy;
  if('3' == g_key) return; //display 3 does not move points around
  if(0 == button) {
    if(0 == state) {
      g_mPress = true;
      //get openGL coordinates from pixel coordinates
      dx = scale(x, g_screen[0]);
      dy = -scale(y, g_screen[1]);
      g_pointSel = getSel(Point(dx, dy));
      //      printf("Selected %d\n", g_pointSel);
      glutPostRedisplay();
    }
    else
      if(1 == state) {
	g_mPress = false;
	g_pointSel = -1;
	glutPostRedisplay();
      }
  }
}

void mouseMove(int x, int y) {
  Float dx, dy;
  if('3' == g_key) return;
  if(g_mPress) {
    dx = scale(x, g_screen[0]);
    dy = -scale(y, g_screen[1]);
    if(dx > 1)  dx = 1;
    if(dx < -1) dx = -1;
    if(dy > 1)  dy = 1;
    if(dy < -1) dy = -1;
    //drag points around
    //    printf("Moving active mouse button to %f, %f\n", dx, dy);
    if(g_pointSel != -1) {
      g_points[g_pointSel] = Point(dx, dy);
      glutPostRedisplay();
    }
  }
}


int main(int argc, char** argv) {
  g_screen = Point(300,300);
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize (g_screen[0], g_screen[1]);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keys);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMove);
  glutIdleFunc(display);

  glutMainLoop();
  return 0;
}
