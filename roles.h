#ifndef ROLES_H
#define ROLES_H

#include <QObject>

namespace Roles
{
Q_NAMESPACE

/// Роли инвенатаря
enum InventoryRoles {
    ItemsRole = Qt::UserRole + 1, ///< Роль для предметов
    AddItemsRole, ///< Роль для добавления предметов
    ItemRole ///< Роль для предмета
};
Q_ENUM_NS(InventoryRoles);
}

#endif // ROLES_H
