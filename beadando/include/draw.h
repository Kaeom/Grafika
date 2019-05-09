#ifndef DRAW_H_
#define DRAW_H_
#include "model.h"

typedef struct Position
{
	double x;
	double y;
	double z;
}Position;

typedef struct {

	double earth_rotation;
	double sun_rotation;
}Rotate;

typedef struct{
	Position earth;
	Position sun;
	Position falcon;
}Move;


/**Draw the model.*/
void draw_model(const struct Model* model);


/**Draw the triangles of the model.*/
void draw_triangles(const struct Model* model);


/**Draw the quads of the model.*/
void draw_quads(const struct Model* model);


/**Draw the normal vectors of the model.*/
void draw_normals(const struct Model* model, double length);

#endif