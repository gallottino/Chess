#include <iostream>
#include <SFML/Graphics.hpp>
#include "ChessItems.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDHT, WINDOW_HEIGHT), "Chess");

    sf::Sprite chessboard;
    sf::Texture text,chessboard_texture;
    text.loadFromFile("../horse.png");
    chessboard_texture.loadFromFile("../chessboard.png");
    Chess::Piece horse(text,CHESSBOARD_ORIGIN_X,CHESSBOARD_ORIGIN_Y,Chess::HORSE);
    chessboard.setPosition(CHESSBOARD_ORIGIN_X,CHESSBOARD_ORIGIN_Y);
    chessboard.setTexture(chessboard_texture);
    chessboard.scale(2,2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            horse.update(window);
        }

        window.clear(sf::Color::White);
        window.draw(chessboard);
        horse.draw(&window);

        window.display();
    }

    return 0;
}