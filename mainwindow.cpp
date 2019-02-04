#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fsm-item.h"

#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent) :
     QMainWindow(parent),
     ui_(new Ui::MainWindow), scene_(QRectF(-100, -100, 300, 300)) ///@todo разобраться с размерами
{
     ui_->setupUi(this);

     ui_->graphicsView->setScene(&scene_);
}

int fsmItem::fsmNumber = 0;
void MainWindow::on_addFsmButt_clicked()
{
     fsmItem* fsm = new fsmItem;
     fsm->setFlags(QGraphicsItem::ItemIsMovable);
     scene_.addItem(fsm);
}

void MainWindow::on_addLinkButt_clicked()
{
     QGraphicsLineItem* currLine = scene_.addLine(QLineF(0, 0, 80, 0), QPen(Qt::black, 3));
     QGraphicsSimpleTextItem* linkName = scene_.addSimpleText("A"); ///@todo каждый раз новая буква
     linkName->setParentItem(currLine);
     linkName->setPos(40, 5);
     currLine->setFlags(QGraphicsItem::ItemIsMovable);
}

MainWindow::~MainWindow()
{
     delete ui_;
}
