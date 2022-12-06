#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"

#include <QObject>

/// Инвентарь
class Inventory : public QObject
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param rowCount Количество строк
    /// \param columnCount Количество столбцов
    /// \param parent Родительский объект
    explicit Inventory(const uint rowCount, const uint columnCount, QObject *parent = nullptr);

    /// Установить предмет
    /// \param row Строка
    /// \param column Столбец
    /// \param item Предмет
    /// \param count Количество предметов
    /// \return Успех операции
    Q_SLOT bool setItem(uint row, uint column, Item item, uint count = 0);
    /// Можно ли добавить предмет
    /// \param row Строка
    /// \param column Столбец
    /// \param item Предмет
    /// \return Можно ли добавить предмет
    bool isAddItem(uint row, uint column, Item item) const;
    /// Добавить предмет
    /// \param row Строка
    /// \param column Столбец
    /// \param item Предмет
    /// \param count Количество
    /// \return Успех операции
    Q_SLOT bool addItem(uint row, uint column, Item item, uint count = 0);
    /// Получить предмет и его количество
    /// \param row Строка
    /// \param column Стобец
    /// \return Предмет и его количество
    QPair<Item, uint> itemThisCount(uint row, uint column) const;
    /// Получить предмет
    /// \param row Строка
    /// \param column Столбец
    /// \return Предмет
    Item item(uint row, uint column) const;
    /// Получить количество предметов
    /// \param row Строка
    /// \param column Столбец
    /// \return Количество предметов
    uint countItem(uint row, uint column) const;
    /// Сигнал об изменении предмета
    /// \param row Строка
    /// \param column Столбец
    /// \param item Предмет
    /// \param count Количество предметов
    Q_SIGNAL void itemChanged(uint row, uint column, Item item, uint count) const;

    /// Получить количество строк
    /// \return Количество строк
    int rowCount() const;
    /// Получить количество столбцов
    /// \return Количество столбцов
    int columnCount() const;

private:
    /// Коректен ли индекс предмета
    /// \param row Строка
    /// \param column Столбец
    /// \return Коректен ли индекс предмета
    bool isValidIndex(uint row, uint column) const;

    const uint _rowCount; ///< Количество строк
    const uint _columnCount; ///< Количество столбцов

    QVector<QVector<QPair<Item, uint>>> _items; ///< Таблица предметов
};

#endif // INVENTORY_H
