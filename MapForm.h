#ifndef MAPFORM_H
#define MAPFORM_H

#include <QWidget>
#include "GameMap.h"
#include "Settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MapForm; }
QT_END_NAMESPACE

class MapForm : public QWidget
{
    Q_OBJECT

public:
    MapForm(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    ~MapForm();

private:
    Ui::MapForm *ui;

    GameMap* mMap;

    QPainter* mMapPainter;

    QTimer* timer;

};
#endif // MAPFORM_H
