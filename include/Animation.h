//
// Created by Gallottino on 23/05/2019.
//

#ifndef CHESS_ANIMATION_H
#define CHESS_ANIMATION_H

#include <SFML/Graphics.hpp>



class Animation {

public:
    Animation();
    void startAnimation();
    void update();
    void stopAnimation();
    void draw(sf::RenderWindow *window);

    void setPosition(int i, int j);

private:
    sf::Texture smoke_asset[5];
    sf::Sprite frames[5];
    sf::Clock clock;

    bool mStarted;
    int now;


};



#endif //CHESS_ANIMATION_H
