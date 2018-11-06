#pragma once

#include <cmath>
#include <GL/glut.h>

class Animation;

class Cigarette
{
public:
	Cigarette(double radius, double filter, double rest, double pos_x, double pos_y, double pos_z, double color1, double color2, double color3)
		: _radius{radius}, _filter{filter}, _rest{rest}, _pos_x{pos_x}, _pos_y{pos_y}, _pos_z{pos_z},
		_col1{color1}, _col2{color2}, _col3{color3} { init(); }
	void render() const;
	void init() const;
	friend class Animation;
private:
	double _radius, _filter, _rest;
	double _pos_x, _pos_y, _pos_z;
	double _col1, _col2, _col3;
	bool _combustion_param;
};
