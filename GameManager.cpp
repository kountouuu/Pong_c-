#include "GameManager.h"
#include <iostream>
#include <math.h>
#include "time.h"
#include "Paddle.h"
#include "Ball.h"
#include "graphics.h"
#include "config.h"
#include "scancodes.h"

GameManager::GameManager(float w, float h)
{
	width = w;
	height = h;
	score1 = 0;
	score2 = 0;
	quit = false;
	ball = new Ball(w / 2, h / 2);
	player1 = new Paddle(50, h / 2);
	player2 = new Paddle(w - 50, h / 2);
	b1 = false;
	b2 = false;
}

GameManager::~GameManager()
{
	delete ball, player1, player2;
		
}

bool GameManager::checkcollision()
{
	//initialize the disk of the ball
	Disk d1 = ball->getCollisionHull();

	//initialize two disks for the 1st player
	//disk d21 is on the down part of the left paddle and disk d22 is on the upper part of the left paddle
	Disk d21 = player1->getCollisionHull(true);
	Disk d22 = player1->getCollisionHull(false);

	//initialize two disks for the 2nd player
	//disk d31 is on the down part of the right paddle and disk d32 is on the upper part of the right paddle
	Disk d31 = player2->getCollisionHull(true);
	Disk d32 = player2->getCollisionHull(false);

	
	float dx11 = d1.posx - d21.posx; //dx between down disk of player1(left paddle) and ball
	float dx12 = d1.posx - d22.posx;//dx between upper disk of player1(left paddle) and ball

	
	float dx21 = d1.posx - d31.posx;//dx between down disk of player2(right paddle) and ball
	float dx22 = d1.posx - d32.posx;//dx between upper disk of player2(right paddle) and ball

	
	float dy11 = d1.posy - d21.posy;//dy between down disk of player1(left paddle) and ball
	float dy12 = d1.posy - d22.posy;//dy between upper disk of player1(left paddle) and ball

	
	float dy21 = d1.posy - d31.posy;//dy between down disk of player2(right paddle) and ball
	float dy22 = d1.posy - d32.posy;//dy between upper disk of player2(right paddle) and ball


	if (sqrtf(dx11 * dx11 + dy11 * dy11) < d1.radius + d21.radius) {
		b1 = true;
		b2 = true;
		return true;
	}
	else if (sqrtf(dx12 * dx12 + dy12 * dy12) < d1.radius + d22.radius)
	{
		b1 = true;
		b2 = true;
		return true;
	}
	else if (sqrtf(dx21 * dx21 + dy21 * dy21)  < d1.radius + d31.radius)
	{
		b1 = true;
		b2 = false;
		return true;
	}
	else if (sqrtf(dx22 * dx22 + dy22 * dy22)  < d1.radius + d32.radius)
	{
		b2 = true;
		b2 = false;
		return true;
	}
	else
	{
		b1 = false;
		b2 = false;
		return false;
	}


}

void GameManager::scoreUp(Paddle *p)
{
	if (p == player1) {
		score1++;
		graphics::playSound(std::string(ASSET_PATH) + "ppoint.mp3", 0.5f);
	}
	else if (p == player2) {
		score2++;
		graphics::playSound(std::string(ASSET_PATH) + "ppoint.mp3", 0.5f);

	}

	ball->Reset();
	player1->Reset();
	player2->Reset();
}

void GameManager::update()
{
	//update ball
	if (ball)
	{
		//bottom wall
		if (ball->getY() <= 40) {
			if (1 + rand() % 7 > 4) {
				ball->direction = UPLEFT;
			}
			else
			{
				ball->direction = UPRIGHT;
			}
		}

		//top wall
		if (ball->getY() >= CANVAS_HEIGHT) {
			//choose randomly if the ball goes leftdownwards or right downwards
			if (1 + rand() % 7 > 4) {
				ball->direction = DOWNLEFT;
			}
			else 
			{
				ball->direction = DOWNRIGHT;
			}
		}

		//right wall
		if (ball->getX() >= CANVAS_WIDTH - 10) {
			score2++;
			ball->Reset();
		}

		//left wall 
		if (ball->getX() <= 0) {
			score1++;
			ball->Reset();
		}

		ball->update(b1, b2);
	}

	//update players
	if (player1)
		player1->update(false);

	if (player2)
		player2->update(true);
	
	checkcollision();

	
}

void GameManager::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background_thumb.png";

	//draw backround
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw ball
	if (ball)
		ball->draw();

	//draw players
	if (player1)
		player1->draw();

	if (player2)
		player2->draw();

	graphics::setFont(std::string(ASSET_PATH) + "Tooney.ttf");

	//draw the score for the left player
	char info1[6];
	sprintf_s(info1, "(%i)", score1);
	graphics::drawText(CANVAS_WIDTH / 2 + 25, 50 ,60, info1,br);

	//draw the score for the right player
	char info2[6];
	sprintf_s(info2, "(%i)", score2);
	graphics::drawText(CANVAS_WIDTH / 2 - 150, 50, 60, info2, br);

	

}



