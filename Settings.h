#ifndef SETTINGS_H
#define SETTINGS_H


#include <QObject>
#include <QDebug>
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

static const QString PATHC = QApplication::applicationDirPath() + "/content/imgs/";
static const QString PATHM = QApplication::applicationDirPath() + "/maps/";
static const int s = 60;

#endif // SETTINGS_H


