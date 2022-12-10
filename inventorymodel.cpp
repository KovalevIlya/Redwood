#include "inventorymodel.h"
#include "inventory.h"
#include "item.h"
#include "roles.h"

#include <QIcon>
#include <QMimeData>
#include <QDataStream>

InventoryModel::InventoryModel(Inventory *inventory, QObject *parent)
    : QAbstractItemModel(parent), _inventory(inventory)
{
    _inventory->setParent(this);
}

Qt::ItemFlags InventoryModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid()) {
        if (!_inventory->isEmpty(index.row(), index.column()))
            return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
        else
            return Qt::ItemIsDropEnabled | defaultFlags;
    }

    return defaultFlags;
}

Qt::DropActions InventoryModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

QStringList InventoryModel::mimeTypes() const
{
    QStringList types;
    types << "text/plane/items";
    types << "text/plane/item";
    return types;
}

QMimeData *InventoryModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            Items items = data(index, Roles::InventoryRoles::ItemsRole).value<Items>();
            stream << static_cast<int>(items.item.type())
                   << items.item.iconPath()
                   << QString::number(items.count);
        }
    }

    mimeData->setData("text/plane/items", encodedData);
    return mimeData;
}

bool InventoryModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                                  const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (row == -1) {
        if (parent.isValid())
            row = parent.row();
    }
    if (column == -1) {
        if (parent.isValid())
            column = parent.column();
    }

    if (column < 0 || column >= columnCount() || row < 0 || row >= rowCount())
        return false;

    if (data->hasFormat("text/plane/items")) {
        QByteArray encodedData = data->data("text/plane/items");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        while (!stream.atEnd()) {
            int typeItemInt;
            QString iconPath;
            QString countStr;

            stream >> typeItemInt >> iconPath >> countStr;

            const auto index = this->index(row, column++);

            const Items newItems(Item(static_cast<Item::TypeItem>(typeItemInt), iconPath),
                        countStr.toUInt());
            const Items oldItems = this->data(index, Roles::InventoryRoles::ItemsRole).value<Items>();

            if (newItems.item != oldItems.item) {
                if (oldItems.item == Item() || oldItems.count == 0)
                    setData(index, QVariant::fromValue(newItems), Roles::InventoryRoles::ItemsRole);
                else
                    return false;
            } else {
                setData(index, QVariant::fromValue(newItems), Roles::InventoryRoles::AddItemsRole);
            }

            if (column == columnCount()) {
                ++row;
                column = 0;
                if (row == rowCount())
                    return true;
            }
        }

        return true;
    } else if (data->hasFormat("text/plane/item")) {
        QByteArray encodedData = data->data("text/plane/item");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        while (!stream.atEnd()) {
            int typeItemInt;
            QString iconPath;

            stream >> typeItemInt >> iconPath;

            const auto index = this->index(row, column++);

            Items newItems(Item(static_cast<Item::TypeItem>(typeItemInt), iconPath), 1);

            const Items oldItems = this->data(index, Roles::InventoryRoles::ItemsRole).value<Items>();

            if (newItems.item != oldItems.item) {
                if (oldItems.item == Item() || oldItems.count == 0)
                    setData(index, QVariant::fromValue(newItems), Roles::InventoryRoles::ItemsRole);
                else
                    return false;
            } else {
                setData(index, QVariant::fromValue(newItems), Roles::InventoryRoles::AddItemsRole);
            }

            if (column == columnCount()) {
                ++row;
                column = 0;
                if (row == rowCount())
                    return true;
            }
        }

        return true;
    }

    return false;
}

QModelIndex InventoryModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex InventoryModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int InventoryModel::rowCount(const QModelIndex &) const
{
    return _inventory->rowCount();
}

int InventoryModel::columnCount(const QModelIndex &) const
{
    return _inventory->columnCount();
}

QVariant InventoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant data;
    switch (role) {
    case Qt::DisplayRole:
        data = _inventory->countItems(index.row(), index.column());
        break;
    case Qt::DecorationRole:
        data = _inventory->item(index.row(), index.column()).icon();
        break;
    case Roles::InventoryRoles::ItemsRole:
        data = QVariant::fromValue(_inventory->items(index.row(), index.column()));
        break;
    default:
        return QVariant();
    }

    return data;
}

bool InventoryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    const int row = index.row();
    const int column = index.column();

    QVector<int> roles;
    switch (role) {
    case Qt::DisplayRole:
        _inventory->setItem(row, column, _inventory->item(row, column), value.toUInt());
        break;
    case Roles::InventoryRoles::ItemsRole:
        _inventory->setItems(row, column, value.value<Items>());
        roles.append(Qt::DisplayRole);
        roles.append(Qt::DecorationRole);
        break;
    case Roles::InventoryRoles::AddItemsRole: {
        const auto items = value.value<Items>();
        _inventory->addItem(row, column, items.item, items.count);
        roles.append(Qt::DisplayRole);
        roles.append(Qt::DecorationRole);
        break;
    }
    default:
        return false;
    }

    roles.append(role);

    emit dataChanged(index, index, roles);

    return true;
}

void InventoryModel::reset()
{
    beginResetModel();

    _inventory->reset();

    endResetModel();
}
