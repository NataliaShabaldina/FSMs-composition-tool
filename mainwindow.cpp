#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent) :
     QMainWindow(parent),
     ui_(new Ui::MainWindow), scene_(QRectF(-100, -100, 300, 300)) ///@todo разобраться с размерами
{
     ui_->setupUi(this);

     ui_->graphicsView->setScene(&scene_);
}

void MainWindow::on_addFsmButt_clicked()
{
     QGraphicsRectItem* currRect = scene_.addRect(QRectF(-30, -30, 120, 80), QPen(Qt::black));
     currRect->setFlags(QGraphicsItem::ItemIsMovable);
}

void MainWindow::on_addLinkButt_clicked()
{
     QGraphicsLineItem* currLine = scene_.addLine(QLineF(-10, -10, -80, -80), QPen(Qt::black, 3));
     currLine->setFlags(QGraphicsItem::ItemIsMovable);
}

MainWindow::~MainWindow()
{
     delete ui_;
}
