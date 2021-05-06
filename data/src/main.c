#include "callbacks.h"
#include "init.h"

#include <time.h>
#include <stdlib.h>

#include <SOIL/SOIL.h>

#include <GL/glut.h>

#include <stdio.h>

 
void set_callbacks()
{
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
	glutSpecialFunc(SpecialInput);
    glutIdleFunc(idle);
}


void initialize()
{

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    int window;
	
	srand(time(0));
    glutInit(&argc, argv);

    glutInitWindowSize(1366, 768);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    window = glutCreateWindow("Two kittens on an island!");
    glutSetWindow(window);
	
	initialize();
	
    init_opengl();
    init_scene(&scene);
    init_camera(&camera);
    set_callbacks();

    glutMainLoop();
    return 0;
}
		