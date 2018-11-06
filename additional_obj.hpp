#pragma once

#include <cmath>
#include <GL/glut.h>

class Animation;

class Ashtray
{
public:
	Ashtray(double radius, double height, double dist, double pos_x, double pos_y, double pos_z)
		: _radius{radius}, _height{height}, _dist{dist},
		_pos_x{pos_x}, _pos_y{pos_y}, _pos_z{pos_z} {}
	void render() const;
	friend class Animation;
private:
	double _radius, _height, _dist;
	double _pos_x, _pos_y, _pos_z;	
};

class Lighter
{
public:
	Lighter(double lighter_x, double lighter_y, double lighter_z, double fire_x, double fire_y, double fire_z,
		double pos_x, double pos_y, double pos_z, bool ind_light)
		: _lighter_x{lighter_x}, _lighter_y{lighter_y}, _lighter_z{lighter_z},
		  _fire_x{fire_x}, _fire_y{fire_y}, _fire_z{fire_z},
		  _pos_x{pos_x}, _pos_y{pos_y}, _pos_z{pos_z},
		  _ind_light{ind_light} { init(); }
	void render() const;
	void init() const;
	/* getter for info about whether the lighter should be displaying a flame; needs to be checked by on_keyboard func */
	bool getIndLight() const;
	void turnOn();
	friend class Animation;
private:
	double _lighter_x, _lighter_y, _lighter_z;
	double _fire_x, _fire_y, _fire_z;
	double _pos_x, _pos_y, _pos_z;
	bool _ind_light;
	void light() const;
};
