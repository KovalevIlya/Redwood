#include "inventory.h"

Inventory::Inventory(const uint rowCount, const uint columnCount, QObject *parent)
    : QObject(parent), _rowCount(rowCount), _columnCount(columnCount)
{
    const auto item = QPair<Item, uint>(Item(), 0);
    _items = QVector<QVector<QPair<Item, uint>>>(_rowCount,
                                                 QVector<QPair<Item, uint>>(_columnCount, item));
}

bool Inventory::setItem(uint row, uint column, Item item, uint count)
{
    if (!isValidIndex(row, column))
        return false;

    _items[row][column] = QPair<Item, uint>(item, count);
    emit itemChanged(row, column, _items[row][column].first, _items[row][column].second);
    return true;
}

bool Inventory::isAddItem(uint row, uint column, Item item) const
{
    if (!isValidIndex(row, column))
        return false;

    return _items[row][column].first == item;
}

bool Inventory::addItem(uint row, uint column, Item item, uint count)
{
    if (!isAddItem(row, column, item))
        return false;

    _items[row][column].second += count;
    emit itemChanged(row, column, _items[row][column].first, _items[row][column].second);
    return true;
}

QPair<Item, uint> Inventory::itemThisCount(uint row, uint column) const
{
    if (!isValidIndex(row, column))
        return { Item(), 0 };

    return _items[row][column];
}

Item Inventory::item(uint row, uint column) const
{
    if (!isValidIndex(row, column))
        return Item();

    return _items[row][column].first;
}

uint Inventory::countItem(uint row, uint column) const
{
    if (!isValidIndex(row, column))
        return 0;

    return _items[row][column].second;
}

int Inventory::rowCount() const
{
    return _rowCount;
}

int Inventory::columnCount() const
{
    return _columnCount;
}

bool Inventory::isValidIndex(uint row, uint column) const
{
    return row < _rowCount && column < _columnCount;
}
