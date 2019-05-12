//
// Created by dgall on 11/05/2019.
//

#include <iostream>
#include "ChessItems.h"

// CHESS::PIECE CLASS
Chess::Piece::Piece(sf::Texture texture, int pos_x, int pos_y, Chess::TYPE_PIECE type_piece,
                    Chess::ChessBoard* chessBoard, Chess::COLOR_PIECE color_piece) {
    this->texture = texture;
    this->type_piece = type_piece;
    this->chessboard_pos_i = pos_x;
    this->chessboard_pos_j = pos_y;
    this->color_piece = color_piece;
    sprite.setTexture(this->texture);
    sprite.setPosition((pos_x * BOX_SIZE) + CHESSBOARD_ORIGIN_X ,(pos_y * BOX_SIZE) + CHESSBOARD_ORIGIN_Y);
    sprite.scale(0.35,0.35);
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
            if(new_pos_i == chessboard_pos_i + 1) return true;
            if(chessboard_pos_i ==  6 && new_pos_i == chessboard_pos_i + 2) return true;
            break;
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

    sf::Texture pawn_texture;
    pawn_texture.loadFromFile("../horse.png");

    selected_i = 1;
    selected_j = 1;
    selected = false;
    for(int i = 0; i < 8 ; i++){
        for(int j=0; j < 8; j++)
            board[i][j] = new Piece(pawn_texture,j,i,Chess::TYPE_PIECE::PAWN,this,BLACK);
    }

    board[3][6] = NULL;
}


void Chess::ChessBoard::update(const sf::RenderWindow &window) {

    if( sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !selected
        && sf::Mouse::getPosition(window).x >= CHESSBOARD_ORIGIN_X
        && sf::Mouse::getPosition(window).x <= CHESSBOARD_ORIGIN_X + CHESSBOARD_SIZE
        && sf::Mouse::getPosition(window).y >= CHESSBOARD_ORIGIN_Y
        && sf::Mouse::getPosition(window).y <= CHESSBOARD_ORIGIN_Y + CHESSBOARD_SIZE){
        selected_i =(int) ( CHESSBOARD_ORIGIN_Y - sf::Mouse::getPosition(window).y ) / BOX_SIZE * (-1);
        selected_j =(int) ( CHESSBOARD_ORIGIN_X - sf::Mouse::getPosition(window).x ) / BOX_SIZE * (-1);
        selected = true;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selected){
        board[selected_i][selected_j]->update(window);
    }
    else{
        if(selected){

            int now_i =(int) ( CHESSBOARD_ORIGIN_Y - sf::Mouse::getPosition(window).y ) / BOX_SIZE * (-1);
            int now_j =(int) ( CHESSBOARD_ORIGIN_X - sf::Mouse::getPosition(window).x ) / BOX_SIZE * (-1); ;
            if(board[now_i][now_j] == NULL){
                Piece* tmp = board[selected_i][selected_j];
                board[selected_i][selected_j] = NULL;
                tmp->move( (now_j * BOX_SIZE) + CHESSBOARD_ORIGIN_X , (now_i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y );
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
