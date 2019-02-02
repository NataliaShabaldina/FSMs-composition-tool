#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
     Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = nullptr);
     ~MainWindow();

public slots:
     ///@brief Слот нажатия на кнопку добавления автомата
     ///       Добавляет на сцену прямоугольник
     void on_addFsmButt_clicked();

     ///@brief Слот нажатия на кнопку добавления связи
     ///       Добавляет на сцену линию
     void on_addLinkButt_clicked();

private:
     Ui::MainWindow* ui_;
     QGraphicsScene scene_;
};

#endif // MAINWINDOW_H
