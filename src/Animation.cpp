//
// Created by Gallottino on 23/05/2019.
//

#include "Animation.h"
#include "Chess.h"


Animation::Animation() {

    type = MOVE;
    for(int i=0;i<5;i++){
        smoke_asset[i].loadFromFile("../images/smoke_asset.png",sf::IntRect(i * Chess::BOX_SIZE, 0, Chess::BOX_SIZE,Chess::BOX_SIZE));
        frames[i].setTexture(smoke_asset[i]);

        smoke_asset_eat[i].loadFromFile("../images/smoke_asset_eat.png",sf::IntRect(i * Chess::BOX_SIZE, 0, Chess::BOX_SIZE,Chess::BOX_SIZE));
        frames_eat[i].setTexture(smoke_asset_eat[i]);
    }

    mStarted = false;
}

void Animation::setPosition(int i,int j)
{
    for(int h=0;h<5;h++){
        frames[h].setPosition(j * Chess::BOX_SIZE + Chess::CHESSBOARD_ORIGIN_X, i * Chess::BOX_SIZE + Chess::CHESSBOARD_ORIGIN_Y);
        frames_eat[h].setPosition(j * Chess::BOX_SIZE + Chess::CHESSBOARD_ORIGIN_X, i * Chess::BOX_SIZE + Chess::CHESSBOARD_ORIGIN_Y);
    }
}

void Animation::startAnimation(Type type)
{
    this->type = type;
    clock.restart();
    now = 0;
    mStarted = true;
}

void Animation::stopAnimation()
{
    now = 5;
    mStarted = false;
}

void Animation::update()
{
    if(mStarted){
        sf::Time elapsed = clock.getElapsedTime();

        if(elapsed.asMilliseconds() >=100){
            now++;
            clock.restart();
            if(now == 5) stopAnimation();
        }
    }
}

void Animation::render(sf::RenderWindow *window)
{
    if(mStarted)
        if(type == EAT)
            window->draw(frames_eat[now]);
        else
            window->draw(frames[now]);
}
