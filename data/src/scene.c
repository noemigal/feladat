#include "scene.h"

#include <GL/glut.h>

#include <time.h>

double airplane_y_rotation=0;
double airplane_z_rotation=0;
double airplane_rotate=0;

double brightness=0;
double flash_light=-2;

double cat_move1=0;
double cat_move2=0;


void init_scene(Scene* scene)
{
    load_model(&(scene->land), "models/land.obj");
    scene->texture_land = load_texture("textures/rock.jpg"); 	
	
    load_model(&(scene->cat1), "models/cat.obj");
    scene->texture_cat = load_texture("textures/cat.jpg"); 	
	
    load_model(&(scene->cat2), "models/cat.obj");

    load_model(&(scene->airplane), "models/airplane.obj");
    scene->texture_airplane = load_texture("textures/airplane.png"); 	
	
    load_model(&(scene->water), "models/water.obj");
    scene->texture_water = load_texture("textures/water.jpg"); 
	scene->information = load_texture("textures/info.png"); 

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;
	
    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 10.0;
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f+brightness, 1.0f+brightness, 1.0f+brightness, 1.0f+brightness };
    float specular_light[] = { 1.0f+flash_light, 1.0f+flash_light, 1.0f+flash_light, 1.0f+flash_light };
    float position[] = { 40.0f, 20.0f, 0.0f, 2.0f };
 
	GLfloat light_position[] = {300, 0, -1000, 0.};
    GLfloat light_color[] = {0, 1, 0, 1};
	
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void update_lighting(Scene* scene, double value)
{
	brightness+=value;
	
}	

void flashlight_mode(int value){
	if(value==0){
			flash_light=2;
	}	
	if(value==1){
			flash_light=-2;
	}		
}

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

void draw_scene(const Scene* scene)
{

    set_material(&(scene->material));
    set_lighting();
	glBindTexture(GL_TEXTURE_2D, scene->texture_land);	
    draw_model(&(scene->land));
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_water);	
	glPushMatrix();	
	draw_model(&(scene->water));
	glPopMatrix();	
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_cat);
	glPushMatrix();
	glTranslatef(0.3,0.0-cat_move1,0.05);
	glScalef(0.2, 0.2, 0.2);
    draw_model(&(scene->cat1));
	glPopMatrix();	
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_cat);	
	glPushMatrix();
	glRotatef(180,0,0,1);
	glTranslatef(-0.3,0.195-cat_move2,0.05);
	glScalef(0.2, 0.2, 0.2);
	draw_model(&(scene->cat2));
	glPopMatrix();	

	glBindTexture(GL_TEXTURE_2D, scene->texture_airplane);	
	glPushMatrix();
	glRotatef(0, 180, 180+airplane_rotate, 0);
	glTranslatef( 0.9, 0.5+airplane_y_rotation, 0.5+airplane_z_rotation);
	glScalef(0.2, 0.2, 0.2);
	draw_model(&(scene->airplane));
	glPopMatrix();	
	
	glBindTexture(GL_TEXTURE_2D, scene->information);
}

void airplane_movement(double time){
	airplane_y_rotation=airplane_y_rotation-time/100;
	airplane_z_rotation=airplane_z_rotation+time/100;
	airplane_rotate=airplane_rotate+time*10;	
}		

void nose_touch(double time){
	if(cat_move1<0.054){
		cat_move1+=time/100;
		cat_move2+=time/100;
	}
}
void nose_touch_error(double time){
	if(cat_move1>0){
		cat_move1-=time/100;
		cat_move2-=time/100;
	}
}	

void invisible(){
	glBlendFunc(1, 1);
}