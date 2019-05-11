//
// Created by dgall on 11/05/2019.
//

#ifndef CHESS_CHESSITEMS_H
#define CHESS_CHESSITEMS_H

#include <SFML/Graphics.hpp>

#define CHESSBOARD_SIZE 512
#define BOX_SIZE 32

#define WINDOW_WIDHT 1000
#define WINDOW_HEIGHT 612

#define CHESSBOARD_ORIGIN_X WINDOW_WIDHT/2 - CHESSBOARD_SIZE/2
#define CHESSBOARD_ORIGIN_Y WINDOW_HEIGHT/2 - CHESSBOARD_SIZE/2

namespace Chess{
    class Piece;
    class ChessBoard;
    enum TYPE_PIECE{
        TOWER,
        HORSE,
        BISHOP,
        QUEEN,
        KING,
        PAWN
    };
}

class Chess::Piece{

public:
    Piece(sf::Texture texture,int pos_x, int pos_y,Chess::TYPE_PIECE type_piece);
    void draw(sf::RenderWindow* window);
    void update(const sf::RenderWindow &window);

    TYPE_PIECE getTypePiece() const;

    int getChessboardPosX() const;

    int getChessboardPosY() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    Chess::TYPE_PIECE type_piece;
    int chessboard_pos_x, chessboard_pos_y;

    bool checkMove(int new_pos_x, int new_pos_y);
};

class Chess::ChessBoard{

public:

private:

};


#endif //CHESS_CHESSITEMS_H
