#include "init.h"
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include "scene.h"

void init_opengl()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();	
    glEnable(GL_DEPTH_TEST);	
    glClearDepth(1.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_FOG);
}

void PopMenuCreate(Scene* scene)
{
	/**Menu:*/
	int sub1 = glutCreateMenu(switchMenu);
	glutAddMenuEntry("Lights off", 1);
	glutAddMenuEntry("Lights on", 2);
	glutAddMenuEntry("Fog off", 3);
	glutAddMenuEntry("Fog on",4);
	glutAddMenuEntry("Draw origin on",5);
	glutAddMenuEntry("Draw origin off",6);
	
	
	int sub2 = glutCreateMenu(switchMenu);
	glutAddMenuEntry("Camera movement: Left click + cursor", 7);
	glutAddMenuEntry("Basic movement: W,A,S,D,Q,E", 8);
	glutAddMenuEntry("Cow movement: Numbad 8,2,4,6,7,9", 9);
	glutAddMenuEntry("Lights -,+:", 9);
	glutAddMenuEntry("Switch lights off-on: X,C", 10);
	
	glutCreateMenu(switchMenu);
	glutAddSubMenu("Lights/Fog", sub1);
	glutAddSubMenu("Help", sub2);
	glutAddMenuEntry("Exit", 12);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void switchMenu(int value)
{
	int color=0;
	switch(value)
	{
		case 1:
		{
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			break;
		}
		case 2:
		{
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			break;
		}
		case 3:
		{
			glDisable(GL_FOG);
			break;
		}
		case 4:
		{
			glEnable(GL_FOG);
			break;
		}
		case 5:
		{
			setOriginToDraw(0);
			break;
		}
		case 6:
		{
			setOriginToDraw(1);
			break;
		}
		case 12:
		{
			exit(0);
			break;
		}
		default:
			break;
	}
	glutPostRedisplay();
}