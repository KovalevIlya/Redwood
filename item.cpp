#include "item.h"

#include <QIcon>
#include <QHash>

inline uint qHash(const Item::TypeItem &tag) {
    return qHash(static_cast<int>(tag));
}

const QHash<Item::TypeItem, QString> Item::_typeNames = {
    { Item::TypeItem::None, QT_TRANSLATE_NOOP(Item::TypeItem, "Пустота") },
    { Item::TypeItem::Apple, QT_TRANSLATE_NOOP(Item::TypeItem, "Яблоко") },
};

Item::Item()
    : Item(TypeItem::None, "")
{

}

Item::Item(const TypeItem typeItem, const QString &iconPath)
    : _typeItem(typeItem), _iconPath(iconPath)
{

}

Item::Item(const TypeItem &&typeItem, const QString &&iconPath)
    : _typeItem(std::move(typeItem)), _iconPath(std::move(iconPath))
{

}

Item::Item(const Item &other)
{
    _typeItem = other._typeItem;
    _iconPath = other._iconPath;
}

Item::Item(Item &&other)
{
    _typeItem = std::move(other._typeItem);
    _iconPath = std::move(other._iconPath);
}

void Item::setType(const TypeItem typeItem)
{
    _typeItem = typeItem;
}

void Item::setType(const TypeItem &&typeItem)
{
    _typeItem = std::move(typeItem);
}

Item::TypeItem Item::type() const
{
    return _typeItem;
}

QString Item::typeName() const
{
    return _typeNames.value(_typeItem);
}

void Item::setIconPath(const QString &iconPath)
{
    _iconPath = iconPath;
}

void Item::setIconPath(const QString &&iconPath)
{
    _iconPath = std::move(iconPath);
}

QString Item::iconPath() const
{
    return _iconPath;
}

QIcon Item::icon() const
{
    return QIcon(_iconPath);
}

Item &Item::operator=(const Item &other)
{
    _typeItem = other._typeItem;
    _iconPath = other._iconPath;
    return *this;
}

Item &Item::operator=(const Item &&other)
{
    _typeItem = std::move(other._typeItem);
    _iconPath = std::move(other._iconPath);
    return *this;
}
