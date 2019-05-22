//
// Created by Gallottino on 23/05/2019.
//

#include "Animation.h"
#include "ChessItems.h"


Animation::Animation() {



    for(int i=0;i<5;i++){
        smoke_asset[i].loadFromFile("../images/smoke_asset_eat.png",sf::IntRect(i * BOX_SIZE, 0, BOX_SIZE,BOX_SIZE));

        frames[i].setTexture(smoke_asset[i]);
    }

    //now = 5;
    mStarted = false;
}

void Animation::setPosition(int i,int j)
{
    for(int h=0;h<5;h++){
        frames[h].setPosition(j * BOX_SIZE + CHESSBOARD_ORIGIN_X, i * BOX_SIZE + CHESSBOARD_ORIGIN_Y);
    }
}

void Animation::startAnimation()
{
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

void Animation::draw(sf::RenderWindow *window)
{
    if(mStarted)
        window->draw(frames[now]);
}
