#ifndef LINKITEM_H
#define LINKITEM_H

#include "arrow-item.h"
#include "common-item.h"
#include "link.h"
#include "globals.h"

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>

/// @brief Класс связи как графического элемента
///        Содержит в себе связь как логический элемент
///        Отвечает за его формирование
///        В процессе формирования связи (лог. эл.) вызывает формирование автомата (лог. эл.)
class LinkItem : public CommonItem
{
private:
     enum { reverseAngle = 180 };
     enum { standartLenght = 80 };
     enum { standartWidth = 20 };

     // Используется для нумерации автоматов
     // Увеличивается в конструкторе
     static int linkNumber;

     int number_;

     /// @brief Итем отрисовывающий стрелку
     ArrowItem* arrowItem_;
     /// @brief Итем отрисосывающий имя канала
     QGraphicsTextItem* idItem_;
     /// @brief Логический элемент канала
     Link link_;

     /// @brief Точка начала стрелки
     QPointF startPoint_;
     /// @brief Точка конца стрелки
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

     virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

#ifdef QT_DEBUG
     virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
     void printDebugInfo();
#endif //QT_DEBUG

public:
     LinkItem(QGraphicsItem* parent = nullptr);
     ~LinkItem();

     int       type() const;
     QString   getId() const;
     /// @brief Возвращает связь как логический элемент
     Link      getLink() const;

     /// @brief Формирует логический элемент
     ///        Вызывает формирование автоматов входящих в эту связь
     void formLink();
};


#endif // LINKITEM_H
