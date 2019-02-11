#ifndef COMMONITEM_H
#define COMMONITEM_H

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>

/// @brief Класс-прокладка для уменьшения дублирования кода в item-ах
class commonItem : public QGraphicsItem
{
private:

protected:
     // Используется для нумерации автоматов
     // Увеличивается в конструкторе
     static int itemNumber;

     /// Конструктор спрятан, чтобы слечайно не создавать экземпляров
     commonItem(QGraphicsItem* parent = nullptr);

public:
     /// @brief Действие при нажатии кнопки мыши
     virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

     /// @brief Действие при отпускании кнопки мыши
     virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

     /// @brief Обработка нажатий клавиш (Delete)
     virtual void keyPressEvent(QKeyEvent* event);
};

#endif // COMMONITEM_H
