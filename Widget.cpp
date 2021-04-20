#include "Widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QPainter>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    mMap = new GameMap(this);
    QString fileName = QFileDialog::getOpenFileName(this,"打开地图","./maps/","*.txt");
    if(!mMap->InitByFile(fileName)){
        QMessageBox::warning(this,"警告","无法打开地图文件");
    }
    mMapPainter = new QPainter(this);
    timer = new QTimer(this);
    timer->start(50);

    //定时调用更新函数
    connect(timer,&QTimer::timeout,[this](){this->update();});

    setFixedSize(1024,768);

    this->update();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){
    mMapPainter->begin(this);

    //画背景
    mMapPainter->drawImage(QRect(0,0,1366,800),QImage("./content/imgs/bg1.png"));

    mMap->PaintMap(mMapPainter);

    //画人物
    mMap->player->DrawPlayer(mMapPainter);

    mMapPainter->end();
}


void Widget::keyPressEvent(QKeyEvent* event){
    switch (event->key())
    {
        case Qt::Key_W:
        case Qt::Key_Up:{
            //MoveUp
            mMap->player->playerImage =  QImage(PATHC + "player-t.png");
            mMap->player->Move(mMap->Collision(Up,mMap->player->XPos,mMap->player->YPos));
            break;
        }
        case Qt::Key_D:
        case Qt::Key_Right:{
            //MoveRight
            mMap->player->playerImage =  QImage(PATHC + "player-r.png");
            mMap->player->Move(mMap->Collision(Right,mMap->player->XPos,mMap->player->YPos));
            break;
        }
        case Qt::Key_S:
        case Qt::Key_Down:{
            //MoveDown
            mMap->player->playerImage =  QImage(PATHC + "player-d.png");
            mMap->player->Move(mMap->Collision(Down,mMap->player->XPos,mMap->player->YPos));
            break;
        }
        case Qt::Key_A:
        case Qt::Key_Left:{
            //MoveLeft
            mMap->player->playerImage =  QImage(PATHC + "player-l.png");
            mMap->player->Move(mMap->Collision(Left,mMap->player->XPos,mMap->player->YPos));
            break;
        }
    }
    if(mMap->CheckWin()){
        QMessageBox::information(this,"完成","你成功了");
        close();
    }
}
