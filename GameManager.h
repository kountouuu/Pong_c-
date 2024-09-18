#pragma once
#include <iostream>
#include "Paddle.h"
#include "Ball.h"



class GameManager
{
	private:
		
		float height, width;
		int score1, score2;
		bool quit;
		Ball* ball;
		Paddle* player1;
		Paddle* player2;
		bool b1;
		bool b2;
		
    public:
		GameManager(float w, float h);
		~GameManager();
		bool checkcollision();
		void scoreUp(Paddle *p);
		void update();
		void draw();
		
		
		
};

