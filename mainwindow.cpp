#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fsm-item.h"
#include "link-item.h"
#include "composition-item.h"
#include "globals.h"

#include <QGraphicsRectItem>

int linkItem::linkNumber = 0;
int fsmItem::fsmNumber = 0;


MainWindow::MainWindow(QWidget *parent) :
     QMainWindow(parent),
     ui_(new Ui::MainWindow), scene_(QRectF(-100, -100, 300, 300)) ///@todo разобраться с размерами
{
     ui_->setupUi(this);

     ui_->graphicsView->setScene(&scene_);
}

void MainWindow::on_addFsmButt_clicked()
{
     fsmItem* fsm = new fsmItem;
     fsm->setFlags(QGraphicsItem::ItemIsMovable);
     scene_.addItem(fsm);
}

void MainWindow::on_addLinkButt_clicked()
{
     linkItem* link = new linkItem;
     link->setFlags(QGraphicsItem::ItemIsMovable);
     scene_.addItem(link);
}

void MainWindow::on_addCompButt_clicked()
{
     compositionItem* compostion = new compositionItem;
     compostion->setFlags(QGraphicsItem::ItemIsMovable);
     compostion->setZValue(globals::behindAllItems);
     scene_.addItem(compostion);
}

MainWindow::~MainWindow()
{
     delete ui_;
}
