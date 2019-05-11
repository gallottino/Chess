//
// Created by dgall on 11/05/2019.
//

#include <iostream>
#include "ChessItems.h"

// CHESS::PIECE CLASS
Chess::Piece::Piece(sf::Texture texture,int pos_x, int pos_y,Chess::TYPE_PIECE type_piece)
{
    this->texture = texture;
    this->type_piece = type_piece;
    this->chessboard_pos_x = (pos_x - CHESSBOARD_ORIGIN_X)/ BOX_SIZE;
    this->chessboard_pos_y = (pos_y - CHESSBOARD_ORIGIN_Y)/ BOX_SIZE;


    sprite.setTexture(this->texture);
    sprite.setPosition(pos_x,pos_y);
    sprite.scale(0.35,0.35 );
}

void Chess::Piece::draw(sf::RenderWindow* window)
    {window->draw(sprite);}

void Chess::Piece::update(const sf::RenderWindow &window)
{
    // TODO: Change get Scale
    if( sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
        && sf::Mouse::getPosition(window).x >= sprite.getPosition().x
        && sf::Mouse::getPosition(window).x <= sprite.getPosition().x + sprite.getTextureRect().width * sprite.getScale().x
        && sf::Mouse::getPosition(window).y >= sprite.getPosition().y
        && sf::Mouse::getPosition(window).y <= sprite.getPosition().y + sprite.getTextureRect().height * sprite.getScale().x
        ){
        std::cout << this->chessboard_pos_y<< " and "<< this->chessboard_pos_x << std::endl;
        sprite.setPosition(sf::Mouse::getPosition(window).x - (sprite.getTextureRect().width/2 * sprite.getScale().x)
                ,sf::Mouse::getPosition(window).y - (sprite.getTextureRect().height/2 * sprite.getScale().x));
    }
}

bool Chess::Piece::checkMove(int new_pos_x, int new_pos_y)
{

}

Chess::TYPE_PIECE Chess::Piece::getTypePiece() const {
    return type_piece;
}

int Chess::Piece::getChessboardPosX() const {
    return chessboard_pos_x;
}

int Chess::Piece::getChessboardPosY() const {
    return chessboard_pos_y;
}


// CHESS::CHESSBOARD CLASS






