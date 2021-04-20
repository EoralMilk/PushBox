#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QObject>
#include <QPainter>
#include "Settings.h"
#include "Player.h"

class GameMap : public QObject
{
    Q_OBJECT
public:
    explicit GameMap(QObject *parent = nullptr);
    ~GameMap();

    bool InitByFile(QString filename); //从文件初始化地图
    void Clear();
    QString SwitchWallType(int** mmap, int i,int j);
    void PaintMap(QPainter* mMapPainter);
    MoveElement Collision(MoveElement move,int xpos,int ypos);
    MoveElement CollisionTool(MoveElement move,int x, int y,int x2, int y2);
    int mRow;
    int mCol;
//    int pXPos;
//    int pYPos;
    int** mPMap; //用于开辟二维数组的2d地图元素

    class Player* player;

signals:

};

#endif // GAMEMAP_H
