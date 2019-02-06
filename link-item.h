#ifndef LINKITEM_H
#define LINKITEM_H

#include "arrow-item.h"

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>

class linkItem : public QGraphicsItem
{
private:
     // Используется для нумерации автоматов
     // Увеличивается в конструкторе
     static int linkNumber;

     enum { reverseAngle = 180 };
     enum { standartLenght = 80 };
     enum { standartWidth = 20 };

     int number_;

     arrowItem* arrowItem_;
     QGraphicsTextItem* nameItem_;
public:
     linkItem();

     QString getName() const;

     /// @brief Определяет невидимые элементы и неприкрытые области, которые должны быть отрисованы стр. 324
     virtual QRectF boundingRect() const;

     /// @brief Отвечает за отображение элемента
     virtual void paint(QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget*);

     /// @brief Действие при нажатии кнопки мыши (курсор на указательный палец)
     virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

     /// @brief Действие при отпускании кнопки мыши (меняется курсор на обычный)
     virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

     /// @brief При двойном клике стрелка меняет своё направление
     virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};


#endif // LINKITEM_H
