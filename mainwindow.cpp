#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fsm-item.h"
#include "link-item.h"
#include "composition-item.h"
#include "view.h"
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
     auto fsm = new fsmItem;
     fsm->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     scene_.addItem(fsm);
}

void MainWindow::on_addLinkButt_clicked()
{
     auto link = new linkItem;
     link->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     scene_.addItem(link);
}

void MainWindow::on_addCompButt_clicked()
{
     auto compostion = new compositionItem;
     compostion->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     compostion->setZValue(globals::behindAllItems);
     scene_.addItem(compostion);
}

void MainWindow::on_delButt_clicked()
{
     scene_.clear();
}

MainWindow::~MainWindow()
{
     delete ui_;
}
