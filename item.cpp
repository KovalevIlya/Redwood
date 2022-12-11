#include "item.h"

#include <QIcon>

Item::Item() : Item(-1, "", "")
{

}

Item::Item(const int typeItem, const QString &iconPath, const QString &name)
    : _typeItem(typeItem), _iconPath(iconPath), _name(name)
{

}

Item::Item(const int typeItem, const QString &&iconPath, const QString &&name)
    : _typeItem(typeItem), _iconPath(std::move(iconPath)), _name(std::move(name))
{

}

Item::Item(const Item &other)
    : _typeItem(other._typeItem), _iconPath(other._iconPath), _name(other._name)
{

}

Item::Item(Item &&other)
    : _typeItem(std::move(other._typeItem)), _iconPath(std::move(other._iconPath)),
      _name(std::move(other._name))
{

}

int Item::type() const
{
    return _typeItem;
}

QString Item::name() const
{
    return _name;
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
    _name = other._name;
    return *this;
}

Item &Item::operator=(const Item &&other)
{
    _typeItem = std::move(other._typeItem);
    _iconPath = std::move(other._iconPath);
    _name = std::move(other._name);
    return *this;
}
