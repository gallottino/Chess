//
// Created by dgall on 11/05/2019.
//

#include <iostream>
#include "../include/ChessItems.h"

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
        sprite.setPosition(sf::Mouse::getPosition(window).x - (sprite.getTextureRect().width/2 * sprite.getScale().x)
                ,sf::Mouse::getPosition(window).y - (sprite.getTextureRect().height/2 * sprite.getScale().x));
}

void Chess::Piece::findMovement()
{
    int i,j;
    box_checked.clear();
    switch(type_piece){
        case PAWN:
            if(color_piece == WHITE){
                if(chessBoard->getPiece(chessboard_pos_i - 1 ,chessboard_pos_j) == NULL)
                    box_checked.push_back(std::pair<int,int>(chessboard_pos_i - 1 ,chessboard_pos_j));
                if(chessBoard->getPiece(chessboard_pos_i - 2 ,chessboard_pos_j) == NULL
                        && chessboard_pos_i == 6)
                    box_checked.push_back(std::pair<int,int>(chessboard_pos_i - 2,chessboard_pos_j));
                if(chessBoard->getPiece(chessboard_pos_i - 1 ,chessboard_pos_j - 1) != NULL
                && chessBoard->getPiece(chessboard_pos_i - 1 ,chessboard_pos_j - 1)->getColor() != color_piece)
                    box_checked.push_back(std::pair<int,int>(chessboard_pos_i - 1 ,chessboard_pos_j - 1));
                if(chessBoard->getPiece(chessboard_pos_i - 1 ,chessboard_pos_j + 1) != NULL
                && chessBoard->getPiece(chessboard_pos_i - 1 ,chessboard_pos_j + 1)->getColor() != color_piece)
                    box_checked.push_back(std::pair<int,int>(chessboard_pos_i - 1 ,chessboard_pos_j + 1));
            }
            else{
                if(chessBoard->getPiece(chessboard_pos_i + 1 ,chessboard_pos_j) == NULL)
                    box_checked.push_back(std::pair<int,int>(chessboard_pos_i + 1 ,chessboard_pos_j));
                if(chessBoard->getPiece(chessboard_pos_i + 2 ,chessboard_pos_j) == NULL
                        && chessboard_pos_i == 1)
                    box_checked.push_back(std::pair<int,int>(chessboard_pos_i + 2,chessboard_pos_j));
                if(chessBoard->getPiece(chessboard_pos_i + 1 ,chessboard_pos_j + 1) != NULL
                && chessBoard->getPiece(chessboard_pos_i + 1 ,chessboard_pos_j + 1)->getColor() != color_piece)
                    box_checked.push_back(std::pair<int,int>(chessboard_pos_i + 1 ,chessboard_pos_j + 1));
                if(chessBoard->getPiece(chessboard_pos_i + 1 ,chessboard_pos_j - 1) != NULL
                && chessBoard->getPiece(chessboard_pos_i + 1 ,chessboard_pos_j - 1)->getColor() != color_piece)
                    box_checked.push_back(std::pair<int,int>(chessboard_pos_i + 1 ,chessboard_pos_j - 1));

            }
            break;

        case HORSE:
            i = chessboard_pos_i-2;
            j = chessboard_pos_j+1;
            if(((i>=0 && j<=7)) && (chessBoard->getPiece(i,j)==NULL
                ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color_piece)))
                box_checked.push_back(std::pair<int,int>(i,j));

            i = chessboard_pos_i-2;
            j = chessboard_pos_j-1;
            if((i>=0 && j>=0) && (chessBoard->getPiece(i,j)==NULL
                ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color_piece)))
                box_checked.push_back(std::pair<int,int>(i,j));

            i = chessboard_pos_i-1;
            j = chessboard_pos_j+2;
            if((i>=0 && j<=7) && (chessBoard->getPiece(i,j)==NULL
                ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color_piece)))
                box_checked.push_back(std::pair<int,int>(i,j));

            i = chessboard_pos_i-1;
            j = chessboard_pos_j-2;
            if((i>=0 && j>=0) && (chessBoard->getPiece(i,j)==NULL
                ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color_piece)))
                box_checked.push_back(std::pair<int,int>(i,j));

            i = chessboard_pos_i+2;
            j = chessboard_pos_j+1;
            if(i<=7 && j<=7 && (chessBoard->getPiece(i,j)==NULL
                ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color_piece)))
                box_checked.push_back(std::pair<int,int>(i,j));

            i = chessboard_pos_i+2;
            j = chessboard_pos_j-1;
            if((i<=7 && j>=0) && (chessBoard->getPiece(i,j)==NULL
                ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color_piece)))
                box_checked.push_back(std::pair<int,int>(i,j));

            i = chessboard_pos_i+1;
            j = chessboard_pos_j+2;
            if((i<=7 && j<=7) && (chessBoard->getPiece(i,j)==NULL
                ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color_piece)))
                box_checked.push_back(std::pair<int,int>(i,j));

            i = chessboard_pos_i+1;
            j = chessboard_pos_j-2;
            if((i<=7 && j>=0) && (chessBoard->getPiece(i,j)==NULL
                ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color_piece)))
                box_checked.push_back(std::pair<int,int>(i,j));
            break;

        case BISHOP:
            j = chessboard_pos_j;
            for(int i=chessboard_pos_i-1;i>=0; i--){
                j--;
                if(chessBoard->getPiece(i,j) != NULL){
                    if(chessBoard->getPiece(i,j)->getColor() == color_piece)
                        break;
                    box_checked.push_back(std::pair<int,int>(i,j));
                    break;
                }
                box_checked.push_back(std::pair<int,int>(i,j));
            }
            j = chessboard_pos_j;
            for(int i=chessboard_pos_i+1;i<=7; i++){
                j++;
                if(chessBoard->getPiece(i,j) != NULL){
                    if(chessBoard->getPiece(i,j)->getColor() == color_piece)
                        break;
                    box_checked.push_back(std::pair<int,int>(i,j));
                    break;
                }
                box_checked.push_back(std::pair<int,int>(i,j));

            }
            j = chessboard_pos_j;
            for(int i=chessboard_pos_i-1;i>=0; i--){
                j++;
                if(chessBoard->getPiece(i,j) != NULL){
                    if(chessBoard->getPiece(i,j)->getColor() == color_piece)
                        break;
                    box_checked.push_back(std::pair<int,int>(i,j));
                    break;
                }
                box_checked.push_back(std::pair<int,int>(i,j));

            }
            j = chessboard_pos_j;
            for(int i=chessboard_pos_i+1;i<=7; i++){
                j--;
                if(chessBoard->getPiece(i,j) != NULL){
                    if(chessBoard->getPiece(i,j)->getColor() == color_piece)
                        break;
                    box_checked.push_back(std::pair<int,int>(i,j));
                    break;
                }
                box_checked.push_back(std::pair<int,int>(i,j));
            }
            break;

        case TOWER:
            j = chessboard_pos_j;
            for(int i=chessboard_pos_i-1;i>=0; i--){
                if(chessBoard->getPiece(i,j) != NULL){
                    if(chessBoard->getPiece(i,j)->getColor() == color_piece)
                        break;
                    box_checked.push_back(std::pair<int,int>(i,j));
                    break;
                }
                box_checked.push_back(std::pair<int,int>(i,j));
            }
            j = chessboard_pos_j;
            for(int i=chessboard_pos_i+1;i<=7; i++){
                if(chessBoard->getPiece(i,j) != NULL){
                    if(chessBoard->getPiece(i,j)->getColor() == color_piece)
                        break;
                    box_checked.push_back(std::pair<int,int>(i,j));
                    break;
                }
                box_checked.push_back(std::pair<int,int>(i,j));
            }
            i = chessboard_pos_i;
            for(int j=chessboard_pos_j-1;j>=0; j--){
                if(chessBoard->getPiece(i,j) != NULL){
                    if(chessBoard->getPiece(i,j)->getColor() == color_piece)
                        break;
                    box_checked.push_back(std::pair<int,int>(i,j));
                    break;
                }
                box_checked.push_back(std::pair<int,int>(i,j));
            }
            i = chessboard_pos_i;
            for(int j=chessboard_pos_j+1;j<=7; j++){
                if(chessBoard->getPiece(i,j) != NULL){
                    if(chessBoard->getPiece(i,j)->getColor() == color_piece)
                        break;
                    box_checked.push_back(std::pair<int,int>(i,j));
                    break;
                }
                box_checked.push_back(std::pair<int,int>(i,j));
            }

            break;
    }
}

bool Chess::Piece::checkMove(int new_pos_i, int new_pos_j)
{
    Chess::ChessBoard tmp = *chessBoard;
    if(chessBoard->getPiece(new_pos_i,new_pos_j) != NULL)
        if (chessBoard->getPiece(new_pos_i,new_pos_j)->getColor() == this->getColor())
            return false;

    switch(type_piece){
        case PAWN:
            return checkPawn(new_pos_i,new_pos_j);

        case HORSE:
            return checkHorse(new_pos_i,new_pos_j);

        case BISHOP:
            return checkBishop(new_pos_i,new_pos_j);

        case TOWER:
            return checkTower(new_pos_i,new_pos_j);

        case KING:
            if( abs(new_pos_i - chessboard_pos_i) <= 1
                && abs(new_pos_j - chessboard_pos_j) <=1) return true;
            return  false;

        case QUEEN:
            // Tower moving
            if((new_pos_i == chessboard_pos_i && new_pos_j != chessboard_pos_j)
                || (new_pos_i != chessboard_pos_i && new_pos_j == chessboard_pos_j)){
                return checkTower(new_pos_i, new_pos_j);
            }
            // Bishop moving
            if( abs(chessboard_pos_i - new_pos_i) == abs(chessboard_pos_j - new_pos_j) )
                return checkBishop(new_pos_i,new_pos_j);

            return false;
    }
    return false;
}

bool Chess::Piece::checkHorse(int new_pos_i,int new_pos_j)
{
    if(new_pos_i == chessboard_pos_i + 2
       && (new_pos_j == chessboard_pos_j - 1
           || new_pos_j == chessboard_pos_j + 1)) return true;

    if(new_pos_i == chessboard_pos_i - 2
       && (new_pos_j == chessboard_pos_j - 1
           || new_pos_j == chessboard_pos_j + 1)) return true;

    if(new_pos_i == chessboard_pos_i + 1
       && (new_pos_j == chessboard_pos_j - 2
           || new_pos_j == chessboard_pos_j + 2 )) return true;

    if(new_pos_i == chessboard_pos_i - 1
       && (new_pos_j == chessboard_pos_j - 2
           || new_pos_j == chessboard_pos_j + 2 )) return true;

    return false;
}

bool Chess::Piece::checkPawn(int new_pos_i, int new_pos_j)
{
    if (color_piece == Chess::COLOR_PIECE::WHITE) {
        if (new_pos_i == chessboard_pos_i - 1
            && (new_pos_j == chessboard_pos_j - 1
                || new_pos_j == chessboard_pos_j + 1)
            && chessBoard->getPiece(new_pos_i, new_pos_j) != NULL)
            return true;

        if (new_pos_i == chessboard_pos_i - 1
            && new_pos_j == chessboard_pos_j
            && chessBoard->getPiece(new_pos_i, new_pos_j) == NULL)
            return true;

        if (chessboard_pos_i == 6
            && new_pos_i == chessboard_pos_i - 2
            && new_pos_j == chessboard_pos_j
            && chessBoard->getPiece(new_pos_i, new_pos_j) == NULL)
            return true;
    } else {
        if (new_pos_i == chessboard_pos_i + 1
            && (new_pos_j == chessboard_pos_j - 1
                || new_pos_j == chessboard_pos_j + 1)
            && chessBoard->getPiece(new_pos_i, new_pos_j) != NULL)
            return true;

        if (new_pos_i == chessboard_pos_i + 1
            && new_pos_j == chessboard_pos_j
            && chessBoard->getPiece(new_pos_i, new_pos_j) == NULL)
            return true;

        if (chessboard_pos_i == 1
            && new_pos_i == chessboard_pos_i + 2
            && new_pos_j == chessboard_pos_j
            && chessBoard->getPiece(new_pos_i, new_pos_j) == NULL)
            return true;
    }
    return false;
}

bool Chess::Piece::checkBishop(int new_pos_i, int new_pos_j)
{
    if( abs(chessboard_pos_i - new_pos_i) == abs(chessboard_pos_j - new_pos_j) ) {
        int j = chessboard_pos_j;
        if (new_pos_i > chessboard_pos_i) {
            if (new_pos_j > chessboard_pos_j) {
                for( int i = chessboard_pos_i + 1; i < new_pos_i ; i++) {
                    j++;
                    if (chessBoard->getPiece(i,j) != NULL) return false;
                }
            }
            else{
                for( int i = chessboard_pos_i + 1; i < new_pos_i; i++){
                    j--;
                    if(chessBoard->getPiece(i,j) != NULL) return false;
                }
            }
        }else {
            if (new_pos_j > chessboard_pos_j) {
                for( int i = chessboard_pos_i - 1; i > new_pos_i; i--){
                    j++;
                    if(chessBoard->getPiece(i,j) != NULL) return false;
                }
            } else {
                for( int i = chessboard_pos_i - 1; i > new_pos_i; i--){
                    j--;
                    if(chessBoard->getPiece(i,j) != NULL) return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool Chess::Piece::checkTower(int new_pos_i, int new_pos_j){
    int change = 1;
    if(new_pos_i == chessboard_pos_i && new_pos_j != chessboard_pos_j){
        if(new_pos_j < chessboard_pos_j) change = -1;
        for(int j = chessboard_pos_j + change; j * change < new_pos_j * change;j+=change)
            if(chessBoard->getPiece(chessboard_pos_i,j)!= NULL) return false;

        return true;
    }
    else if(new_pos_i != chessboard_pos_i && new_pos_j == chessboard_pos_j){
        if(new_pos_i < chessboard_pos_i) change = - 1;
        for(int i = chessboard_pos_i + change; i * change < new_pos_i * change;i+=change)
            if(chessBoard->getPiece(i,chessboard_pos_j)!= NULL) return false;

        return true;
    }
    return false;
}

void Chess::Piece::move(float x, float y)
{
    this->chessboard_pos_i =  ( CHESSBOARD_ORIGIN_Y - y ) / BOX_SIZE * (-1);
    this->chessboard_pos_j =  ( CHESSBOARD_ORIGIN_X - x ) / BOX_SIZE * (-1);
    this->sprite.setPosition(x,y);
}

// CHESS::CHESSBOARD CLASS

Chess::ChessBoard::ChessBoard() {

    sf::Texture asset;
    sf::Texture tower_black;
    sf::Texture tower_white;
    sf::Texture horse_black;
    sf::Texture horse_white;
    sf::Texture pawn_white;
    sf::Texture pawn_black;
    sf::Texture bishop_white;
    sf::Texture bishop_black;
    sf::Texture king_white;
    sf::Texture king_black;
    sf::Texture queen_white;
    sf::Texture queen_black;

    std::string path_black = "../images/chess_asset.png";
    std::string path_white = "../images/chess_asset_white.png";

    tower_black.loadFromFile(path_black,sf::IntRect(3 * BOX_SIZE, 1 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    tower_white.loadFromFile(path_white,sf::IntRect(3 * BOX_SIZE, 1 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    horse_black.loadFromFile(path_black,sf::IntRect(2 * BOX_SIZE, 1 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    horse_white.loadFromFile(path_white,sf::IntRect(2 * BOX_SIZE, 1 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    pawn_black.loadFromFile(path_black,sf::IntRect(0 * BOX_SIZE, 1 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    pawn_white.loadFromFile(path_white,sf::IntRect(0 * BOX_SIZE, 1 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    bishop_black.loadFromFile(path_black,sf::IntRect(1 * BOX_SIZE, 1 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    bishop_white.loadFromFile(path_white,sf::IntRect(1 * BOX_SIZE, 1 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    king_white.loadFromFile(path_white,sf::IntRect(2 * BOX_SIZE, 0 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    king_black.loadFromFile(path_black,sf::IntRect(2 * BOX_SIZE, 0 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    queen_white.loadFromFile(path_white,sf::IntRect(3 * BOX_SIZE, 0 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    queen_black.loadFromFile(path_black,sf::IntRect(3 * BOX_SIZE, 0 * BOX_SIZE, BOX_SIZE, BOX_SIZE));


    box_texture_black.loadFromFile(path_black,sf::IntRect(1 * BOX_SIZE, 0 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    box_texture_white.loadFromFile(path_black,sf::IntRect(0 * BOX_SIZE, 0 * BOX_SIZE, BOX_SIZE, BOX_SIZE));
    selected_texture.loadFromFile("../images/selector.png");
    selected_icon.setTexture(selected_texture);
    selected_icon.scale(2,2);

    selected_i = 1;
    selected_j = 1;
    selected = false;
    turn = WHITE;

    for(int i = 0; i < 8 ; i++){
        for(int j=0; j < 8; j++) {
            chessboard_sprite[i][j].setPosition(j*BOX_SIZE + CHESSBOARD_ORIGIN_X,i*BOX_SIZE + CHESSBOARD_ORIGIN_Y);
            if(i % 2 == 0)
                if (j % 2 == 0)
                    chessboard_sprite[i][j].setTexture(box_texture_white);
                else
                    chessboard_sprite[i][j].setTexture(box_texture_black);
            else
                if (j % 2 != 0)
                    chessboard_sprite[i][j].setTexture(box_texture_white);
                else
                    chessboard_sprite[i][j].setTexture(box_texture_black);

        }
    }

    // Init blank chessboard
    for(int i = 0; i < 8 ; i++){
        for(int j=0; j < 8; j++)
            board[i][j] = NULL;
    }

    //Init black pieces
    for(int i = 0 ; i< 8 ; i++)
        board[1][i] = new Piece(pawn_black,1,i,PAWN,this,BLACK);
    board[0][0] = new Piece(tower_black,0,0,TOWER,this,BLACK);
    board[0][7] = new Piece(tower_black,0,7,TOWER,this,BLACK);
    board[0][1] = new Piece(horse_black,0,1,HORSE,this,BLACK);
    board[0][6] = new Piece(horse_black,0,6,HORSE,this,BLACK);
    board[0][5] = new Piece(bishop_black,0,5,BISHOP,this,BLACK);
    board[0][2] = new Piece(bishop_black,0,2,BISHOP,this,BLACK);
    board[0][3] = new Piece(king_black,0,3,KING,this,BLACK);
    board[0][4] = new Piece(queen_black,0,4,QUEEN,this,BLACK);

    // Init white pieces
    for(int i = 0 ; i< 8 ; i++)
        board[6][i] = new Piece(pawn_white,6,i,PAWN,this,WHITE);
    board[7][0] = new Piece(tower_white,7,0,TOWER,this,WHITE);
    board[7][7] = new Piece(tower_white,7,7,TOWER,this,WHITE);
    board[7][1] = new Piece(horse_white,7,1,HORSE,this,WHITE);
    board[7][6] = new Piece(horse_white,7,6,HORSE,this,WHITE);
    board[7][5] = new Piece(bishop_white,7,5,BISHOP,this,WHITE);
    board[7][2] = new Piece(bishop_white,7,2,BISHOP,this,WHITE);
    board[7][3] = new Piece(king_white,7,3,KING,this,WHITE);
    board[7][4] = new Piece(queen_white,7,4,QUEEN,this,WHITE);

}

Chess::Piece* Chess::ChessBoard::getPiece(int i, int j){ return board[i][j];}

void Chess::ChessBoard::update(const sf::RenderWindow &window) {



    if( sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !selected
        && sf::Mouse::getPosition(window).x >= CHESSBOARD_ORIGIN_X
        && sf::Mouse::getPosition(window).x <= CHESSBOARD_ORIGIN_X + CHESSBOARD_SIZE
        && sf::Mouse::getPosition(window).y >= CHESSBOARD_ORIGIN_Y
        && sf::Mouse::getPosition(window).y <= CHESSBOARD_ORIGIN_Y + CHESSBOARD_SIZE){
        selected_i = (int) ( CHESSBOARD_ORIGIN_Y - sf::Mouse::getPosition(window).y ) / BOX_SIZE * (-1);
        selected_j = (int) ( CHESSBOARD_ORIGIN_X - sf::Mouse::getPosition(window).x ) / BOX_SIZE * (-1);
        if(board[selected_i][selected_j] != NULL
            && board[selected_i][selected_j]->getColor() == turn) {
            selected = true;
            board[selected_i][selected_j]->findMovement();
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selected){
        board[selected_i][selected_j]->update(window);
    }
    else{
        if(selected){
            int now_i =(int) ( CHESSBOARD_ORIGIN_Y - sf::Mouse::getPosition(window).y ) / BOX_SIZE * (-1);
            int now_j =(int) ( CHESSBOARD_ORIGIN_X - sf::Mouse::getPosition(window).x ) / BOX_SIZE * (-1);

            if(board[selected_i][selected_j]->checkMove(now_i,now_j)){

                if(board[now_i][now_j] != NULL) {


                    if (board[now_i][now_j]->getColor() != board[selected_i][selected_j]->getColor()) {
                        board[selected_i][selected_j]->move((now_j * BOX_SIZE) + CHESSBOARD_ORIGIN_X,
                                (now_i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y);
                        animation.setPosition(now_i,now_j);
                        delete(board[now_i][now_j]);
                        board[now_i][now_j] = board[selected_i][selected_j];
                        board[selected_i][selected_j] = NULL;
                        if(turn == WHITE) turn = BLACK;
                        else turn = WHITE;
                    } else {
                        board[selected_i][selected_j]->move((selected_j * BOX_SIZE) + CHESSBOARD_ORIGIN_X ,
                                                            (selected_i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y );
                        animation.setPosition(selected_i,selected_j);
                    }
                }
                else{
                    board[selected_i][selected_j]->move((now_j * BOX_SIZE) + CHESSBOARD_ORIGIN_X,
                            (now_i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y);
                    board[now_i][now_j] = board[selected_i][selected_j];
                    animation.setPosition(now_i,now_j);
                    board[selected_i][selected_j] = NULL;
                    if(turn == WHITE) turn = BLACK;
                    else turn = WHITE;
                }
            }
            else{
                board[selected_i][selected_j]->move((selected_j * BOX_SIZE) + CHESSBOARD_ORIGIN_X ,
                          (selected_i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y );
                animation.setPosition(selected_i,selected_j);
            }
            animation.startAnimation();
        }
        selected = false;
    }

    animation.update();

}

void Chess::ChessBoard::draw(sf::RenderWindow *pWindow) {



    for(int i=0; i < 8 ; i++){
        for(int j=0; j<8; j++){
            pWindow->draw(chessboard_sprite[i][j]);
            if(board[i][j]!= NULL)
                board[i][j]->draw(pWindow);
        }
    }

    if(selected)
        for(std::pair<int,int> p : board[selected_i][selected_j]->getMovement()){
            if(p.first >= 0 && p.first <=7 && p.second >= 0 && p.second <=7) {
                selected_icon.setPosition(p.second * BOX_SIZE + CHESSBOARD_ORIGIN_X,
                                          p.first * BOX_SIZE + CHESSBOARD_ORIGIN_Y);
                pWindow->draw(selected_icon);
            }
        }

    if(board[selected_i][selected_j] != NULL)
        board[selected_i][selected_j]->draw(pWindow);

    animation.draw(pWindow);
}
