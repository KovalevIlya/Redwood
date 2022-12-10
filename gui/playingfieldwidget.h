#ifndef PLAYINGFIELDWIDGET_H
#define PLAYINGFIELDWIDGET_H

#include <QWidget>

class InventoryModel;

/// Виджет игрового поля
class PlayingFieldWidget : public QWidget
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param parent Родительский виджет
    explicit PlayingFieldWidget(QWidget *parent = nullptr);
    /// Перезагрузить игровое поле
    Q_SLOT void reset();

private:
    /// Создание инвентаря
    /// \return Инвентарь
    QWidget *makeInventory();
    /// Создание источника предметов
    /// \return Источник
    QWidget *makeSpawner();

    InventoryModel* _inventoryModel; ///< Модель инвентаря

};

#endif // PLAYINGFIELDWIDGET_H
