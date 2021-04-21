#ifndef SETTINGS_H
#define SETTINGS_H


#include <QObject>
#include <QDebug>

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

static const QString PATHC = "./content/imgs/";
static const QString PATHM = "./maps/";
static const int s = 60;

#endif // SETTINGS_H


