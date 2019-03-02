#ifndef COMPOSITIONITEM_H
#define COMPOSITIONITEM_H

#include "common-item.h"
#include "composition.h"
#include "globals.h"

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>

class CompositionItem : public CommonItem
{
private:
     Composition composition_;

protected:
     /// @brief Определяет невидимые элементы и неприкрытые области, которые должны быть отрисованы стр. 324
     virtual QRectF boundingRect() const;

     /// @brief Отвечает за отображение элемента
     virtual void paint(QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget*);

public:
     CompositionItem(QGraphicsItem* parent = nullptr);

     /// @brief Формирует логический элемент композиции
     void formComposition();

     int type() const;
};

#endif // COMPOSITIONITEM_H
