#ifndef FSMITEM_H
#define FSMITEM_H

#include "common-item.h"

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QFile>
#include <QApplication>
#include <QMenu>

class fsmItem : public commonItem
{
private:
     // Используется для нумерации автоматов
     // Увеличивается в конструкторе
     static int fsmNumber;

     QFile file_;

     int number_;
     QGraphicsTextItem* nameItem_;

private:
     QString getName() const;

protected:
     /// @brief Определяет невидимые элементы и неприкрытые области, которые должны быть отрисованы стр. 324
     virtual QRectF boundingRect() const;

     /// @brief Отвечает за отображение элемента
     virtual void paint(QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget*);

     /// @brief Конекстное меню для автомата содержит также прикрепление файла
     virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

public:
     fsmItem(QGraphicsItem* parent = nullptr);
     ~fsmItem();

     void onAttachFile();
};

#endif // FSMITEM_H
