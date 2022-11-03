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

void menu(int n)
{

}

//manage the menu creation and attach to right click button
int createMenu()
{
	int mainmenu = glutCreateMenu(menu);

	glutAddMenuEntry("test 1", 1);
	glutAddMenuEntry("test 2", 2);
	glutAddMenuEntry("test 3", 3);
	glutAddMenuEntry("test 4", 4);

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