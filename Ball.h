#pragma once
#include <iostream>
#include "util.h"


enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };


class Ball
{
	private:
		float startposx;
		float startposy;
		float posx;
		float posy;
		float speed;
		friend std::ostream & operator<<(std::ostream & left, Ball b);
	public:
		Ball(float pos_x, float pos_y);
		eDir direction;
		float getX();
		float getY();
		eDir getDirection();
		void Reset();
		void ChangeDirection(eDir d);
		void RandomDirection();
		void Move();
		void draw();
		void update(bool b1,bool b2);//b1 is true when we have collision and b2 is true 
		//when we have collision with the left paddle and false when we have collision with the right paddle
		Disk getCollisionHull() const ;

};


