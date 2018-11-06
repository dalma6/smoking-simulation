#include "cigarette.hpp"

double start_cx, start_cy, start_cz;

extern bool moveCigUp;
extern bool moveCigDown;
extern double flickAngle;

void Cigarette::render() const
{
	double angle = 0;
	
	/* enabling light material so that the assigned colors show properly */
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glTranslatef(_pos_x, _pos_y, _pos_z);
	glRotatef(75, 0, 1, 0);
	glColor3f(1, 0.25, 0);
	
	/* flicking */
	if(moveCigUp)
		glRotatef(-flickAngle, 1, 0, 0);
	else if(moveCigDown)
		glRotatef(flickAngle, 1, 0, 0);
		
	/* creates the circle which is used to fill the back side of the cylinder which is the actual cigarette */
	glBegin(GL_POLYGON);
		for(double angle=0; angle <= 2*M_PI; angle += M_PI/120)
			glVertex3f(_radius*cos(angle), _radius*sin(angle), 0);
		glVertex3f(_radius*cos(0), _radius*sin(0), 0);
	glEnd();
	
	/* creates the filter of the cigarette */
	glBegin(GL_TRIANGLE_STRIP);
		for(angle=0; angle <= 2*M_PI; angle += M_PI/120)
		{
			glVertex3f(_radius*cos(angle), _radius*sin(angle), 0);
			glVertex3f(_radius*cos(angle), _radius*sin(angle), _filter);
		}
		glVertex3f(_radius*cos(0), _radius*sin(0), 0);
		glVertex3f(_radius*cos(0), _radius*sin(0), _filter);
	glEnd();
	
	glColor3f(1, 1, 1);
	
	/* creates the rest of the cigarette */
	glBegin(GL_TRIANGLE_STRIP);
		for(angle=0; angle <= 2*M_PI; angle += M_PI/120)
		{
			glVertex3f(_radius*cos(angle), _radius*sin(angle), _filter);
			glVertex3f(_radius*cos(angle), _radius*sin(angle), _rest);
		}
		glVertex3f(_radius*cos(0), _radius*sin(0), _filter);
		glVertex3f(_radius*cos(0), _radius*sin(0), _rest);
	glEnd();
	
	/* creates the circle which is used to fill the front side of the cylinder which is the actual cigarette */
	glColor3f(_col1, _col2, _col3);
	glBegin(GL_POLYGON);
		for(double angle=0; angle <= 2*M_PI; angle += M_PI/120)
			glVertex3f(_radius*cos(0), _radius*sin(0), _rest);
	glEnd();
}

/* remember the initial coordinates of the cigarette */
void Cigarette::init() const
{
	start_cx = _pos_x;
	start_cy = _pos_y;
	start_cz = _pos_z;
}