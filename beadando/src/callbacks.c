#include "callbacks.h"
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 70.0

struct {
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
	
    set_view(&camera);
    draw_scene(&scene);

    glPopMatrix();
    glutSwapBuffers();
	glFlush();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{
    rotate_camera(&camera, mouse_position.x - x, mouse_position.y - y);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void pressKey(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w': /**elore mozgas*/
		set_camera_speed(&camera, 5);
        break;
    case 's': /**hatra mozgas*/
		set_camera_speed(&camera, -5);
        break;
    case 'a': /**balra mozgas*/
        set_camera_side_speed(&camera, 5);
        break;
    case 'd': /**jobbra mozgas*/
        set_camera_side_speed(&camera, -5);
        break;
	case 'f': /**Fog*/
		glDisable(GL_FOG);
		break;		
	case 'e': /**kamera le*/
        set_camera_height(&camera, -5);
        break;
	case 'q': /**kamera fel*/
		set_camera_height(&camera, 5);
		break;
		
	case '-': /**Lights -*/
		set_lighting_intensity(-0.05f);
        break;
	case '+': /**Lights +*/
        set_lighting_intensity(0.05f);
        break;
		
	/**Cow_controll	*/
	case '8': /**cow forward*/
		move_cow_x(0.02f);
		break;
	case '5': /**cow backward*/
		move_cow_x(-0.02f);
		break;
	case '4': /**cow left*/
		move_cow_y(-0.02f);
		break;
	case '6': /**cow right*/
		move_cow_y(0.02f);
		break;
	case '7': /**cow angle left*/
		move_cow_angle(0.05f);
		break;
	case '9': /**cow angle right*/
		move_cow_angle(-0.05f);
		break;
	
	case 'x': /**Lights off*/
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
        break;
	case 'c': /**Lights on*/
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
        break;
	case 27: /**Exit*/
		exit(0);
        break;
	}
    glutPostRedisplay();
}

void releaseKey(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
	case 'q':
	case 'e':
		set_camera_height(&camera, 0);
		break;		
	case '8':
	case '5':
		move_cow_x(0.00f);
		break;
	case '4':
	case '6':
		move_cow_y(0.00f);
		break;
	case '7':
	case '9':
		move_cow_angle(0.0f);
		break;
	case 'f': /**Fog*/
		glEnable(GL_FOG);
		break;		
	case '-': /**Lights -*/
		set_lighting_intensity(-0.05f);
        break;
	case '+': /**Lights +*/
        set_lighting_intensity(0.05f);
        break;
	case 'x':
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
        break;
	case 'c':
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
        break;
	}
    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);

    glutPostRedisplay();
}
