#include "additional_obj.hpp"

double start_lx, start_ly, start_lz;

void Ashtray::render() const
{
	/* enabling light material so that the assigned colors show properly */
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(0.5, 0.25, 0.5);
	double angle = 0;
	
	glTranslatef(_pos_x, _pos_y, _pos_z);
	glRotatef(270, 1, 0, 0);
	
	/* draws the base of the ashtray */
	glBegin(GL_POLYGON);
		for(double angle=0; angle <= 2*M_PI; angle += M_PI/120)
			glVertex3f(_radius*cos(angle), _radius*sin(angle), 0);
		glVertex3f(_radius*cos(0), _radius*sin(0), 0);
	glEnd();
	
	/* draws the rest of the ashtray*/
	glColor3f(0, 0, 1);
	glBegin(GL_TRIANGLE_STRIP);
		for(angle=0; angle <= 2*M_PI; angle += M_PI/120)
		{
			glVertex3f(_radius*cos(angle), _radius*sin(angle), 0);
			glVertex3f(_radius*cos(angle), _radius*sin(angle), _height);
		}
		glVertex3f(_radius*cos(0), _radius*sin(0), 0);
		glVertex3f(_radius*cos(0), _radius*sin(0), _height);
	glEnd();
}

void Lighter::render() const
{
	/* enabling light material so that the assigned colors show properly */
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glColor3f(1, 1, 0);
	/* draws the lighter */
	glTranslatef(_pos_x, _pos_y, _pos_z);
	glScalef(_lighter_x, _lighter_y, _lighter_z);
	glutSolidCube(1);
	if(_ind_light)
		light();
}

void Lighter::init() const
{
	start_lx = _pos_x;
	start_ly = _pos_y;
	start_lz = _pos_z;
}

void Lighter::light() const
{	
	glColor3f(1, 0.25, 0);
	glPushMatrix();
		glTranslatef(-0.15, _lighter_y*1.2, 0);
		glScalef(_fire_x, _fire_y, _fire_z);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();
}

/* get the indicator for if the cigarette is lit */
bool Lighter::getIndLight() const
{
	return _ind_light;
}

/* turns the animation on */
void Lighter::turnOn()
{
	_ind_light = true;
}