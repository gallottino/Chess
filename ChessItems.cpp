//
// Created by dgall on 11/05/2019.
//

#include <iostream>
#include "ChessItems.h"

// CHESS::PIECE CLASS
Chess::Piece::Piece(sf::Texture texture, int pos_i, int pos_j, Chess::TYPE_PIECE type_piece,
                    Chess::ChessBoard* chessBoard, Chess::COLOR_PIECE color_piece) {
    this->texture = texture;
    this->type_piece = type_piece;
    this->chessboard_pos_i = pos_i;
    this->chessboard_pos_j = pos_j;
    this->color_piece = color_piece;
    sprite.setTexture(this->texture);
    sprite.setPosition((pos_j * BOX_SIZE) + CHESSBOARD_ORIGIN_X ,(pos_i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y);
    this->chessBoard = chessBoard;
}

void Chess::Piece::draw(sf::RenderWindow* window)
    {window->draw(sprite);}

void Chess::Piece::update(const sf::RenderWindow &window)
{
        //std::cout << this->chessboard_pos_y<< " and "<< this->chessboard_pos_x << std::endl;
        sprite.setPosition(sf::Mouse::getPosition(window).x - (sprite.getTextureRect().width/2 * sprite.getScale().x)
                ,sf::Mouse::getPosition(window).y - (sprite.getTextureRect().height/2 * sprite.getScale().x));
}

bool Chess::Piece::checkMove(int new_pos_i, int new_pos_j)
{
    switch(type_piece){

        case PAWN:
            if(color_piece == Chess::COLOR_PIECE::WHITE) {
                if (new_pos_i == chessboard_pos_i - 1
                    && ( new_pos_j == chessboard_pos_j - 1
                        || new_pos_j == chessboard_pos_j + 1)
                    && chessBoard->getPiece(new_pos_i,new_pos_j) != NULL) return true;

                if (new_pos_i == chessboard_pos_i - 1
                        && new_pos_j == chessboard_pos_j) return true;

                if (chessboard_pos_i == 6
                        && new_pos_i == chessboard_pos_i - 2
                        && new_pos_j == chessboard_pos_j) return true;
            }
            else{
                if (new_pos_i == chessboard_pos_i + 1) return true;

                if (new_pos_i == chessboard_pos_i + 1
                    && ( new_pos_j == chessboard_pos_j - 1
                        || new_pos_j == chessboard_pos_j + 1)
                    && chessBoard->getPiece(new_pos_i,new_pos_j ) != NULL) return true;

                if (chessboard_pos_i == 1
                    && new_pos_i == chessboard_pos_i + 2) return true;
            }
            break;

            //TODO: ADD KING, QUEEN, TOWER, HORSE, BISHOP
    }

    return false;
}

Chess::TYPE_PIECE Chess::Piece::getTypePiece(){
    return type_piece;
}

void Chess::Piece::move(float x, float y)
{
    this->chessboard_pos_i =  ( CHESSBOARD_ORIGIN_Y - y ) / BOX_SIZE * (-1);
    this->chessboard_pos_j =  ( CHESSBOARD_ORIGIN_X - x ) / BOX_SIZE * (-1);
    this->sprite.setPosition(x,y);
}

// CHESS::CHESSBOARD CLASS

Chess::ChessBoard::ChessBoard() {

    sf::Texture tower_black;
    sf::Texture tower_white;
    sf::Texture horse_black;
    sf::Texture horse_white;

    tower_black.loadFromFile("../images/torre_black.png");
    tower_white.loadFromFile("../images/torre.png");
    horse_black.loadFromFile("../images/horse_black.png");
    horse_white.loadFromFile("../images/horse_white.png");

    selected_i = 1;
    selected_j = 1;
    selected = false;

    for(int i = 0; i < 8 ; i++){
        for(int j=0; j < 8; j++)
            board[i][j] = NULL;
    }

    for(int i = 0 ; i< 8 ; i++)
        board[1][i] = new Piece(tower_black,1,i,Chess::TYPE_PIECE::PAWN,this,BLACK);

    board[0][1] = new Piece(horse_black,0,1,Chess::TYPE_PIECE::HORSE,this,BLACK);
    board[0][6] = new Piece(horse_black,0,6,Chess::TYPE_PIECE::HORSE,this,BLACK);
    board[7][1] = new Piece(horse_white,7,1,Chess::TYPE_PIECE::HORSE,this,WHITE);
    board[7][6] = new Piece(horse_white,7,6,Chess::TYPE_PIECE::HORSE,this,WHITE);

    for(int i = 0 ; i< 8 ; i++)
        board[6][i] = new Piece(tower_white,6,i,Chess::TYPE_PIECE::PAWN,this,WHITE);

}

Chess::Piece* Chess::ChessBoard::getPiece(int i, int j){ return board[i][j];}

void Chess::ChessBoard::update(const sf::RenderWindow &window) {

    if( sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !selected
        && sf::Mouse::getPosition(window).x >= CHESSBOARD_ORIGIN_X
        && sf::Mouse::getPosition(window).x <= CHESSBOARD_ORIGIN_X + CHESSBOARD_SIZE
        && sf::Mouse::getPosition(window).y >= CHESSBOARD_ORIGIN_Y
        && sf::Mouse::getPosition(window).y <= CHESSBOARD_ORIGIN_Y + CHESSBOARD_SIZE){
        selected_i =(int) ( CHESSBOARD_ORIGIN_Y - sf::Mouse::getPosition(window).y ) / BOX_SIZE * (-1);
        selected_j =(int) ( CHESSBOARD_ORIGIN_X - sf::Mouse::getPosition(window).x ) / BOX_SIZE * (-1);
        if(board[selected_i][selected_j] != NULL)
            selected = true;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selected){
        board[selected_i][selected_j]->update(window);
    }
    else{
        if(selected){
            int now_i =(int) ( CHESSBOARD_ORIGIN_Y - sf::Mouse::getPosition(window).y ) / BOX_SIZE * (-1);
            int now_j =(int) ( CHESSBOARD_ORIGIN_X - sf::Mouse::getPosition(window).x ) / BOX_SIZE * (-1); ;
            if(board[selected_i][selected_j]->checkMove(now_i,now_j)){
                Piece* tmp = board[selected_i][selected_j];
                board[selected_i][selected_j] = NULL;
                tmp->move( (now_j * BOX_SIZE) + CHESSBOARD_ORIGIN_X , (now_i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y );
                if(board[now_i][now_j] != NULL){
                    delete(board[now_i][now_j]);
                }
                board[now_i][now_j] = tmp;

            }
            else{
                board[selected_i][selected_j]->move((selected_j * BOX_SIZE) + CHESSBOARD_ORIGIN_X ,
                        (selected_i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y );
            }

        }
        selected = false;
    }
}

void Chess::ChessBoard::draw(sf::RenderWindow *pWindow) {

    for(int i=0; i < 8 ; i++){
        for(int j=0; j<8; j++){
            if(board[i][j]!= NULL)
                board[i][j]->draw(pWindow);
        }
    }
}
