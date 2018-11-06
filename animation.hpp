#pragma once

#include "cigarette.hpp"
#include "additional_obj.hpp"
#include <iostream>
#include <cmath>

using namespace std;

class Animation
{
public:
	Animation(Cigarette c, Ashtray a, Lighter l, double anim_param = 0, double combustion_param = 0)
		: _c{c}, _a{a}, _l{l}, _anim_param{anim_param}, _combustion_param{combustion_param} {}
	void render() const;
	void helpTurnOn();
	void move_lighter_to_cigarette();
	void move_lighter_from_cigarette();
	void move_cigarette_to_ashtray();
	void move_cigarette_from_ashtray();
	void increase_ltcp();
	void increase_lfcp();
	void increase_ctap();
	void increase_cfap();
	void checkCollisions();
	double getAnimParam() const;
	void flick();
private:
	Cigarette _c;
	Ashtray _a;
	Lighter _l;
	double _anim_param;
	double _combustion_param;
};