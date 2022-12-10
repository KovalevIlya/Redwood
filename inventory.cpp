#include "inventory.h"

Items::Items() : Items(Item())
{

}

Items::Items(const Item &item, const uint count) : item(item), count(count)
{

}

Items::Items(const Item &&item, const uint count) : item(std::move(item)), count(count)
{

}

Inventory::Inventory(const uint rowCount, const uint columnCount, QObject *parent)
    : QObject(parent), _rowCount(rowCount), _columnCount(columnCount)
{
    _items = QVector<QVector<Items>>(_rowCount, QVector<Items>(_columnCount, Items()));
}

bool Inventory::setItem(const uint row, const uint column, const Item item, const uint count)
{
    if (!isValidIndex(row, column))
        return false;

    _items[row][column] = Items(item, count);
    emit itemsChanged(row, column, _items[row][column].item, _items[row][column].count);
    return true;
}

bool Inventory::setItems(const uint row, const uint column, const Items items)
{
    if (!isValidIndex(row, column))
        return false;

    _items[row][column] = items;
    emit itemsChanged(row, column, _items[row][column].item, _items[row][column].count);
    return true;
}

bool Inventory::isAddItem(const uint row, const uint column, const Item item) const
{
    if (!isValidIndex(row, column))
        return false;

    return _items[row][column].item == item;
}

bool Inventory::addItem(const uint row, const uint column, const Item item, const uint count)
{
    if (!isAddItem(row, column, item))
        return false;

    _items[row][column].count += count;
    emit itemsChanged(row, column, _items[row][column].item, _items[row][column].count);
    return true;
}

Items Inventory::items(const uint row, const uint column) const
{
    if (!isValidIndex(row, column))
        return Items();

    return _items[row][column];
}

Item Inventory::item(const uint row, const uint column) const
{
    if (!isValidIndex(row, column))
        return Item();

    return _items[row][column].item;
}

uint Inventory::countItems(const uint row, const uint column) const
{
    if (!isValidIndex(row, column))
        return 0;

    return _items[row][column].count;
}

bool Inventory::isEmpty(const uint row, const uint column) const
{
    return _items[row][column].count == 0;
}

int Inventory::rowCount() const
{
    return _rowCount;
}

int Inventory::columnCount() const
{
    return _columnCount;
}

void Inventory::reset()
{
    for (uint row = 0; row < _rowCount; ++row) {
        for (uint column = 0; column < _columnCount; ++column) {
            _items[row][column] = Items();
            emit itemsChanged(row, column, _items[row][column].item, _items[row][column].count);
        }
    }
}

bool Inventory::isValidIndex(const uint row, const uint column) const
{
    return row < _rowCount && column < _columnCount;
}
