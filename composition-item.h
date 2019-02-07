#ifndef COMPOSITIONITEM_H
#define COMPOSITIONITEM_H

#include "common-item.h"

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>

class compositionItem : public commonItem
{
public:
     compositionItem();

     /// @brief Определяет невидимые элементы и неприкрытые области, которые должны быть отрисованы стр. 324
     virtual QRectF boundingRect() const;

     /// @brief Отвечает за отображение элемента
     virtual void paint(QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget*);
};

#endif // COMPOSITIONITEM_H
