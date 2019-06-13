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
     ///        Вызывает формирование связей
     ///        Которые вызывают формирование автоматов
     void formComposition();

     int type() const;

     Composition getComposition() const;

     // Добавляет контекстное меню, позволяющее сформировать связь
     void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

     #ifdef QT_DEBUG
     // Выводит в qDebug() автоматы и связи, входящие в композицию
     void printFsmsAndLinks();
#endif //QT_DEBUG
};

#endif // COMPOSITIONITEM_H
