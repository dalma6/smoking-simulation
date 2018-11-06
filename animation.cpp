#include "animation.hpp"

extern bool moveLighterTo;
extern bool moveLighterFrom;
extern bool moveCigTo;

extern bool flickCig;
extern bool moveCig;
extern bool moveCigUp;
extern bool moveCigDown;

extern double start_cx, start_cy, start_cz;
extern double start_lx, start_ly, start_lz;

double end_cx, end_cy, end_cz;
double end_lx, end_ly, end_lz;

/* calls the drawing functions */
void Animation::render() const
{
	glPushMatrix();
		_c.render();
	glPopMatrix();
	glPushMatrix();
		_a.render();
	glPopMatrix();
	glPushMatrix();
		_l.render();
	glPopMatrix();
}

/* turns the light on */
void Animation::helpTurnOn()
{
	_l.turnOn();
}

/* Increases the lighter-to-cigarette animation parameter and calls the moving function if its indicator is set to true.
When it reaches 1, the parameter is reset and the indicator is set to false. */
void Animation::increase_ltcp()
{
	if(_anim_param < 1)
	{
		/* checks for collisions and changes behaviour if necessary */
		checkCollisions();
		_l._ind_light = true;
		_anim_param += 0.005;
		if(moveLighterTo)
			move_lighter_to_cigarette();
		_c._col1 = 1;
		_c._col2 = 0.25;
		_c._col3 = 0;
	}
	else
	{
		_anim_param = 0;
		moveLighterTo = false;
		moveLighterFrom = true;
		_l._ind_light = false;
	}
}

/* Increases the lighter-from-cigarette animation parameter and calls the moving function if its indicator is set to true.
When it reaches 1, the parameter is reset and the indicator is set to false. */
void Animation::increase_lfcp()
{
	if(_anim_param < 1)
	{
		_anim_param += 0.005;
		if(moveLighterFrom)
			move_lighter_from_cigarette();
	}
	else
	{
		_anim_param = 0;
		moveLighterFrom = false;
		moveCigTo = true;
	}
}

/* Increases the cigarette-to-ashtray animation parameter and calls the moving function if its indicator is set to true.
When it reaches 1, the parameter is reset and the indicator is set to false. */
void Animation::increase_ctap()
{
	/* checks for collisions and changes behaviour if necessary */
	checkCollisions();
	if(_anim_param < 1)
	{
		_anim_param += 0.005;
		if(moveCigTo)
			move_cigarette_to_ashtray();
	}
	else
	{
		_anim_param = 0;
		moveCigTo = false;
		flickCig = true;
	}
}

/* controls flicking */
void Animation::flick()
{
	_anim_param = 0;
	if(_c._rest > _c._filter)
	{
		_c._rest -= 0.005;
		if(flickCig)
			moveCig = true;
	}
	else
	{
		flickCig = false;
		moveCig = false;
		moveCigUp = false;
		moveCigDown = false;
		_c._pos_y -= _a._height;
		_c._pos_x += _a._radius;
	}
}

/* Moves the lighter towards the cigarette following the imaginary line connecting these objects. */
void Animation::move_lighter_to_cigarette()
{
	_l._pos_x = start_lx + (_c._pos_x-start_lx)*_anim_param;
	_l._pos_y = start_ly + (_c._pos_y-start_ly)*_anim_param;
	_l._pos_z = start_lz + (_c._pos_z-start_lz)*_anim_param;
}

/* Turns the lighter off and moves the lighter away from the cigarette following the imaginary line connecting these objects. */
void Animation::move_lighter_from_cigarette()
{
	_l._ind_light = false;
	_l._pos_x = end_lx + (start_lx-end_lx)*_anim_param;
	_l._pos_y = end_ly + (start_ly-end_ly)*_anim_param;
	_l._pos_z = end_lz + (start_lz-end_lz)*_anim_param;
}

/* Moves the cigarette towards the ashtray following the imaginary line connecting these objects. */
void Animation::move_cigarette_to_ashtray()
{
	_c._pos_x = start_cx + (_a._pos_x-start_cx)*_anim_param;
	_c._pos_y = start_cy + (_a._pos_y-start_cy)*_anim_param;
	_c._pos_z = start_cz + (_a._pos_z-start_cz)*_anim_param;
}

/* getter for the animation parameter */
double Animation::getAnimParam() const
{
	return _anim_param;
}

/* deals with collisions; based on the touching spheres concept */
void Animation::checkCollisions()
{
	double ac_x = _a._pos_x-_c._pos_x;
	double ac_y = _a._pos_y-_c._pos_y;
	double ac_z = _a._pos_z-_c._pos_z;
	double dist_ac = sqrt(ac_x*ac_x + ac_y*ac_y + ac_z*ac_z);
	if(dist_ac <= _a._radius/0.6)
	{
		moveCigTo = false;
		flickCig = true;
		end_cx = _c._pos_x;
		end_cy = _c._pos_y;
		end_cz = _c._pos_z;
		_anim_param = 0;
	}
	
	double lc_x = _l._pos_x-_c._pos_x;
	double lc_y = _l._pos_y-_c._pos_y;
	double lc_z = _l._pos_z-_c._pos_z;
	double dist_lc = sqrt(lc_x*lc_x + lc_y*lc_y + lc_z*lc_z);
	if(dist_lc <= _l._lighter_x + (_c._filter+_c._rest)/2 || dist_lc <= _l._lighter_y + (_c._filter+_c._rest)/2
		|| dist_lc <= _l._lighter_z + (_c._filter+_c._rest)/2)
	{
		moveLighterTo = false;
		moveLighterFrom = true;
		end_lx = _l._pos_x;
		end_ly = _l._pos_y;
		end_lz = _l._pos_z;
		_anim_param = 0;
	}
}