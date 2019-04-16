#include "callbacks.h"
#include "init.h"
#include "scene.h"
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <windows.h>

void set_callbacks()
{
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(pressKey);
    glutKeyboardUpFunc(releaseKey);
    glutIdleFunc(idle);
}

int main(int argc, char* argv[])
{
    int window;

    glutInit(&argc, argv);

    glutInitWindowSize(1280, 720);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    window = glutCreateWindow("Süle Ábel - D7ITL3");
	
	PopMenuCreate();
	
    glutSetWindow(window);

    init_opengl();	
	initialize_texture();
    init_scene(&scene);
    init_camera(&camera);
    set_callbacks();
	
	glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
