#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <array>
#include "CyrusBeck.h"

using namespace std;

int width = 640;
int height = 480;

array<float, 3> polyColor = {1,1,1};
array<float, 3> windColor = {1,1,1};

static int mainMenu;
static int subMenuColor;
static int subMenuWindow;

array<int, 2> currentPoint;
vector<array<int, 2>> points;
vector<array<int, 2>> windowPoints;
vector<array<int, 2>> cbPoints;

bool closed = false;
bool windowClosed = false;
bool drawPoly = false;
bool drawWind = false;

//draw the line between the points selected by user
void drawPolygon()
{
	if (!points.empty())
	{
		glBegin(GL_LINE_STRIP);

		glColor3f(polyColor[0], polyColor[1], polyColor[2]);

		for (auto& pt : points)
			glVertex2f((float)pt[0], (float)pt[1]);
		auto& endPt = closed ? points.front() : currentPoint;
		glVertex2f((float)endPt[0], (float)endPt[1]);

		glEnd();
	}
}

//draw the window with the user inputs
void drawWindow()
{
	if (!windowPoints.empty())
	{
		glBegin(GL_LINE_STRIP);

		glColor3f(windColor[0], windColor[1], windColor[2]);

		for (auto& pt : windowPoints)
			glVertex2f((float)pt[0], (float)pt[1]);
		auto& endPt = windowClosed ? windowPoints.front() : currentPoint;
		glVertex2f((float)endPt[0], (float)endPt[1]);

		glEnd();
	}
}

void drawCyrusBeck()
{
	if (!cbPoints.empty())
	{
		glBegin(GL_LINE_STRIP);

		glColor3f(1, 0, 1);

		for (auto& pt : cbPoints)
			glVertex2f((float)pt[0], (float)pt[1]);
		auto& endPt = cbPoints.front();
		glVertex2f((float)endPt[0], (float)endPt[1]);

		glEnd();
	}
}

void render()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//call drawPolygon
	drawPolygon();

	//call drawWindow
	drawWindow();

	//call drawCyrusBeck
	drawCyrusBeck();

	glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
	//press c to close the polygon and stop drawing the polygon
	if (c == 'c')
	{
		closed = true;
		drawPoly = false;
	}
	//press f to close the window and stop window drawing
	if (c == 'f')
	{
		windowClosed = true;
		drawWind = false;
	}
}

//manage mouse events
void mouse(int button, int state, int x, int y)
{
	//if left mouse button is down then add the next point for polygon
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && drawPoly)
	{
		if (closed)
			points.clear();
		closed = false;
		points.push_back(currentPoint);
	}
	//if left mouse button is down then add the next point for window
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && drawWind)
	{
		if (windowClosed)
			windowPoints.clear();
		windowClosed = false;
		windowPoints.push_back(currentPoint);
	}
}

//get the current position of the mouse
void mouse_move(int x, int y)
{
	currentPoint = array<int, 2>{x, height - y};
	glutPostRedisplay();
}

//define what to do when a user click on a menu
void menu(int n)
{
	CyrusBeck cB;

	switch (n)
	{
	//choose color once the user started drawing the polygon
	case 11 :
		if (drawPoly)
			polyColor = { 1.0,0,0 };
		if (drawWind)
			windColor = { 1.0,0,0 };
		break;
	case 12:
		if (drawPoly)
			polyColor = { 0,1.0,0 };
		if (drawWind)
			windColor = { 0,1.0,0 };
		break;
	case 13:
		if (drawPoly)
			polyColor = { 0,0,1.0 };
		if (drawWind)
			windColor = { 0,0,1.0 };
		break;
	//start the drawing process of a polygon when user click on the appropriate menu
	case 2 :
		drawPoly = true;
		points.clear();
		break;
	case 3:
		drawWind = true;
		windowPoints.clear();
		break;
	case 41:
		cbPoints = cB.cyrusBeck(points, windowPoints);
		break;
	default :
		break;
	}

}

//manage the menu creation and attach to right click button
void createMenu()
{
	subMenuColor = glutCreateMenu(menu);
	glutAddMenuEntry("red", 11);
	glutAddMenuEntry("green", 12);
	glutAddMenuEntry("blue", 13);

	subMenuWindow = glutCreateMenu(menu);
	glutAddMenuEntry("Cyrus Beck", 41);
	glutAddMenuEntry("Sutherland-ogdmann", 42);
	glutAddMenuEntry("Ear cutting", 43);

	mainMenu = glutCreateMenu(menu);
	glutAddSubMenu("couleurs", subMenuColor);
	glutAddMenuEntry("polygone à découper", 2);
	glutAddMenuEntry("tracé fenêtre", 3);
	glutAddSubMenu("fenêtrage", subMenuWindow);
	glutAddMenuEntry("remplissage", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Simple Window");

	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouse_move);

	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0f, (float)width, 0.0f, (float)height, -1.0, 1.0);

	//create a menu
	createMenu();

	glutMainLoop();
}