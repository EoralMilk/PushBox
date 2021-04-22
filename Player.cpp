#include "Player.h"
#include <QPainter>

Player::Player(int xpos,int ypos,QObject *parent) : QObject(parent)
{
    XPos = xpos;
    YPos = ypos;
    playerImage = QImage(PATHC + "player-d.png");
}

void Player::DrawPlayer(QPainter* PPainter){
    PPainter->drawImage(QRect(XPos*s,YPos*s,s,s),playerImage);
}

void Player::Move(MoveElement move){
    switch (move) {
        case Up: YPos -= 1; break;
        case Right: XPos += 1; break;
        case Down: YPos += 1; break;
        case Left: XPos -= 1; break;
        case Stop:
        case Block:
            break;
    }
//    qDebug()<<" XPos:"<<XPos<<" YPos:"<<YPos;
}
