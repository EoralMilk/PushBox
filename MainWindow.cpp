#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *label = new QLabel("<h2><i>Hello</i> "
                                  "<font color=red>Qt!</font></h2>",this);
    label->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
