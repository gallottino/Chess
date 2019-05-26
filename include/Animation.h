//
// Created by Gallottino on 23/05/2019.
//

#ifndef CHESS_ANIMATION_H
#define CHESS_ANIMATION_H

#include <SFML/Graphics.hpp>



class Animation {

public:
    enum Type{
        EAT,
        MOVE
    };

    Animation();
    void startAnimation(Type type);
    void update();
    void stopAnimation();
    void render(sf::RenderWindow *window);
    void setPosition(int i, int j);

private:

    sf::Texture smoke_asset[5],smoke_asset_eat[5];
    sf::Sprite frames[5],frames_eat[5];
    sf::Clock clock;
    Type type;

    bool mStarted;
    int now;


};



#endif //CHESS_ANIMATION_H
