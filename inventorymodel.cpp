#include "inventorymodel.h"
#include "inventory.h"
#include "item.h"
#include "database.h"
#include "global.h"

#include <QIcon>
#include <QMimeData>
#include <QDataStream>

InventoryModel::InventoryModel(Inventory *inventory, QObject *parent)
    : QAbstractItemModel(parent), _inventory(inventory)
{
    _inventory->setParent(this);

    connect(this, &InventoryModel::dataChanged,
            this, [this](const QModelIndex &topLeft, const QModelIndex &bottomRight,
                         const QVector<int> &roles){
        if (!roles.contains(Roles::InventoryRoles::ItemsRole))
            return;

        int row = topLeft.row();
        int column = topLeft.column();

        const int endRow = bottomRight.row();
        const int endColumn = bottomRight.column();

        const int columnCount = this->columnCount();

        while (row <= endRow) {
            const auto items = data(index(row, column),
                                    Roles::InventoryRoles::ItemsRole).value<Items>();
            Database::instance().setItems(row * columnCount + column, items);

            ++column;
            if (column > endColumn) {
                ++row;
                column = topLeft.column();
            }
        }
    });
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
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    if (indexes.count() != 1)
        return nullptr;

    const auto index = indexes[0];

    if (!index.isValid())
        return nullptr;

    Items items = data(index, Roles::InventoryRoles::ItemsRole).value<Items>();
    stream << items.item.type() << items.item.iconPath() << items.item.name() << items.count;

    QMimeData *mimeData = new QMimeData();
    mimeData->setData("text/plane/items", encodedData);
    return mimeData;
}

bool InventoryModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                                  const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (!parent.isValid())
        return false;

    row = parent.row();
    column = parent.column();

    const auto editItems = [this, &row, &column](const Items &&newItems) {

        const auto index = this->index(row, column);

        const Items oldItems = this->data(index, Roles::InventoryRoles::ItemsRole).value<Items>();

        if (newItems.item != oldItems.item) {
            if (oldItems.item == Item() || oldItems.count == 0)
                setData(index, QVariant::fromValue(newItems), Roles::InventoryRoles::ItemsRole);
            else
                return false;
        } else {
            setData(index, QVariant::fromValue(newItems), Roles::InventoryRoles::AddItemsRole);
        }
        return true;
    };

    if (data->hasFormat("text/plane/items")) {
        QByteArray encodedData = data->data("text/plane/items");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        if (!stream.atEnd()) {
            int typeItem;
            QString iconPath;
            QString name;
            int count;

            stream >> typeItem >> iconPath >> name >> count;

            return editItems(Items(Item(typeItem, iconPath, name), count));
        }
    } else if (data->hasFormat("text/plane/item")) {
        QByteArray encodedData = data->data("text/plane/item");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        if (!stream.atEnd()) {
            int typeItem;
            QString iconPath;
            QString name;

            stream >> typeItem >> iconPath >> name;

            return editItems(Items(Item(typeItem, iconPath, name), 1));
        }
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
        roles.append(Roles::InventoryRoles::ItemsRole);
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

QMap<int, QVariant> InventoryModel::itemData(const QModelIndex &index) const
{
    return {{ Roles::ItemsRole, data(index, Roles::ItemsRole) }};
}

void InventoryModel::reset()
{
    beginResetModel();

    _inventory->reset();

    endResetModel();
}
