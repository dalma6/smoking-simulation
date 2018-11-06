#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include "animation.hpp"

using namespace std;

/* callback function declarations */
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);

/* redraws the animation so that 'g' can be pressed multiple times */
void reset(void);

int window_width, window_height;

/* animation parameters */
bool moveLighterTo = false;
bool moveLighterFrom = false;
bool moveCigTo = false;
bool flickCig = false;
bool moveCigUp = false;
bool moveCigDown = false;
bool moveCig = false;

/* this angle determines how far cigarette flicking goes */
double flickAngle = 0;

/* creates an instance of the cigarette object; the class Cigarette is to be found in cigarette.hpp */
Cigarette c1(0.25, 1, 3, -4, 2, 0, 1, 1, 1);
/* creates an instance of the ashtray object; the class Ashtray is to be found in additional_obj.hpp */
Ashtray a1(2, 1, 0, 5, -1, 0);
/* creates an instance of the lighter object; the class Lighter is to be found in additional_obj.hpp */
Lighter l1(0.6, 0.7, 0.2, 0.15, 0.3, 0.15, 3, -1, 3, false);

/* creates an instance of the animation object; the class Animation is to be found in animation.hpp */
Animation anim(c1, a1, l1);

int main(int argc, char** argv)
{
	/* GLUT initialization */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	
	/* window creating */
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Smoking");
	
	/* background colour and depth test */
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	
	/* callback functions */
	glutDisplayFunc(on_display);
	glutKeyboardFunc(on_keyboard);
	glutReshapeFunc(on_reshape);
		
	/* entering glut main loop */
	glutMainLoop();
	return 0;
}

static void on_display(void)
{	
    /* we need to clear the previous contetnts of the space */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* enable lighting */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* ambient light coeffs */
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	
	/* diffuse light coeffs */
	GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8, 1.0f};
	
	/* specular light coeffs */
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	
	/* light position */
	GLfloat position[] = { -20, -20, -20, 1.0f };

	/* assignment of light coeffs to gl_light0 */
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position); 

	/* setting the camera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 	gluLookAt(
 		-1, 3, 5,
 		0, 0, 0,
 		0, 1, 0
 	);
	
	anim.render();
	
	glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		/* when esc is pressed, the window is shut */
		case 27:
			exit(0);
			break;
		/* when g is pressed, the ligher moves to the cigarette and lights it, and then moves back to its original place */
		case 'g':
		case 'G':
			reset();
			if(!anim.getAnimParam())
			{
				reset();
				if(l1.getIndLight())
					anim.helpTurnOn();
				moveLighterTo = true;
				glutTimerFunc(20, on_timer, 0);
				break;
			}
	}
}

static void on_reshape(int width, int height)
{
	/* remembring window width and height */
    window_width = width;
    window_height = height;

    /* setting the viewport. */
    glViewport(0, 0, width, height);

    /* setting the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, (float) width / height, 1, 25);
}

static void on_timer(int value)
{
	/* for the lighter-to-cigarette movements */
	if(moveLighterTo) 
		anim.increase_ltcp();
	/* for the cigarette to ashtray movements */
	if(moveCigTo) 
		anim.increase_ctap();
	/* for the lighter-from-cigarette movements */
	if(moveLighterFrom) 
		anim.increase_lfcp();
	/* for cigarette flicking */
	if(flickCig)
		anim.flick();
	
	/* increases flicking angle */
	if(flickAngle < 20 && moveCig)
	{
		moveCigUp = true;
		flickAngle += 0.1;
	}
	
	/* stops flicking */
	if(flickAngle >= 20 && moveCigUp)
	{
		moveCigUp = false;
		moveCigDown = true;
		flickAngle = 0;
	}
	
	/* stops flicking */
	if(flickAngle >= 20 && moveCigDown)
	{
		moveCigDown = false;
		flickAngle = 0;
	}
	
	/* flicing down */
	if(flickAngle < 20 && moveCigDown)
	{
		flickAngle += 0.1;
	}
	
	
	glutPostRedisplay();
	glutTimerFunc(20, on_timer, 0);
}

void reset()
{
	/* render the animation again */
	anim.render();
}


