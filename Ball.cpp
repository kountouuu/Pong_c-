#include <iostream>
#include "Ball.h"
#include <stdlib.h> 
#include <time.h> 
#include "graphics.h"
#include "config.h"
#include "util.h"

using namespace std;


Ball::Ball(float pos_x, float pos_y)
{
	startposx = pos_x;
	startposy = pos_y;
	posx = pos_x;
	posy = pos_y;
	speed = 7.0f;
	direction = STOP;
}

float Ball::getX()
{
	return posx;
}

float Ball::getY()
{
	return posy;
}

eDir Ball::getDirection()
{
	return direction;
}

void Ball::Reset()
{
	posx = startposx;
	posy = startposy;
	direction = STOP;
}

void Ball::ChangeDirection(eDir d) {
	direction = d;
}

void Ball::RandomDirection()
{
	direction = (eDir)(1 + rand() % 6);
}

void Ball::Move()
{
	switch (direction)
	{
	case STOP:
		break;
	case LEFT:
		posx-= speed * graphics::getDeltaTime() / 10.0f;
		break;
	case UPLEFT:
		posx-= speed * graphics::getDeltaTime() / 10.0f;
		posy+= speed * graphics::getDeltaTime() / 10.0f;
		break;
	case DOWNLEFT:
		posx-= speed * graphics::getDeltaTime() / 10.0f;
		posy-= speed * graphics::getDeltaTime() / 10.0f;
		break;
	case RIGHT:
		posx+= speed * graphics::getDeltaTime() / 10.0f;
		break;
	case UPRIGHT:
		posx+= speed * graphics::getDeltaTime() / 10.0f;
		posy+= speed * graphics::getDeltaTime() / 10.0f;
		break;
	case DOWNRIGHT:
		posx+= speed * graphics::getDeltaTime() / 10.0f;
		posy-= speed * graphics::getDeltaTime() / 10.0f;
		break;
	default:
		break;
	}

}

void Ball::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "ballp.png";
	br.gradient = true;
	br.outline_opacity = 0.0f;

	graphics::drawRect(posx,posy, BALL_WIDTH, BALL_HEIGHT, br);
}

void Ball::update(bool b1, bool b2)
{
	if (b1 == true)
	{
		if (b2 == true)
		{
			ChangeDirection((eDir)(4+ rand() % 3));//if b2=true then the left paddle hits the ball and the ball can go only in the right middle
		}
		else {
			ChangeDirection((eDir)(1 + rand() % 3));//if b2=false then the left paddle hits the ball and the ball can go only in the left middle
		}
	}
	if (direction == STOP) {
		RandomDirection();
	}
	Move();
}

Disk Ball::getCollisionHull() const
{
	Disk disk;
	disk.posx = posx;
	disk.posy = posy;
	disk.radius = BALL_WIDTH / 2;
	return disk;
}

std::ostream & operator<<(std::ostream & left, Ball b)
{
	left << "Ball [" << b.getX() << "," << b.getY() << "]" << "[" << b.getDirection() << "]" << endl;
	return left;
}
