#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Camera camera;
	Model land;
	Model cat1;
	Model cat2;
	Model airplane;
	Model water;
    Material material;
    GLuint texture_land;
    GLuint texture_cat;
    GLuint texture_airplane;
    GLuint texture_water;
    GLuint information;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Update the light of the scene.
 */
void update_lighting(Scene* scene, double value);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 *Set the airplane move of the scene.
 */
void airplane_movement();


#endif /* SCENE_H */
