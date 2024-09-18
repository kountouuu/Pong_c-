#include "graphics.h"
#include "Ball.h"
#include "Paddle.h"
#include "GameManager.h"
#include "config.h"
#include <iostream>


void update(float ms)
{
    GameManager* gm = reinterpret_cast<GameManager*>(graphics::getUserData());
    gm->update();
}

void draw()
{
    GameManager* gm = reinterpret_cast<GameManager*>(graphics::getUserData());
    gm->draw();
}

int main()
{
    GameManager my_game(WINDOW_WIDTH, WINDOW_HEIGHT);
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PONG GAME");

    graphics::setUserData(&my_game);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);


    graphics::startMessageLoop();

}