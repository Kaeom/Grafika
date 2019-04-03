#include "scene.h"
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include "model.h"
#include "draw.h"
#include <math.h>

/**Globalis valtozok:*/

/**Szin parameterezesek*/
double red = 0.3;
double green = 0.0;
double blue = 0.0;

double red2 = 0.8;
double green2 = 0.0;
double blue2 = 0.0;

/**Vilagitas ereje*/
double light = 0.8f;

/**Tehen hejzete, skalazasa, iranya*/
double cow_x = 0.0f;
double cow_y = 0.0f;
double cow_z = -4.9f;
double cow_speed_x = 0.0f;
double cow_speed_y = 0.0f;
double cow_speed_z = 0.0f;
double cow_scale = 0.25f;
double cow_angle = -90;
double cow_deltaAngle = 0.0f;
double cow_deltaMove = 0;

double grassLocations[60][60][2];

void init_scene(Scene* scene)
{
    load_model("models/Cow.obj", &scene->cow.model);
	
	/*load_model("models/grass1.obj",&(scene->grass));
	
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
	
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
	white_material(scene);/**Skybox Fehér Material*/
	draw_skybox();
	cow_material(scene); //Cow Barna Material
	update_cow_position();
	draw_cow(scene);
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
	float ambient_light[] = { light, light, light, 1.0f };
    float diffuse_light[] = { light, light, light, 1.0f };
    float specular_light[] = { light, light, light, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 0.0f };
	
	float ambient_light1[] = { light, light, light, 1.0f };
    float diffuse_light1[] = { light, light, light, 1.0f };
    float specular_light1[] = { light, light, light, 1.0f };
    float position1[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light1);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
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
/**Anyagtulajdonságok*/
void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
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
	/* comment the material*/
	GLfloat amb[]={0.21f,0.12f,0.1f,1.0f};
	GLfloat diff[]={0.71f,0.41f,0.19f,1.0f};
	GLfloat spec[]={0.38f,0.27f,0.17f,1.0f};
	GLfloat shine=60;
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
}
void draw_cow(const Scene* scene)
{
		glEnable(GL_TEXTURE_2D);	
		glPushMatrix();						
			//glBindTexture(GL_TEXTURE_2D, texture_names[6]);
			glTranslatef(cow_x,cow_y,cow_z);	
			glScaled(cow_scale,cow_scale,cow_scale);
			glRotatef(cow_angle, 0, 0, 2);					
			draw_model(&scene->cow.model);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		
}

/**void draw_grasses(const Scene* scene){
	int i,j;
    for(i = 0;i < 60;i++){
        for(j = 0;j < 60;j++){
			glPushMatrix();			
				glTranslatef(grassLocations[i][j][0],grassLocations[i][j][1],-10);
				draw_model(&(scene->grass));
			glPopMatrix();
        }
    }
	
}*/

void update_cow_position(){
	
	static int last_frame_time = 0;
	int current_time;
	double time;	
	   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = time;
	
	double angle;
    double side_angle;
	
    angle = degree_to_radian(cow_angle);
    side_angle = degree_to_radian(cow_angle + 90.0);
	
	cow_x += cos(angle) * cow_speed_y * time;
	cow_y += sin(angle) * cow_speed_y * time;
	cow_x += cos(side_angle) * cow_speed_x * time;
	cow_y += sin(side_angle) * cow_speed_x * time;
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
		cow_angle += angle;
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

void draw_skybox()
{
	double x=30.0f;
	double y=30.0f;
	double z=5.0f;
	
	glEnable(GL_TEXTURE_2D);
	
	//glDisable(GL_COLOR_MATERIAL);
	//Korrigációs eltolás
	glTranslatef(0.0f, 0.0f, 5.0f);
	
    glBindTexture(GL_TEXTURE_2D, texture_names[5]);
	glBegin(GL_QUADS);
	//Padló:
    glTexCoord2f(0.0,0.0);
    glVertex3f(-x, -y, -z);
	glTexCoord2f(0.0,1.0);
    glVertex3f(-x, y, -z);
	glTexCoord2f(1.0,1.0);
	glVertex3f(x, y, -z);
	glTexCoord2f(1.0,0.0);
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
									"textures/asphalt.png", //5  Padló
									"textures/cow.png"}; //6  Cow
	for (i = 0; i < 7; ++i) {
		printf("Texture Load: %d\n",i+1);
        texture_names[i] = load_texture(texture_filenames[i], images[i]);
    }

	//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); //textúrára is hat ezzel a fény
	
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
		
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

    return texture_name;
}