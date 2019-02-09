#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
     Q_OBJECT
public slots:
     void deleteItem();

public:
     View(QWidget* parent = nullptr);
     View(QGraphicsScene* scene, QWidget* parent = nullptr);

     virtual void keyPressEvent(QKeyEvent* event);
};

#endif // VIEW_H
