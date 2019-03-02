#ifndef LINKITEM_H
#define LINKITEM_H

#include "arrow-item.h"
#include "common-item.h"
#include "link.h"
#include "globals.h"

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>

class LinkItem : public CommonItem
{
private:
     // Используется для нумерации автоматов
     // Увеличивается в конструкторе
     static int linkNumber;

     enum { reverseAngle = 180 };
     enum { standartLenght = 80 };
     enum { standartWidth = 20 };

     int number_;

     /// @brief Итем отрисовывающий стрелку
     ArrowItem* arrowItem_;
     /// @brief Итем отрисосывающий имя канала
     QGraphicsTextItem* idItem_;
     /// @brief Логический элемент канала
     Link link_;

     QPointF startPoint_;
     QPointF endPoint_;
private:
     /// @brief Разворачивает стрелку на 180 градусов
     void rotate();

protected:
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

#ifdef QT_DEBUG
     virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
#endif //QT_DEBUG

public:
     LinkItem(QGraphicsItem* parent = nullptr);
     ~LinkItem();

     QString getName() const;

     /// @brief Формирует логический элемент
     /// @exception
     void formLink();
     void debug();
     int type() const;
};


#endif // LINKITEM_H
