//
// Created by dgall on 11/05/2019.
//

#ifndef CHESS_CHESSITEMS_H
#define CHESS_CHESSITEMS_H

#include <SFML/Graphics.hpp>

#define CHESSBOARD_SIZE 512
#define BOX_SIZE 64

#define WINDOW_WIDHT 1000
#define WINDOW_HEIGHT 612

#define CHESSBOARD_ORIGIN_X WINDOW_WIDHT/2 - CHESSBOARD_SIZE/2
#define CHESSBOARD_ORIGIN_Y WINDOW_HEIGHT/2 - CHESSBOARD_SIZE/2

namespace Chess{
    class Piece;
    class Horse;
    class ChessBoard;
    enum TYPE_PIECE{
        TOWER,
        HORSE,
        BISHOP,
        QUEEN,
        KING,
        PAWN
    };
    enum COLOR_PIECE{
        BLACK,
        WHITE
    };
}

class Chess::Piece{

public:
    Piece(sf::Texture texture, int pos_i, int pos_j, Chess::TYPE_PIECE type_piece,
          Chess::ChessBoard* chessBoard,Chess::COLOR_PIECE);
    void draw(sf::RenderWindow* window);
    void update(const sf::RenderWindow &window);
    void move(float x, float y);
    bool checkMove(int new_pos_i, int new_pos_j);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    Chess::TYPE_PIECE type_piece;
    Chess::COLOR_PIECE color_piece;
    Chess::ChessBoard* chessBoard;

    int chessboard_pos_i, chessboard_pos_j;

    bool checkBishop(int new_pos_i, int new_pos_j);

    bool checkTower(int new_pos_i, int new_pos_j);
};

class Chess::ChessBoard{

public:
    ChessBoard();
    void update(const sf::RenderWindow &window);
    void draw(sf::RenderWindow *pWindow);
    Chess::Piece* getPiece(int i, int j);

private:
    Piece* board[8][8];
    int selected_i,selected_j;
    bool selected = false;
};


#endif //CHESS_CHESSITEMS_H
