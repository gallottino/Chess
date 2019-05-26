//
// Created by dgall on 24/05/2019.
//
#include "Chess.h"

//CHESSBOARD
Chess::Chessboard::Chessboard()
{
    selected_texture.loadFromFile("../images/selector.png");
    black_box.loadFromFile("../images/chess_asset.png",sf::IntRect(BOX_SIZE,0,BOX_SIZE,BOX_SIZE));
    white_box.loadFromFile("../images/chess_asset.png",sf::IntRect(0,0,BOX_SIZE,BOX_SIZE));

    for(int i = 0; i < 8 ; i++){
        for(int j=0; j < 8; j++) {
            chessboard_sprite[i][j].setPosition(j*BOX_SIZE + CHESSBOARD_ORIGIN_X,i*BOX_SIZE + CHESSBOARD_ORIGIN_Y);
            if(i % 2 == 0)
                if (j % 2 == 0)
                    chessboard_sprite[i][j].setTexture(white_box);
                else
                    chessboard_sprite[i][j].setTexture(black_box);
            else
            if (j % 2 != 0)
                chessboard_sprite[i][j].setTexture(white_box);
            else
                chessboard_sprite[i][j].setTexture(black_box);
        }
    }

    for(int i = 0; i < 8 ; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard[i][j] = NULL;
        }
    }

    selected_icon.setTexture(selected_texture);
    selected_icon.scale(2,2);
    selected = false;

    turn = WHITE;
    // INIT CHESSBOARD BLACK
    for(int i=0;i<8;i++){
        chessboard[1][i] = new Pawn(1,i,BLACK,this);
    }
    chessboard[0][5] = new Bishop(0,5,BLACK,this);
    chessboard[0][6] = new Knight(0,6,BLACK,this);
    chessboard[0][7] = new Tower(0,7,BLACK,this);
    chessboard[0][4] = new Queen(0,4,BLACK,this);
    chessboard[0][3] = new King(0,3,BLACK,this);
    chessboard[0][2] = new Bishop(0,2,BLACK,this);
    chessboard[0][1] = new Knight(0,1,BLACK,this);
    chessboard[0][0] = new Tower(0,0,BLACK,this);


    // INIT CHESSBOARD WHITE
    for(int i=0;i<8;i++){
        chessboard[6][i] = new Pawn(6,i,WHITE,this);
    }
    chessboard[7][5] = new Bishop(7,5,WHITE,this);
    chessboard[7][6] = new Knight(7,6,WHITE,this);
    chessboard[7][7] = new Tower(7,7,WHITE,this);
    chessboard[7][4] = new Queen(7,4,WHITE,this);
    chessboard[7][3] = new King(7,3,WHITE,this);
    chessboard[7][2] = new Bishop(7,2,WHITE,this);
    chessboard[7][1] = new Knight(7,1,WHITE,this);
    chessboard[7][0] = new Tower(7,0,WHITE,this);

}

void Chess::Chessboard::render(sf::RenderWindow* window)
{
    for(int i = 0; i < 8 ; i++) {
        for (int j = 0; j < 8; j++) {
            window->draw(chessboard_sprite[i][j]);
        }
    }
    for(int i = 0; i < 8 ; i++) {
        for (int j = 0; j < 8; j++) {
            if(chessboard[i][j] != NULL)
            chessboard[i][j]->render(window);
        }
    }

    if(selected){
        for(std::pair<int,int> p : chessboard[selected_i][selected_j]->getMovements())
        {
            selected_icon.setPosition(p.second * BOX_SIZE + CHESSBOARD_ORIGIN_X,
                                      p.first * BOX_SIZE + CHESSBOARD_ORIGIN_Y);
            window->draw(selected_icon);
        }
        chessboard[selected_i][selected_j]->render(window);
    }
}
void Chess::Chessboard::update(const sf::RenderWindow &window)
{

    if( !selected && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
        && sf::Mouse::getPosition(window).x >= CHESSBOARD_ORIGIN_X
        && sf::Mouse::getPosition(window).x <= CHESSBOARD_ORIGIN_X + CHESSBOARD_SIZE
        && sf::Mouse::getPosition(window).y >= CHESSBOARD_ORIGIN_Y
        && sf::Mouse::getPosition(window).y <= CHESSBOARD_ORIGIN_Y + CHESSBOARD_SIZE){
        selected_i = (int) ( CHESSBOARD_ORIGIN_Y - sf::Mouse::getPosition(window).y ) / BOX_SIZE * (-1);
        selected_j = (int) ( CHESSBOARD_ORIGIN_X - sf::Mouse::getPosition(window).x ) / BOX_SIZE * (-1);
        if(chessboard[selected_i][selected_j] != NULL
           && chessboard[selected_i][selected_j]->getColor() == turn) {
            selected = true;
            chessboard[selected_i][selected_j]->findMovement();
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selected){
        chessboard[selected_i][selected_j]->update(window);
    }
    else if(selected){
        int now_i =(int) ( CHESSBOARD_ORIGIN_Y - sf::Mouse::getPosition(window).y ) / BOX_SIZE * (-1);
        int now_j =(int) ( CHESSBOARD_ORIGIN_X - sf::Mouse::getPosition(window).x ) / BOX_SIZE * (-1);
        if(chessboard[selected_i][selected_j]->checkMove(now_i,now_j)){
            // SPOSTATI
            chessboard[selected_i][selected_j]->move(now_i,now_j);
            if(chessboard[now_i][now_j] != NULL && now_i != selected_i) {
                delete (chessboard[now_i][now_j]);
            }
            chessboard[now_i][now_j] = chessboard[selected_i][selected_j];
            chessboard[selected_i][selected_j] = NULL;
            if(turn == WHITE) turn = BLACK;
            else turn = WHITE;
        }
        else{
            //TORNA AL TUO POSTO
            chessboard[selected_i][selected_j]->move(selected_i,selected_j);
        }
        selected = false;
    }
}


// ABSTRACT CLASS
Chess::Piece::Piece(int i, int j,Chess::Color color,Chessboard* chessboard)
{
    this->pos_i = i;
    this->pos_j = j;
    this->color = color;
    this->chessBoard = chessboard;
    sprite.setPosition((j * BOX_SIZE) + CHESSBOARD_ORIGIN_X ,(i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y);
}

Chess::Type Chess::Piece::getType(){return type;}

Chess::Color Chess::Piece::getColor(){return color;}

bool Chess::Piece::checkMove(int i,int j)
{
    for(std::pair<int,int> p : box_checked){
        if(p.first == i && p.second == j)
            return true;
    }

    return false;
}

void Chess::Piece::render(sf::RenderWindow *window){ window->draw(sprite); }

void Chess::Piece::update(const sf::RenderWindow &window)
{
    sprite.setPosition(sf::Mouse::getPosition(window).x - (sprite.getTextureRect().width/2 * sprite.getScale().x)
            ,sf::Mouse::getPosition(window).y - (sprite.getTextureRect().height/2 * sprite.getScale().x));
}

void Chess::Piece::move(int i,int j)
{
    this->pos_i = i;
    this->pos_j = j;
    sprite.setPosition((j * BOX_SIZE) + CHESSBOARD_ORIGIN_X ,(i * BOX_SIZE) + CHESSBOARD_ORIGIN_Y);
}

/*** DERIVED CLASS ***/
//PAWN CLASS
Chess::Pawn::Pawn(int i, int j, Chess::Color color,Chessboard* chessboard)
: Chess::Piece(i,j,color,chessboard)
{
    if(color == WHITE) {
        texture.loadFromFile("../images/chess_asset_white.png",sf::IntRect(0,BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    else{
        texture.loadFromFile("../images/chess_asset.png",sf::IntRect(0,BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    sprite.setTexture(texture);
}

void Chess::Pawn::findMovement()
{
    box_checked.clear();
    if(color == WHITE){
        if(chessBoard->getPiece(pos_i - 1 ,pos_j) == NULL)
            box_checked.push_back(std::pair<int,int>(pos_i - 1 ,pos_j));
        if(chessBoard->getPiece(pos_i - 2 ,pos_j) == NULL
           && pos_i == 6)
            box_checked.push_back(std::pair<int,int>(pos_i - 2,pos_j));
        if(chessBoard->getPiece(pos_i - 1 ,pos_j - 1) != NULL
           && chessBoard->getPiece(pos_i - 1 ,pos_j - 1)->getColor() != color)
            box_checked.push_back(std::pair<int,int>(pos_i - 1 ,pos_j - 1));
        if(chessBoard->getPiece(pos_i - 1 ,pos_j + 1) != NULL
           && chessBoard->getPiece(pos_i - 1 ,pos_j + 1)->getColor() != color)
            box_checked.push_back(std::pair<int,int>(pos_i - 1 ,pos_j + 1));
    }
    else{
        if(chessBoard->getPiece(pos_i + 1 ,pos_j) == NULL)
            box_checked.push_back(std::pair<int,int>(pos_i + 1 ,pos_j));
        if(chessBoard->getPiece(pos_i + 2 ,pos_j) == NULL
           && pos_i == 1)
            box_checked.push_back(std::pair<int,int>(pos_i + 2,pos_j));
        if(chessBoard->getPiece(pos_i + 1 ,pos_j + 1) != NULL
           && chessBoard->getPiece(pos_i + 1 ,pos_j + 1)->getColor() != color)
            box_checked.push_back(std::pair<int,int>(pos_i + 1 ,pos_j + 1));
        if(chessBoard->getPiece(pos_i + 1 ,pos_j - 1) != NULL
           && chessBoard->getPiece(pos_i + 1 ,pos_j - 1)->getColor() != color)
            box_checked.push_back(std::pair<int,int>(pos_i + 1 ,pos_j - 1));
    }
}

// KNIGHT CLASS
Chess::Knight::Knight(int i, int j, Chess::Color color,Chessboard* chessboard)
: Piece(i,j,color,chessboard)
{
    if(color == WHITE) {
        texture.loadFromFile("../images/chess_asset_white.png",sf::IntRect(2 * BOX_SIZE,BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    else if (color == BLACK){
        texture.loadFromFile("../images/chess_asset.png",sf::IntRect(2*BOX_SIZE,BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    type = KNIGHT;
    sprite.setTexture(texture);
}

void Chess::Knight::findMovement() {
    box_checked.clear();
    int i = pos_i-2;
    int j = pos_j+1;
    if(((i>=0 && j<=7)) && (chessBoard->getPiece(i,j)==NULL
        ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color)))
        box_checked.push_back(std::pair<int,int>(i,j));

    i = pos_i-2;
    j = pos_j-1;
    if((i>=0 && j>=0) && (chessBoard->getPiece(i,j)==NULL
          ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color)))
        box_checked.push_back(std::pair<int,int>(i,j));

    i = pos_i-1;
    j = pos_j+2;
    if((i>=0 && j<=7) && (chessBoard->getPiece(i,j)==NULL
          ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color)))
        box_checked.push_back(std::pair<int,int>(i,j));

    i = pos_i-1;
    j = pos_j-2;
    if((i>=0 && j>=0) && (chessBoard->getPiece(i,j)==NULL
          ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color)))
        box_checked.push_back(std::pair<int,int>(i,j));

    i = pos_i+2;
    j = pos_j+1;
    if(i<=7 && j<=7 && (chessBoard->getPiece(i,j)==NULL
        ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color)))
        box_checked.push_back(std::pair<int,int>(i,j));

    i = pos_i+2;
    j = pos_j-1;
    if((i<=7 && j>=0) && (chessBoard->getPiece(i,j)==NULL
          ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color)))
        box_checked.push_back(std::pair<int,int>(i,j));

    i = pos_i+1;
    j = pos_j+2;
    if((i<=7 && j<=7) && (chessBoard->getPiece(i,j)==NULL
          ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color)))
        box_checked.push_back(std::pair<int,int>(i,j));

    i = pos_i+1;
    j = pos_j-2;
    if((i<=7 && j>=0) && (chessBoard->getPiece(i,j)==NULL
          ||( chessBoard->getPiece(i,j)!=NULL && chessBoard->getPiece(i,j)->getColor() != color)))
        box_checked.push_back(std::pair<int,int>(i,j));
}

// TOWER CLASS
Chess::Tower::Tower(int i, int j, Chess::Color color, Chess::Chessboard *chessboard)
:Piece(i,j,color,chessboard)
{
    if(color == WHITE) {
        texture.loadFromFile("../images/chess_asset_white.png",sf::IntRect(3 * BOX_SIZE,BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    else if (color == BLACK){
        texture.loadFromFile("../images/chess_asset.png",sf::IntRect(3*BOX_SIZE,BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    type = TOWER;
    sprite.setTexture(texture);
}

void Chess::Tower::findMovement()
{
    box_checked.clear();
    int j = pos_j;
    for(int i=pos_i-1;i>=0; i--){
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
    j = pos_j;
    for(int i=pos_i+1;i<=7; i++){
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
    int i = pos_i;
    for(int j=pos_j-1;j>=0; j--){
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
    i = pos_i;
    for(int j=pos_j+1;j<=7; j++){
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
}

//BISHOP CLASS
Chess::Bishop::Bishop(int i, int j, Chess::Color color, Chess::Chessboard *chessboard)
:Piece(i,j,color,chessboard)
{
    if(color == WHITE) {
        texture.loadFromFile("../images/chess_asset_white.png",sf::IntRect(1 * BOX_SIZE,BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    else if (color == BLACK){
        texture.loadFromFile("../images/chess_asset.png",sf::IntRect(1*BOX_SIZE,BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    type = BISHOP;
    sprite.setTexture(texture);
}

void Chess::Bishop::findMovement()
{
    box_checked.clear();
    int j = pos_j;
    for(int i=pos_i-1;i>=0 && j>0; i--){
        j--;
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
    j = pos_j;
    for(int i=pos_i+1;i<=7 && j<7; i++){
        j++;
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));

    }
    j = pos_j;
    for(int i=pos_i-1;i>=0&& j<7; i--){
        j++;
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));

    }
    j = pos_j;
    for(int i=pos_i+1;i<=7 && j>0; i++){
        j--;
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
}

//KING CLASS
Chess::King::King(int i, int j, Chess::Color color, Chess::Chessboard *chessboard)
:Piece(i,j,color,chessboard)
{
    if(color == WHITE) {
        texture.loadFromFile("../images/chess_asset_white.png",sf::IntRect(2 * BOX_SIZE,0 * BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    else if (color == BLACK){
        texture.loadFromFile("../images/chess_asset.png",sf::IntRect(2 * BOX_SIZE,0 * BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    type = KING;
    sprite.setTexture(texture);
}

void Chess::King::findMovement()
{
    box_checked.clear();
    int j = pos_j - 1;
    for(int i = pos_i - 1;i < pos_i + 2 && j > 0 ; i++){
        if(i < 0 || i > 7 ||
            (chessBoard->getPiece(i,j) != NULL && chessBoard->getPiece(i,j)->getColor() == color )) continue;
        box_checked.push_back(std::pair<int,int>(i,j));
    }

    j = pos_j;
    for(int i = pos_i - 1;i < pos_i + 2 ; i++){
        if(i < 0 || i > 7 ||
           (chessBoard->getPiece(i,j) != NULL && chessBoard->getPiece(i,j)->getColor() == color )) continue;
        box_checked.push_back(std::pair<int,int>(i,j));
    }

    j = pos_j + 1;
    for(int i = pos_i - 1;i < pos_i + 2 && j < 7; i++){
        if(i < 0 || i > 7 ||
           (chessBoard->getPiece(i,j) != NULL && chessBoard->getPiece(i,j)->getColor() == color )) continue;
        box_checked.push_back(std::pair<int,int>(i,j));
    }
}

//QUEEN CLASS
Chess::Queen::Queen(int i, int j, Chess::Color color, Chess::Chessboard *chessboard)
:Piece(i,j,color,chessboard)
{
    if(color == WHITE) {
        texture.loadFromFile("../images/chess_asset_white.png",sf::IntRect(3 * BOX_SIZE,0 * BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    else if (color == BLACK){
        texture.loadFromFile("../images/chess_asset.png",sf::IntRect(3 * BOX_SIZE,0 * BOX_SIZE,BOX_SIZE,BOX_SIZE));
    }
    type = QUEEN;
    sprite.setTexture(texture);
}

void Chess::Queen::findMovement()
{
    /*** BISHOP SIMULATED ***/
    box_checked.clear();
    int j = pos_j;
    for(int i=pos_i-1;i>=0 && j>0; i--){
        j--;
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
    j = pos_j;
    for(int i=pos_i+1;i<=7 && j<7; i++){
        j++;
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));

    }
    j = pos_j;
    for(int i=pos_i-1;i>=0&& j<7; i--){
        j++;
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));

    }
    j = pos_j;
    for(int i=pos_i+1;i<=7 && j>0; i++){
        j--;
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }

    /*** TOWER SIMULATED ***/
    j = pos_j;
    for(int i=pos_i-1;i>=0; i--){
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
    j = pos_j;
    for(int i=pos_i+1;i<=7; i++){
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
    int i = pos_i;
    for(int j=pos_j-1;j>=0; j--){
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
    i = pos_i;
    for(int j=pos_j+1;j<=7; j++){
        if(chessBoard->getPiece(i,j) != NULL){
            if(chessBoard->getPiece(i,j)->getColor() == color)
                break;
            box_checked.push_back(std::pair<int,int>(i,j));
            break;
        }
        box_checked.push_back(std::pair<int,int>(i,j));
    }
}