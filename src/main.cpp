#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/ChessItems.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess");
    sf::Sprite chessboard;
    sf::Texture text,chessboard_texture;
    Chess::ChessBoard chessBoard;

    chessboard_texture.loadFromFile("../chessboard.png");
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

            chessBoard.update(window);
        }

        window.clear();
        window.draw(chessboard);
        chessBoard.draw(&window);
        window.display();
    }

    return 0;
}