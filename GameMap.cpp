#include "GameMap.h"
#include <QFile>

GameMap::GameMap(QObject *parent) : QObject(parent)
{
    mRow = 0;
    mCol = 0;
    mPMap = nullptr;

}

GameMap::~GameMap(){
    Clear();
}

void GameMap::Clear(){
    if(mPMap != nullptr){
        for(int i=0; i<mRow; i++){
            delete [] mPMap[i];
        }
        delete []  mPMap;
    }
    if(player != nullptr){
        delete player;
    }
}

bool GameMap::InitByFile(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {

        return false;
    }

    //读取所有内容
    QByteArray all =  file.readAll();
    all.replace("\r\n","\n");
    QList<QByteArray> lines = all.split('\n');

    qDebug()<<"lines:"<<lines;


    mRow = lines.size(); //确定行数
    qDebug()<<"mRow:"<<mRow;

    mPMap = new int*[mRow+2];
    mCol = lines[0].split(',').size(); //确定列数
    qDebug()<<"mRow:"<<mRow<<"  mCol:"<<mCol;
    for(int i = 0; i<mRow+2; i++){
        // 赋值地图二维数组
        mPMap[i] = new int[mCol+2];
        if(i == 0 || i == mRow+1){ //第一行和最后一行都是空的
            for(int j = 0; j<mCol+2;j++){
                mPMap[i][j] = Empty;
            }
        }
        else{
            QList<QByteArray> cols = lines[i-1].split(',');
            for(int j = 0; j<mCol+2;j++){
                if(j == 0 || j == mCol+1){ //第一列和最后一列都是空的
                    mPMap[i][j] = Empty;
                }
                else{
                    if(cols[j-1].toUInt() == Player ||
                       cols[j-1].toUInt() == PlayerInPoint){//确定玩家位置
                        player = new class Player(j,i,this);

                    }
                    mPMap[i][j] = cols[j-1].toUInt();
                }
            }
        }

    }


    return true;

}


MoveElement GameMap::CollisionTool(MoveElement move,int x,int y,int x2,int y2)
{
    //前面是墙
    if(mPMap[y][x] == Wall)
    {
    qDebug()<<"Block";
    return Block;
    }
    //前面是箱子
    else if(mPMap[y][x] == Box)
    {
        //箱子前面是箱子或者墙
        if(mPMap[y2][x2] == Box||
            mPMap[y2][x2] == InPoint||
            mPMap[y2][x2] == Wall){
                return Block;
            }
        else {
            if(mPMap[y2][x2] == Road ||
            mPMap[y2][x2] == Player)
            {
                //箱子前面是道路
                mPMap[y][x] = Road;
                mPMap[y2][x2] = Box;
            }
            if(mPMap[y2][x2] == Point||
            mPMap[y2][x2] == PlayerInPoint)
            {
                //箱子前面是目标点
                mPMap[y][x] = Road;
                mPMap[y2][x2] = InPoint;
            }
            qDebug()<<"Up";
            return move;
        }
    }
    //前面是目标点上的箱子
    else if(mPMap[y][x] == InPoint)
    {
        //箱子前面是箱子或者墙
        if(mPMap[y2][x2] == Box||
            mPMap[y2][x2] == InPoint||
            mPMap[y2][x2] == Wall){
                return Block;
            }
        else {
            if(mPMap[y2][x2] == Road ||
            mPMap[y2][x2] == Player)
            {
                //箱子前面是道路
                mPMap[y][x] = Point;
                mPMap[y2][x2] = Box;
            }
            if(mPMap[y2][x2] == Point||
            mPMap[y2][x2] == PlayerInPoint)
            {
                //箱子前面是目标点
                mPMap[y][x] = Point;
                mPMap[y2][x2] = InPoint;
            }
            qDebug()<<"Up";
            return move;
        }
    }
    else {
            qDebug()<<"Up";
            return move;
        }
    }

MoveElement GameMap::Collision(MoveElement move,int xpos,int ypos){
    switch (move) {
    case Up: return CollisionTool(move,xpos,ypos-1,xpos,ypos-2);

    case Right: return CollisionTool(move,xpos+1,ypos,xpos+2,ypos);
    case Down: return CollisionTool(move,xpos,ypos+1,xpos,ypos+2);
    case Left: return CollisionTool(move,xpos-1,ypos,xpos-2,ypos);
    case Stop:
    case Block:
        return move;
    }
}

QString GameMap::SwitchWallType(int ** mapp, int i, int j){

    if(   mapp[i-1][j] == Wall
       && mapp[i+1][j] == Wall
       && mapp[i][j-1] != Wall
       && mapp[i][j+1] != Wall)
    {
        return PATHC + "wall-td.png";
    }
    else if(   mapp[i-1][j] != Wall
            && mapp[i+1][j] != Wall
            && mapp[i][j-1] == Wall
            && mapp[i][j+1] == Wall){
        return PATHC + "wall-rl.png";
    }
    // 角
    else if(   mapp[i-1][j] != Wall
            && mapp[i+1][j] == Wall
            && mapp[i][j-1] != Wall
            && mapp[i][j+1] == Wall){
        return PATHC + "wall-rd.png";
    }
    else if(   mapp[i-1][j] != Wall
            && mapp[i+1][j] == Wall
            && mapp[i][j-1] == Wall
            && mapp[i][j+1] != Wall){
        return PATHC + "wall-dl.png";
    }
    else if(   mapp[i-1][j] == Wall
            && mapp[i+1][j] != Wall
            && mapp[i][j-1] != Wall
            && mapp[i][j+1] == Wall){
        return PATHC + "wall-tr.png";
    }
    else if(   mapp[i-1][j] == Wall
            && mapp[i+1][j] != Wall
            && mapp[i][j-1] == Wall
            && mapp[i][j+1] != Wall){
        return PATHC + "wall-tl.png";
    }
    //3向
    else if(   mapp[i-1][j] != Wall
            && mapp[i+1][j] == Wall
            && mapp[i][j-1] == Wall
            && mapp[i][j+1] == Wall){
        return PATHC + "wall-rdl.png";
    }
    else if(   mapp[i-1][j] == Wall
            && mapp[i+1][j] == Wall
            && mapp[i][j-1] == Wall
            && mapp[i][j+1] != Wall){
        return PATHC + "wall-tdl.png";
    }
    else if(   mapp[i-1][j] == Wall
            && mapp[i+1][j] != Wall
            && mapp[i][j-1] == Wall
            && mapp[i][j+1] == Wall){
        return PATHC + "wall-trl.png";
    }
    else if(   mapp[i-1][j] == Wall
            && mapp[i+1][j] == Wall
            && mapp[i][j-1] != Wall
            && mapp[i][j+1] == Wall){
        return PATHC + "wall-trd.png";
    }
    //1向
    else if(   mapp[i-1][j] == Wall
            && mapp[i+1][j] != Wall
            && mapp[i][j-1] != Wall
            && mapp[i][j+1] != Wall){
        return PATHC + "wall-td.png";
    }
    else if(   mapp[i-1][j] != Wall
            && mapp[i+1][j] == Wall
            && mapp[i][j-1] != Wall
            && mapp[i][j+1] != Wall){
        return PATHC + "wall-td.png";
    }
    else if(   mapp[i-1][j] != Wall
            && mapp[i+1][j] != Wall
            && mapp[i][j-1] == Wall
            && mapp[i][j+1] != Wall){
        return PATHC + "wall-rl.png";
    }
    else if(   mapp[i-1][j] != Wall
            && mapp[i+1][j] != Wall
            && mapp[i][j-1] != Wall
            && mapp[i][j+1] == Wall){
        return PATHC + "wall-rl.png";
    }
    // 4向
    else if(   mapp[i-1][j] == Wall
            && mapp[i+1][j] == Wall
            && mapp[i][j-1] == Wall
            && mapp[i][j+1] == Wall){
        return PATHC + "wall-trdl.png";
    }
    return PATHC + "wall-trdl.png";
}

void GameMap::PaintMap(QPainter* mMapPainter){

    int** mapp = mPMap;
    for(int i=0; i<mRow+2; i++){
        for (int j=0; j<mCol+2; j++ ) {
            QString cellUrl;
            switch (mapp[i][j]) {
                case Road: cellUrl = PATHC + "road.png"; break;
                case Box: cellUrl = PATHC + "box.png"; break;
                case Player: cellUrl = PATHC + "road.png"; break;

                case Wall:
                    cellUrl = SwitchWallType(mapp,i,j);
                    break;

                case Point: cellUrl = PATHC + "point.png"; break;
                case InPoint: cellUrl = PATHC + "inpoint.png"; break;
                case PlayerInPoint: cellUrl = PATHC + "point.png"; break;

                case Empty: cellUrl = PATHC + "empty.png"; break;

            }
            QImage img(cellUrl);
            mMapPainter->drawImage(QRect(j*s,i*s,s,s),img);
        }
    }
}
