#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>

namespace Specification {
Q_NAMESPACE

constexpr int sizeItem = 100; ///< Графический размер элемента

} // end namespace Specification

namespace Roles
{
Q_NAMESPACE

/// Роли инвенатаря
enum InventoryRoles {
    ItemsRole = Qt::UserRole + 1, ///< Роль для предметов
    AddItemsRole, ///< Роль для добавления предметов
    ItemRole ///< Роль для предмета
};
Q_ENUM_NS(InventoryRoles)
} // end namespace Roles

#endif // GLOBAL_H
