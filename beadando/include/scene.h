#ifndef SCENE_H
#define SCENE_H
#include "camera.h"
#include "model.h"
#include <SOIL/SOIL.h>
#include <GL/glut.h>

typedef GLubyte Pixel[3];

Pixel* images[3];

GLuint texture_names[7];

typedef struct {
    Model model;
}Entity;

typedef struct Scene
{
    Camera camera;
    Entity cow;
	Entity grass;
	Entity house;
    Material material;
} Scene;



/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Initialize the textures by loading pictures.
 */
void initialize_texture();

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename, Pixel* image);
/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the lighting off on the scene.
 */

void set_material(const Material* material);

/**
 * Set the color for the object.
 */

void reset_material(Scene* scene);
/**
 * Draw the scene objects.
 */
void draw_scene(Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Draw the skybox for the world.
 */
void draw_skybox();

/**
 * Draw the stand cylinder for the car.
 */

void set_lighting_intensity(double lightGet);

/**
 * Set the lighting of the skybox.
 */
void white_material(Scene* scene);

/**
 * Updating color palette.
 */
void draw_cow(const Scene* scene);
void update_cow_position();
void move_cow_y(double y);
void move_cow_x(double h);
void move_cow_angle(double angle);
double* get_cow_x_position();
double* get_cow_y_position();
double* get_cow_z_position();
void fog();
void draw_grasses(const Scene* scene);
void draw_origin();
void setOriginToDraw(int onOff);
void draw_house(const Scene* scene);
void house_material(Scene* scene);
#endif /* SCENE_H */
