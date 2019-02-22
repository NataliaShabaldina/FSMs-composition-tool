#ifndef LINKITEM_H
#define LINKITEM_H

#include "arrow-item.h"
#include "common-item.h"

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>

class linkItem : public commonItem
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

private:
     void rotate();

public:
     linkItem(QGraphicsItem* parent = nullptr);
     ~linkItem();

     QString getName() const;

     /// @brief Определяет невидимые элементы и неприкрытые области, которые должны быть отрисованы стр. 324
     virtual QRectF boundingRect() const;

     /// @brief Отвечает за отображение элемента
     virtual void paint(QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget*);

     /// @brief При двойном клике стрелка меняет своё направление
     virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

     /// @brief Конекстное меню для автомата содержит также прикрепление файла
     virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};


#endif // LINKITEM_H
