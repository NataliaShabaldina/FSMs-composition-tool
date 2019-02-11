#ifndef FSMITEM_H
#define FSMITEM_H

#include "common-item.h"

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>

class fsmItem : public commonItem
{
private:
     // Используется для нумерации автоматов
     // Увеличивается в конструкторе
     static int fsmNumber;

     int number_;
     QGraphicsTextItem* nameItem_;
public:
     fsmItem(QGraphicsItem* parent = nullptr);
     ~fsmItem();

     /// @brief Определяет невидимые элементы и неприкрытые области, которые должны быть отрисованы стр. 324
     virtual QRectF boundingRect() const;

     /// @brief Отвечает за отображение элемента
     virtual void paint(QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget*);
};

#endif // FSMITEM_H
