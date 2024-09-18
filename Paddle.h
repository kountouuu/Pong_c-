#pragma once
#include <iostream>
#include "util.h"



class Paddle 
{
private:
	float posx, posy;
	float startx, starty;
	float speed = 10.0f;
	friend std::ostream& operator<<(std::ostream& left, Paddle p);
public:
	Paddle();
	Paddle(float x,float y);
	float getX();
	float getY();
	void Reset();
	void draw();
	void update(bool b);
	Disk getCollisionHull(bool b) const;

};

