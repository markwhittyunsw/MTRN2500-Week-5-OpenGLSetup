#include <stdafx.h>
#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


// Start of Point class definition ===========================================
class Point
{
protected:
	double X;
	double Y;
	double R;
	double G;
	double B;
	double alpha;
public:
	Point();
	Point(double x, double y);
	// Any other constructors
	// Getters and setters
	double GetX();
	double GetY();
	double GetR();
	double GetG();
	double GetB();
	void SetX(double x);
	void SetY(double y);
	void SetColour(double r, double g, double b);
	// Point class capabilities
	void Draw();
	void Move(double x, double y);
	//any other capabilities
};
	
Point::Point()
{
}

Point::Point(double x, double y)
{
	X = x;
	Y = y;
	R = 1.0;
	G = 1.0;
	B = 1.0;
}


double Point::GetX()
{
	return X;
}

double Point::GetY()
{
	return Y;
}

double Point::GetR()
{
	return R;
}

double Point::GetG()
{
	return G;
}

double Point::GetB()
{
	return B;
}

void Point::SetX(double x)
{
	X = x;
}

void Point::SetY(double y)
{
	Y = y;
}

void Point::SetColour(double r, double g, double b)
{
	R = r;
	G = g;
	B = b;
}

void Point::Draw()
{
	glColor3f(R,G,B);
	glLoadIdentity();
	glBegin(GL_POINTS);
	glVertex2f(X,Y);
	glEnd();
}

void Point::Move(double x, double y)
{
	X = x;
	Y = y;
}
// End of Point class definition and the member function declaration ==========

// Start of Circle class definition ===========================================
class Circle : public Point //Circle inherits everything from Point class.
{
protected:
	double Radius;

public:
	Circle();
	Circle(double x, double y, double r, double g, double b, double radius);
	double GetRadius();
	void SetRadius(double radius);
	void Draw();
	void Move(double x, double y); //inherited move is sufficient - see definition
};

Circle::Circle():Point()
{
}

Circle::Circle(double x, double y, double r, double g, double b, double radius):Point(x,y)
{
	SetColour(r,g,b);
	Radius = radius;
}
double Circle::GetRadius()
{
	return Radius;
}
void Circle::SetRadius(double radius)
{
	Radius = radius;
}
void Circle::Draw()
{
	double p, q, theta = 0.0;
	glColor3f(R,G,B);
	glLoadIdentity();
	glBegin(GL_LINE_LOOP);
	do
	{
		p = X + Radius*cos(theta);
		q = Y + Radius*sin(theta);
		glVertex2f(p,q);
		theta += 0.005;
	}
	while(theta < 2*3.15);
	glEnd();
}

// This function is redundant however provides better readability
void Circle::Move(double x, double y) 
{
	Point::Move(x,y);
}

// End of circle class definition ============================================

//Global data Declaration

Point P(100,200);
Circle C(100,200,1,0,0,50);
Circle C2(110, 220, 0, 0, 1, 20);
double temp_x = 0;
double temp_y = 0;

void drawMyAxis(int length)
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(length, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, length, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, length);
	glEnd();
}


void drawWheel(float offX, float offY, float offZ, double angPos, double steeringAngle)
{
	glPushMatrix();
	glTranslatef(offX, offY, offZ);
	glRotated(steeringAngle, 0, 1, 0);
	glRotated(angPos, 0, 0, 1);

	glTranslatef(0, 0, -.125);
	GLUquadric *q1 = gluNewQuadric();
	gluDisk(q1, 0, 50, 50, 60);

	//gluCylinder(1, 1, .25);

	glTranslatef(0, 0, .25);
	GLUquadric *q2 = gluNewQuadric();
	gluDisk(q2, 0, 50, 50, 60);
	glPopMatrix();
}




//OpenGL related functions 

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 27:
		exit(0);
	}
}


void display (void) 
{
	double p, q, theta = 0;

	double Radius = 10.0;
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

// Draw
	P.Draw();
	C.Draw();
	C2.SetColour(0, 1, 0);
	C2.Move(temp_x++, temp_y++);
	C2.Draw();
	C.Draw();
	drawMyAxis(50);



// End of Draw

	glFlush();
	glutSwapBuffers();
	Sleep(10);
}


void reshape (int w, int h) 
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(-(GLdouble) w,(GLdouble) w,-(GLdouble) h,(GLdouble) h);
	glMatrixMode (GL_MODELVIEW);
}


int main (int argc, char **argv) 
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("An OpenGL Example Window");
	init();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutIdleFunc(display);
	glutMainLoop ();
	return 0;
}
