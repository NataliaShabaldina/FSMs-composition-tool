#ifndef FSMITEM_H
#define FSMITEM_H

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>

class fsmItem : public QGraphicsItem
{
private:
     enum { penWidth = 2 };

     // Используется для нумерации автоматов
     // Увеличивается в конструкторе
     static int fsmNumber;

public:
     fsmItem();

     /// @brief Определяет невидимые элементы и неприкрытые области, которые должны быть отрисованы стр. 324
     virtual QRectF boundingRect() const;

     /// @brief Отвечает за отображение элемента
     virtual void paint(QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget*);

     /// @brief Действие при нажатии кнопки мыши
     virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

     /// @brief Действие при отпускании кнопки мыши
     virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

};

#endif // FSMITEM_H
