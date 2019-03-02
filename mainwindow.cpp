#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fsm-item.h"
#include "link-item.h"
#include "composition-item.h"
#include "view.h"
#include "globals.h"

#include <QGraphicsRectItem>

int LinkItem::linkNumber = 0;
int FsmItem::fsmNumber = 0;


MainWindow::MainWindow(QWidget *parent) :
     QMainWindow(parent),
     ui_(new Ui::MainWindow), scene_(QRectF(0, 0, 500, 450)) ///@todo разобраться с размерами
{
     ui_->setupUi(this);

     ui_->graphicsView->setScene(&scene_);
}

void MainWindow::on_addFsmButt_clicked()
{
     scene_.addFsm();
}

void MainWindow::on_addLinkButt_clicked()
{
     scene_.addLink();
}

void MainWindow::on_addCompButt_clicked()
{
     scene_.addComposition();
}

void MainWindow::on_delButt_clicked()
{
     scene_.clear();
}

MainWindow::~MainWindow()
{
     delete ui_;
}
