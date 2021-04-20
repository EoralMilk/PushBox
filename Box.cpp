#include "Box.h"
#include <QPainter>

Box::Box(int xpos,int ypos,QObject *parent) : QObject(parent)
{
    XPos = xpos;
    YPos = ypos;
    boxImage = QImage(PATHC + "box.png");
}


void Box::DrawBox(QPainter* PPainter){
    PPainter->drawImage(QRect(XPos*s,YPos*s,s,s),boxImage);
}


void Box::Move(MoveElement move){
    switch (move) {
        case Up: YPos -= 1; break;
        case Right: XPos += 1; break;
        case Down: YPos += 1; break;
        case Left: XPos -= 1; break;
        case Stop:
        case Block:
            break;
    }
    qDebug()<<"Box XPos:"<<XPos<<" Box YPos:"<<YPos;
}
