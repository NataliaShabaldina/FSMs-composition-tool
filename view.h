#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

/// @brief Класс представления
class View : public QGraphicsView
{
     Q_OBJECT

public:
     View(QWidget* parent = nullptr);
     View(QGraphicsScene* scene, QWidget* parent = nullptr);
};

#endif // VIEW_H
