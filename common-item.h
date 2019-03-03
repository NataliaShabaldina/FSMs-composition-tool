#ifndef COMMONITEM_H
#define COMMONITEM_H

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QApplication>
#include <QGraphicsSceneContextMenuEvent>

/// @brief Класс-прокладка для уменьшения дублирования кода в item-ах
class CommonItem : public QGraphicsItem
{
protected:
     // Используется для нумерации автоматов
     // Увеличивается в конструкторе
     static int itemNumber;

     /// Конструктор спрятан, чтобы слечайно не создавать экземпляров
     CommonItem(QGraphicsItem* parent = nullptr);

     /// @brief Действие при нажатии кнопки мыши
     virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

     /// @brief Действие при отпускании кнопки мыши
     virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

     /// @brief Обработка нажатий клавиш (Delete)
     virtual void keyPressEvent(QKeyEvent* event);

     /// @brief Контекстное меню - для всех элементов содержит удаление
     virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

     /// @brief Удаляет элемент со сцены
     void removeItem();
};

#endif // COMMONITEM_H
