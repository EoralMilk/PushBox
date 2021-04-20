#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "Settings.h"
#include <QImage>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(int xpos,int ypos,QObject *parent = nullptr);

    int XPos;
    int YPos;
    QImage playerImage;

    void DrawPlayer(QPainter* painter);

    void Move(MoveElement move);



signals:

};

#endif // PLAYER_H
