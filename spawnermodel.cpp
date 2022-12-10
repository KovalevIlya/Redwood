#include "spawnermodel.h"
#include "roles.h"

#include <QIcon>
#include <QMimeData>
#include <QDataStream>

SpawnerModel::SpawnerModel(const uint rowCount, QObject *parent)
    : QAbstractListModel(parent), _rowCount(rowCount)
{
    _items.resize(rowCount);
}

Qt::ItemFlags SpawnerModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | defaultFlags;

    return defaultFlags;
}

Qt::DropActions SpawnerModel::supportedDropActions() const
{
    return Qt::CopyAction;
}

QStringList SpawnerModel::mimeTypes() const
{
    QStringList types;
    types << "text/plane/item";
    return types;
}

QMimeData *SpawnerModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            Item item = data(index, Roles::InventoryRoles::ItemRole).value<Item>();
            stream << static_cast<int>(item.type())
                   << item.iconPath();
        }
    }

    mimeData->setData("text/plane/item", encodedData);
    return mimeData;
}

int SpawnerModel::rowCount(const QModelIndex &) const
{
    return _rowCount;
}

QVariant SpawnerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant data;
    switch (role) {
    case Qt::DisplayRole:
        data = _items[index.row()].typeName();
        break;
    case Qt::DecorationRole:
        data = _items[index.row()].icon();
        break;
    case Roles::InventoryRoles::ItemRole:
        data = QVariant::fromValue(_items[index.row()]);
        break;
    default:
        return QVariant();
    }

    return data;
}

bool SpawnerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    const int row = index.row();

    QVector<int> roles;
    switch (role) {
    case Roles::InventoryRoles::ItemRole:
        _items[row] = value.value<Item>();
        roles.append(Qt::DisplayRole);
        roles.append(Qt::DecorationRole);
        break;
    default:
        return false;
    }

    roles.append(role);

    emit dataChanged(index, index, roles);

    return true;
}
