#ifndef FSMITEM_H
#define FSMITEM_H

#include "common-item.h"
#include "fsm.h"

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QFile>
#include <QApplication>
#include <QMenu>

class FsmItem : public CommonItem
{
private:
     // Используется для нумерации автоматов
     // Увеличивается в конструкторе
     static int fsmNumber;

     /// @brief Используется для задания начального идентификатора автомата
     int number_;
     /// @brief Текстовый итем - отвечает за отображение id_ автомата
     QGraphicsTextItem* idItem_;
     /// @brief Файл прикреплённый к автомату черещ onAtachFile()
     QFile file_;
     /// @brief Соответствующий логический элемент автомата
     Fsm fsm_;
private:
     /// @brief Вызывает диалоговое окно выбора файла и прекрепляет файл к итему
     void onAttachFile();

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
     FsmItem(QGraphicsItem* parent = nullptr);
     ~FsmItem();
     QString getId() const;

     /// @brief Формирует fsm_ поле
     void formFsm();
};

#endif // FSMITEM_H
