#ifndef INIT_H
#define INIT_H

#include <windows.h>
#include "scene.h"

/**
 * Initialize the OpenGL context.
 */
void init_opengl();

/**
 * Switch function for menu.
 */
void switchMenu(int value);

/**
 * Initialize the pop-up menu.
 */
void PopMenuCreate();

#endif /* INIT_H */
