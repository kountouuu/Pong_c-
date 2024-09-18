#include "Paddle.h"
#include <iostream>
#include "config.h"
#include "graphics.h"
#include "scancodes.h"


Paddle::Paddle()
{
	posx = posy = 0;
	startx = starty = 0;
}

Paddle::Paddle(float x, float y)
{
	startx = x;
	starty = y;
	posx = x;
	posy = y;
}

float Paddle::getX()
{
	return posx;
}

float Paddle::getY()
{
	return posy;
}


void Paddle::Reset()
{
	posx = startx;
	posy = starty;
}

//Ta Paddles einai makrostena me apotelesma na xreiazetai na ftiaksoume duo antikeimena disks wste na kaluptoun eparkws thn epifaneia tous
//gia na ta diaxwrisoume ftiaxnoume ton ena disko otan b = false kai ton allo otan b = true.
Disk Paddle::getCollisionHull(bool b) const
{
	if (b == true) {
		Disk disk1;
		disk1.posx = posx;
		disk1.posy = posy +15;
		disk1.radius = PADDLE_WIDTH  / 2 + 3;
		return disk1;
	}
	else {
			Disk disk2;
			disk2.posx = posx;
			disk2.posy = posy - 15;
			disk2.radius = PADDLE_WIDTH / 2 + 3;
			return disk2;
	}
	
}

void Paddle::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "paddle.png";
	br.gradient = true;
	br.outline_opacity = 0.0f;

	graphics::drawRect(posx, posy, PADDLE_WIDTH, PADDLE_HEIGHT, br);
}

//bool b is a variable that helps identify the player.
void Paddle::update(bool b)
{
	if (graphics::getKeyState(graphics::SCANCODE_W) && b == false  && posy >= 40) {
		posy -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S) && b == false && posy <= CANVAS_HEIGHT - 40) {
		posy += speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_O) && b == true && posy >= 40) {
		posy -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_L) && b == true && posy <= CANVAS_HEIGHT - 40) {
		posy += speed * graphics::getDeltaTime() / 10.0f;
	}
}

std::ostream& operator<<(std::ostream& left, Paddle p)
{
	left << "Paddle [" << p.getX() << "," << p.getY() << "]"  << std::endl;
	return left;
}