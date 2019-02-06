#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QGraphicsItem>

class arrowItem : public QGraphicsItem
{
public:
     arrowItem(QGraphicsItem* parent);

     /// @brief Определяет невидимые элементы и неприкрытые области, которые должны быть отрисованы стр. 324
     virtual QRectF boundingRect() const;

     /// @brief Отвечает за отображение элемента
     virtual void paint(QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget*);
};



#endif // ARROWITEM_H
