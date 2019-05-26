//
// Created by dgall on 24/05/2019.
//

#ifndef CHESS_CHESS_H
#define CHESS_CHESS_H

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Animation.h"

namespace Chess {

    const int BOX_SIZE = 64;
    const int PIECE_SIZE = BOX_SIZE;
    const int CHESSBOARD_SIZE = BOX_SIZE * 8;
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 640;
    const int CHESSBOARD_ORIGIN_X = WINDOW_WIDTH/2 - CHESSBOARD_SIZE/2;
    const int CHESSBOARD_ORIGIN_Y = WINDOW_HEIGHT/2 - CHESSBOARD_SIZE/2;

    class Piece;
    class ChessBoard;

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

    class Chessboard {
    public:
        Chessboard();
        Piece* getPiece(int i, int j){return chessboard[i][j];}
        void render(sf::RenderWindow *window);
        void update(const sf::RenderWindow &window);
    private:
        Chess::Color turn;
        Chess::Piece* chessboard[8][8];

        sf::Texture black_box,white_box,selected_texture;
        sf::Sprite chessboard_sprite[8][8],selected_icon;

        Animation animation;

        bool selected;
        int selected_i,selected_j;
    };

    class Piece {
    public:
        Piece(int i, int j,Chess::Color color,Chessboard* chessboard);
        void render(sf::RenderWindow* window);
        void update(const sf::RenderWindow &window);
        virtual void findMovement() = 0;
        void move(int i, int j);
        bool checkMove(int i,int j);
        std::list<std::pair<int,int>> getMovements(){return box_checked;}
        Type getType() ;
        Color getColor();

    protected:
        sf::Texture texture;
        sf::Sprite sprite;

        Type type;
        Color color;
        Chessboard* chessBoard;

        std::list<std::pair<int,int>> box_checked;

        int pos_i,pos_j;
    };

    class Pawn : public Piece {
    public:
        Pawn(int i, int j, Color color,Chessboard* chessboard);

        void findMovement();
    };

    class Knight : public Piece {
    public:
        Knight(int i, int j,Chess::Color color,Chessboard* chessboard);

        void findMovement();

    };

    class Tower : public Piece {
    public:
        Tower(int i, int j,Chess::Color color,Chessboard* chessboard);
        void findMovement();
    };

    class Bishop : public Piece {
    public:
        Bishop(int i, int j,Chess::Color color,Chessboard* chessboard);
        void findMovement();
    };

    class King : public Piece
    {
    public:
        King(int i, int j,Chess::Color color,Chessboard* chessboard);
        void findMovement();
    };

    class Queen : public Piece
    {
    public:
        Queen(int i, int j,Chess::Color color,Chessboard* chessboard);
        void findMovement();
    };
}

#endif //CHESS_CHESS_H
