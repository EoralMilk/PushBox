#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "GameMap.h"
#include "Settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    ~Widget();

private:
    Ui::Widget *ui;

    GameMap* mMap;

    QPainter* mMapPainter;

    QTimer* timer;

};
#endif // WIDGET_H
