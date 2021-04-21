#ifndef MAPFORM_H
#define MAPFORM_H

#include <QWidget>
#include "GameMap.h"
#include "Settings.h"

class MapForm : public QWidget
{
    Q_OBJECT

public:
    MapForm(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);

private:
    GameMap* mMap;

    QPainter* mMapPainter;

    QTimer* timer;

};
#endif // MAPFORM_H
