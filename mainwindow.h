#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui 
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
     Q_OBJECT
private:
     Ui::MainWindow* ui_;
     Scene scene_;

public slots:
     /// !!!Слоты вида on_btnName_clicked() коннектятся с сигналом автоматически!!!

     ///@brief Слот нажатия на кнопку добавления автомата
     ///       Добавляет на сцену прямоугольник
     void on_addFsmButt_clicked();

     ///@brief Слот нажатия на кнопку добавления связи
     ///       Добавляет на сцену линию
     void on_addLinkButt_clicked();

     ///@brief Слот нажатия на кнопку добавления композиции
     ///       Добавляет на сцену пунктирный прямоугольник
     void on_addCompButt_clicked();

     void on_delButt_clicked();

public:
     explicit MainWindow(QWidget *parent = nullptr);
     ~MainWindow();
};

#endif // MAINWINDOW_H
