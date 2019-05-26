#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/Chess.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(Chess::WINDOW_WIDTH, Chess::WINDOW_HEIGHT), "Chess");

    sf::Texture text,chessboard_texture;
    Chess::Chessboard chessboard;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        chessboard.update(window);
        window.clear();
        chessboard.render(&window);
        window.display();
    }

    return 0;
}