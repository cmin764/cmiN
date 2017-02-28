#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

//the positions of the control points
double points[4][2] = {{-0.7,-0.5}, {-0.5,0.5}, {0.5, -0.5}, {0.6,0}};
//maximum distance between the point and where the mouse clicks in order to consider the mouse clicking on that point
double  maxDist=0.05;
//is the mouse pressed?
bool mPress = false;
//which point has the mouse selected
int pointSel = -1;

unsigned int width = 500, height = 500;

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);

}

//each point alongside the bezier line is the hierarchical _weighted_ arithmetic mean of the control points. The side the weights 'pulls towards' changes as line is drawn, progressively.
double bezier(double a, double b, double c, double d, double t) {
  double s, ab, bc, cd, abc, bcd;
  s = 1-t;
  ab = a * s + b * t;
  bc = b * s + c * t;
  cd = c * s + d * t;
  abc = ab * s + bc * t;
  bcd = bc * s + cd * t;
  return(abc * s + bcd *t);
}

void display(void)
{
   int i;
   double di, r = 0.001;
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINE_STRIP);
   //iterate through all points of the Bezier line
      for (di = 0; di <= 1+r; di+=r)
	glVertex2f(bezier(points[0][0], points[1][0], points[2][0], points[3][0],di), bezier(points[0][1], points[1][1], points[2][1], points[3][1],di));
   glEnd();
   //increase point size, and draw them
   glPointSize(7.0);
   for (i = 0; i < 4; i++) {
     glColor3f(0.9 * double(i)/double(3) , 0.9 * double (3-i)/double(3), 0.1);
     glBegin(GL_POINTS);
     glVertex2f(points[i][0], points[i][1]);
     glEnd();
   }
   //draw the selected point differently
   if(pointSel>-1) {
     glColor3f(0.3, 0.2, 1);
     glBegin(GL_POINTS);
     glVertex2f(points[pointSel][0], points[pointSel][1]);
     glEnd();
     glColor3f(0.9, 0.9, 0.1);
   }
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   width = w;
   height = h;
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
  if(key==27) exit(0);
  if(key=='r') {//reset
    points[0][0] = -0.7;
    points[0][1] = -0.5;
    points[1][0] = -0.5;
    points[1][1] = 0.5;
    points[2][0] = 0.5;
    points[2][1] = -0.5;
    points[3][0] = 0.6;
    points[3][1] = 0;
    glutPostRedisplay();
  }
}

double scale(int c, int length)
{
  return(-1.0 + double(c) * 2.0 / double(length));
}

double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int getSel(double x, double y) {
  //check if the distance given falls within the activation radius of any of the control points
  double minDist = 5, dist;
  int index = -1;
  //if multiple points are grouped together, activate only (the last) one
  for(int i = 0; i < 4; ++i) {
    dist = distance(points[i][0], points[i][1], x, y);
    if (dist < minDist) {
      minDist = dist;
      index = i;
    }
  }
  if(minDist <= maxDist) {
    return(index);
  }
  else {
    return(-1);
  }
}


void mouse(int button, int state, int x, int y) {
  double dx, dy;
  if(button == 0) {
    if(state == 0) {
      mPress = true;
      //get openGL coordinates from pixel coordinates
      dx = scale(x, width);
      dy = -scale(y, height);
      pointSel = getSel(dx, dy);
      printf("Selected %d\n", pointSel);
    }
    else
      if(state == 1) {
	mPress = false;
	pointSel = -1;
      }
    glutPostRedisplay();
  }
}

void mouseMove(int x, int y) {
  double dx, dy;
  if(mPress) {
    dx = scale(x, width);
    dy = -scale(y, height);
    if(dx>1) dx = 1;
    if(dx<-1) dx = -1;
    if(dy>1) dy = 1;
    if(dy<-1) dy=-1;
    //drag points around
    printf("Moving active mouse button to %f, %f\n", dx, dy);
    if(pointSel != -1) {
      points[pointSel][0] = dx;
      points[pointSel][1] = dy;
      glutPostRedisplay();
    }
  }
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize (width, height);
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

