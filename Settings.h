#ifndef SETTINGS_H
#define SETTINGS_H


#include <QObject>
//#include <QDebug>
#include <QApplication>

enum MoveElement{
    Stop,
    Up,
    Right,
    Down,
    Left,
    Block
};

enum MapElement{
    Road,
    Wall,
    Box,
    Point,
    InPoint,
    Empty,
    Player,
    PlayerInPoint
};

#define PATHC (QApplication::applicationDirPath() + "/content/imgs/")
#define PATHM (QApplication::applicationDirPath() + "/maps/")
static const int s = 60;

#endif // SETTINGS_H


