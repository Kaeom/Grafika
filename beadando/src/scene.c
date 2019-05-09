#include "scene.h"
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include "model.h"
#include "draw.h"
#include <math.h>

/**Globalis valtozok:*/

/**Vilagitas ereje*/
double light = 0.8f;
//double light = 0.0f;

double spot_x = 0;
double spot_y = 0;
double spot_z = 10;
double spot_cutoff = 20;
double focusing = 1;


/**Tehen hejzete, skalazasa, iranya*/
double cow_x = 0.0f;
double cow_y = 0.0f;
double cow_z = -4.9f;
double cow_speed_x = 0.0f;
double cow_speed_y = 0.0f;
double cow_speed_z = 0.0f;
double cow_angle = -90;
double cow_angle_speed = 0.0f;

double cow_scale = 0.25f;
double cow_deltaAngle = 0.0f;
double cow_deltaMove = 0;

int drawOrigin = 0;

double grassLocations[60][60][2];

void init_scene(Scene* scene)
{
    load_model("models/cow.obj", &scene->cow.model);
	
	load_model("models/barn.obj",&scene->house.model);

	/**
	grass generálás egy négyzetrácsra random eltolódásokkal x y irényokba.
	Sajnos nem bírja a gép :(
	load_model("models/grass1.obj",&scene->grass.model);
	
	Utilban van:
	genGrid(grassLocations);*/
	
	/**Kornyezeti vilagitas:*/
    scene->material.ambient.red = 0.8f;
    scene->material.ambient.green = 0.8f;
    scene->material.ambient.blue = 0.8f;
	
	/**Szort vilagitas:*/
    scene->material.diffuse.red = 0.8f;
    scene->material.diffuse.green = 0.8f;
    scene->material.diffuse.blue = 0.8f;
	
	/**"Csillogo" vilagitas:*/
    scene->material.specular.red = 0.9;
    scene->material.specular.green = 0.9;
    scene->material.specular.blue = 1.0;
	
	/**Csillogas merteke:*/
    scene->material.shininess = 80;
}


void draw_scene(Scene* scene)
{
    set_lighting();
    draw_origin();
	white_material(scene);/**Skybox Fehér Material*/
	draw_skybox();
	cow_material(scene); //Cow Barna Material*/
	update_cow_position();
	draw_cow(scene);
	//house_material(scene);
	draw_house(scene);
	/**draw_grasses(scene);*/
	fog();
	glDisable(GL_TEXTURE_2D);
}

void fog(){	
	GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_START, 10.0f);
	glFogf(GL_FOG_END, 100.0f);
	glFogf(GL_FOG_DENSITY, 0.03f);
}

void set_lighting()
{
	float ambient_light[] = { light, light, light, 0.8f };
    float diffuse_light[] = { light, light, light, 0.8f };
    float specular_light[] = { light, light, light, 0.8f };
    float position[] = { 0.0f, 0.0f, 10.0f, 0.0f };		
	
	float ambient_light1[] = { light, light, light, 0.8f };
    float diffuse_light1[] = { light, light, light, 0.8f };
    float specular_light1[] = { light, light, light, 0.8f };
    float position1[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light1);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
	
/**Egy bátor spotlight próbálkozás
	
	float ambient_light2[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light2[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float specular_light2[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//float position2[] = { 15.0f, 1.0f, 10.0f, 1.0f };
	
	float position2[] = { spot_x, spot_y, spot_z, 1.0f };
	
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_light2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_light2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular_light2);
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
	
	GLfloat dirVector0[]={ 0,0,-1};
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spot_cutoff);// set cutoff angle
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dirVector0); 
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1); // set focusing strength	
	*/
}

void set_spot(double gspot_x, double gspot_y, double gspot_z, double gspot_cutoff, double gfocusing)
{
	spot_x += gspot_x;
	spot_y += gspot_y;
	spot_z += gspot_z;
	spot_cutoff += gspot_cutoff;
	focusing += gfocusing;
	printf("Spot_X: %f,Spot_Y: %f,Spot_Z: %f,Spot_Vutoff: %f,Spot_focus: %f\n",spot_x,spot_y,spot_z,spot_cutoff,focusing);
}



/**Feny erossegenek allitasa*/
void set_lighting_intensity(double lightGet)
{
	
	light = light + lightGet;
	
	if (light>1.0f)
	{
		light = 1.0f;
	}
	else if (light<0.0f)
	{
		light = 0.0f;
	}
	else
	{
		light = light;
	}
}

void white_material(Scene* scene)
{
	/**Skybox világítása*/
	float ambient_material_color[] = {0.8f,0.8f,0.8f,1.0f};
    float diffuse_material_color[] = {0.8f,0.8f,0.8f,1.0f};
    float specular_material_color[] = {0.8f,0.8f,0.8f,1.0f};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
}

void cow_material(Scene* scene)
{
	/** comment the material*/
	GLfloat amb[]={0.21f,0.12f,0.054f,1.0f};
	GLfloat diff[]={0.71f,0.41f,0.19f,1.0f};
	GLfloat spec[]={0.38f,0.27f,0.17f,1.0f};
	GLfloat shine=60;
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
}

void house_material(Scene* scene)
{
	/** comment the material*/
	GLfloat amb[]={0.25f,0.148f,0.06475f,1.0f};
	GLfloat diff[]={0.4f,0.2368f,0.1036f,1.0f};
	GLfloat spec[]={0.474597f,0.458561f,0.200621f,1.0f};
	GLfloat shine=76.8f;
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
}
void draw_cow(const Scene* scene)
{
		glEnable(GL_TEXTURE_2D);	
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();						
			glBindTexture(GL_TEXTURE_2D, texture_names[6]);
			glTranslatef(cow_x,cow_y,cow_z);	
			glScaled(cow_scale,cow_scale,cow_scale);
			glRotatef(cow_angle, 0, 0, 2);					
			draw_model(&scene->cow.model);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		
}

void draw_house(const Scene* scene){
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, texture_names[7]);
			glTranslatef(20,20,-5);
			glRotatef(180,0,0,1);
			draw_model(&scene->house.model);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
}

void draw_grasses(const Scene* scene){
	int i,j;
    for(i = 0;i < 60;i++){
        for(j = 0;j < 60;j++){
			glPushMatrix();			
				glTranslatef(grassLocations[i][j][0],grassLocations[i][j][1],5);
				draw_model(&(scene->grass.model));
			glPopMatrix();
        }
    }
	
}

void update_cow_position(){
	
	static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;
	
	double angle;
    double side_angle;
	
    angle = degree_to_radian(cow_angle);
    side_angle = degree_to_radian(cow_angle + 90.0);
	
	cow_x += cos(angle) * cow_speed_y * elapsed_time;
	cow_y += sin(angle) * cow_speed_y * elapsed_time;
	cow_x += cos(side_angle) * cow_speed_x * elapsed_time;
	cow_y += sin(side_angle) * cow_speed_x * elapsed_time;
	cow_angle += cow_angle_speed * elapsed_time;
	
	if(cow_x >= 29 ){
		cow_x = 29;
	}else if(cow_x <= -29){
		cow_x = -29;
	}
	if(cow_y >= 29){
		cow_y = 29;
	}else if(cow_y <= -29){
		cow_y = -29;
	}	
}

void move_cow_y(double y)
{
		cow_speed_y = y;
}
void move_cow_x(double x)
{
		cow_speed_x = x;
}

void move_cow_angle(double angle)
{
		cow_angle_speed = angle;
}

double* get_cow_x_position()
{
	return &cow_x;
}
double* get_cow_y_position()
{
	return &cow_y;
}
double* get_cow_z_position()
{
	return &cow_z;
}
	
	
	

void draw_origin()
{
	if(drawOrigin == 0){		
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1000, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1000, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1000);

    glEnd();
	glDisable(GL_COLOR_MATERIAL);
	}	
}

void setOriginToDraw(int onOff){
	drawOrigin = onOff;
}

void draw_skybox()
{
	double x=30.0f;
	double y=30.0f;
	double z=5.0f;
	
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_COLOR_MATERIAL);
	//Korrigációs eltolás
	glTranslatef(0.0f, 0.0f, 5.0f);	
	glColor3f(1, 1, 1);
	
	
    glBindTexture(GL_TEXTURE_2D, texture_names[5]);
	glBegin(GL_QUADS);
	//Padló:
    glTexCoord2f(0.0,0.0);
    glVertex3f(-x, -y, -z);
	glTexCoord2f(0.0,3.0);
    glVertex3f(-x, y, -z);
	glTexCoord2f(3.0,3.0);
	glVertex3f(x, y, -z);
	glTexCoord2f(3.0,0.0);
	glVertex3f(x, -y, -z);
    glEnd();
	
    glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	glBegin(GL_QUADS);
	//Előlap:
    glTexCoord2f(0.0,0.0);
    glVertex3f(-x, -y, -x);
	glTexCoord2f(0.0,1.0);
    glVertex3f(-x, y, -x);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-x, y, x);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-x, -y, x);
    glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texture_names[3]);
	glBegin(GL_QUADS);
	//Jobb oldal:
    glTexCoord2f(0.0,0.0);
	glVertex3f(x, -y, -x);
	glTexCoord2f(0.0,1.0);
	glVertex3f(x, -y, x);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-x, -y, x);
	glTexCoord2f(1.0,0.0);
    glVertex3f(-x, -y, -x);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_names[2]);
	glBegin(GL_QUADS);
	//Hátlap:
    glTexCoord2f(0.0,0.0);
	glVertex3f(x, -y, x);
	glTexCoord2f(0.0,1.0);
	glVertex3f(x, y, x);
	glTexCoord2f(1.0,1.0);
	glVertex3f(x, y, -x);
	glTexCoord2f(1.0,0.0);
	glVertex3f(x, -y, -x);
    glEnd();
	
    glBindTexture(GL_TEXTURE_2D, texture_names[1]);
	glBegin(GL_QUADS);
	//Bal oldal:
    glTexCoord2f(0.0,0.0);
	glVertex3f(x, y, -x);
	glTexCoord2f(0.0,1.0);
	glVertex3f(x, y, x);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-x, y, x);
	glTexCoord2f(1.0,0.0);
    glVertex3f(-x, y, -x);
    glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texture_names[4]);
	glBegin(GL_QUADS);
	//Fedőlap:
    glTexCoord2f(0.0,0.0);
	glVertex3f(-x, y, x);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-x, -y, x);
	glTexCoord2f(1.0,1.0);
	glVertex3f(x, -y, x);
	glTexCoord2f(1.0,0.0);
	glVertex3f(x, y, x);
    glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
}



void initialize_texture()
{
    unsigned int i;
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    char texture_filenames[][32] = {"textures/sky1.png", //0  Előlap
									"textures/sky2.png", //1  Bal oldal
									"textures/sky3.png", //2  Hátlap
									"textures/sky4.png", //3  Jobb oldal
									"textures/sky5.png", //4  Fedőlap
									"textures/grass1.jpg", //5  Padló
									"textures/cow.png", //6  Cow
									"textures/barn.png"}; //7 Barn
	for (i = 0; i < 8; ++i) {
		printf("Texture Load: %d\n",i+1);
        texture_names[i] = load_texture(texture_filenames[i], images[i]);
    }

	//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); //textúrára is hat ezzel a fény
	
	glEnable(GL_TEXTURE_2D);
}

GLuint load_texture(char* filename, Pixel* image)
{
    GLuint texture_name;
    glGenTextures(1, &texture_name);

    int width;
    int height;

    image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);	

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);
		
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

    return texture_name;
}