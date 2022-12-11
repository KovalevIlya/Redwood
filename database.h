#ifndef DATABASE_H
#define DATABASE_H

#include "item.h"
#include "inventory.h"

/// База данных
class Database
{
public:
    /// Деструктор
    ~Database();
    /// Получить объект класса
    /// \return Объект класса
    static Database &instance();

    /// Получить предмет
    /// \param type Тип предмета
    /// \return Предмет
    Item item(int type) const;
    /// Получить список предметов
    /// \note Список содержит одиночные предметы (Item)
    /// \return Список предметов
    QList<Item> itemList() const;

    /// Установить предметы в инвентаре
    /// \param index Индекс предметов
    /// \param items Предметы
    void setItems(const int index, const Items& items);
    /// Получить предметы из инвентаря
    /// \param index Индекс предметов
    /// \return Предметы
    Items items(const int index) const;
    /// Сбросить предметы в инвентаре
    void resetItems();
    /// Получить список предметов инвентаря
    /// \note Список содержит предметы с количеством в инвентаре (Items)
    /// \return Список предметов
    QList<Items> itemsList() const;

private:
    /// Конструктор
    explicit Database();
};

#endif // DATABASE_H
