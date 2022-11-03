#include <GL/glut.h>
#include <iostream>

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex2f(-0.5, -0.5);
		glColor3f(0, 1, 0);
		glVertex2f(0.5, -0.5);
		glColor3f(0, 0, 1);
		glVertex2f(0, 0.5);
	glEnd();*/

	glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
	if (c == 27)
		exit(0);
}

void mouse(int button, int state, int x, int y)
{
	/*if (button == GLUT_RIGHT_BUTTON)
		exit(0);*/
}

//define what to do when a user click on a menu
void menu(int n)
{
	switch (n)
	{
	case 1 :
		exit(0);
		break;
	default :
		break;
	}

}

//manage the menu creation and attach to right click button
int createMenu()
{
	int mainmenu = glutCreateMenu(menu);

	glutAddMenuEntry("couleurs", 1);
	glutAddMenuEntry("polygone à découper", 2);
	glutAddMenuEntry("tracé fenêtre", 3);
	glutAddMenuEntry("fenêtrage", 4);
	glutAddMenuEntry("remplissage", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return mainmenu;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Simple Window");

	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	//create a menu
	int mainmenu = createMenu();

	glutMainLoop();
}