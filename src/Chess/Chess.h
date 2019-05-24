//
// Created by dgall on 24/05/2019.
//

#ifndef CHESS_CHESS_H
#define CHESS_CHESS_H

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

namespace Chess {

 /*   const int BOX_SIZE = 64;
    const int PIECE_SIZE = BOX_SIZE;
    const int CHESSBOARD_SIZE = BOX_SIZE * 8;

    enum Type{
        PAWN,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING,
        TOWER
    };
    enum Color{
        WHITE,
        BLACK,
        VOID
    };

    class Piece {

    public:
        Piece(int i, int j,Chess::Color color);
        void render(sf::RenderWindow* window);
        void update(const sf::RenderWindow &window);
        virtual void findMovement() = 0;
        void move(int i, int j);
        bool checkMove(int i,int j);
        Type getType() ;
        Color getColor();

    private:
        sf::Texture texture;
        sf::Sprite sprite;

        Chess::Type type;
        Chess::Color color;
        Chess::Piece** chessboard;

        std::list<std::pair<int,int>> movements;

        int pos_i,pos_j;

    };

    class Pawn : public Piece {
        void findMovement(){

        }
    };

    */
}

#endif //CHESS_CHESS_H
