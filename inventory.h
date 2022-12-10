#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"

#include <QObject>

/// Структура предметов
struct Items {
    /// Конструктор по-умолчанию
    Items();
    /// Конструктор
    /// \param item Предмет
    /// \param count Количество
    explicit Items(const Item &item, const int count = 0);
    /// Конструктор
    /// \param item Предмет
    /// \param count Количество
    explicit Items(const Item &&item, const int count = 0);

    Item item; ///< Предмет
    int count; ///< Количество
};
Q_DECLARE_METATYPE(Items)

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
    Q_SLOT bool setItem(const uint row, const uint column, const Item item, const int count = 1);
    /// Установить предметы
    /// \param row Строка
    /// \param column Столбец
    /// \param items Предметы
    /// \return Успех операции
    Q_SLOT bool setItems(const uint row, const uint column, const Items items);
    /// Можно ли добавить предмет
    /// \param row Строка
    /// \param column Столбец
    /// \param item Предмет
    /// \return Можно ли добавить предмет
    bool isAddItem(const uint row, const uint column, const Item item) const;
    /// Добавить предмет
    /// \param row Строка
    /// \param column Столбец
    /// \param item Предмет
    /// \param count Количество
    /// \return Успех операции
    Q_SLOT bool addItem(const uint row, const uint column, const Item item, const int count = 0);
    /// Получить предмет и его количество
    /// \param row Строка
    /// \param column Стобец
    /// \return Предмет и его количество
    Items items(const uint row, const uint column) const;
    /// Получить предмет
    /// \param row Строка
    /// \param column Столбец
    /// \return Предмет
    Item item(const uint row, const uint column) const;
    /// Получить количество предметов
    /// \param row Строка
    /// \param column Столбец
    /// \return Количество предметов
    uint countItems(const uint row, const uint column) const;
    /// Пустой ли предмет
    /// \param row Строка
    /// \param column Столбец
    /// \return Пустой ли предмет
    bool isEmpty(const uint row, const uint column) const;
    /// Сигнал об изменении предмета
    /// \param row Строка
    /// \param column Столбец
    /// \param item Предмет
    /// \param count Количество предметов
    Q_SIGNAL void itemsChanged(const uint row, const uint column,
                               const Item item, const int count) const;

    /// Получить количество строк
    /// \return Количество строк
    int rowCount() const;
    /// Получить количество столбцов
    /// \return Количество столбцов
    int columnCount() const;
    /// Сброс инвентаря
    void reset();

private:
    /// Коректен ли индекс предмета
    /// \param row Строка
    /// \param column Столбец
    /// \return Коректен ли индекс предмета
    bool isValidIndex(const uint row, const uint column) const;

    const uint _rowCount; ///< Количество строк
    const uint _columnCount; ///< Количество столбцов

    QVector<QVector<Items>> _items; ///< Таблица предметов
};

#endif // INVENTORY_H
