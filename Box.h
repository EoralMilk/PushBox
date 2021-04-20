#ifndef BOX_H
#define BOX_H

#include <QObject>
#include "Settings.h"
#include <QImage>

class Box : public QObject
{
    Q_OBJECT
public:
    explicit Box(int xpos,int ypos,QObject *parent = nullptr);

    int XPos;
    int YPos;
    QImage boxImage;

    void DrawBox(QPainter* painter);

    void Move(MoveElement move);

signals:

};

#endif // BOX_H
