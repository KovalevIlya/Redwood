#ifndef ITEM_H
#define ITEM_H

#include <QObject>

/// Предмет
class Item
{
    Q_GADGET
public:

    /// Конструктор по-умолчанию
    /// \note Инициализирует пустотой объект без иконки и названия
    Item();
    /// Конструктор
    /// \param typeItem Тип предмета
    /// \param iconPath Путь к иконке предмета
    /// \param name Название предмета
    explicit Item(const int typeItem, const QString &iconPath, const QString &name);
    /// Конструктор
    /// \param typeItem Тип предмета
    /// \param iconPath Путь к иконке предмета
    /// \param name Название предмета
    explicit Item(const int typeItem, const QString &&iconPath, const QString &&name);
    /// Конструктор копирования
    /// \param other Копируемый предмет
    Item(const Item &other);
    /// Конструктор перемещения
    /// \param other Перемещаемый предмет
    Item(Item &&other);

    /// Получить тип предмета
    /// \return Тип предмета
    int type() const;
    /// Получить название предмета
    /// \return Название предмета
    QString name() const;
    /// Получить путь до иконки
    /// \return Путь до иконки
    QString iconPath() const;
    /// Получить иконку
    /// \return Иконка
    QIcon icon() const;

    /// Оператор копирования
    /// \param other Коприруемый предмет
    /// \return Полученный предмет
    Item &operator=(const Item &other);
    /// Оператор перемещения
    /// \param other Перемещаемый предмет
    /// \return Полученный предмет
    Item &operator=(const Item &&other);

private:
    int _typeItem; ///< Тип предмета
    QString _iconPath; ///< Путь до иконки
    QString _name; ///< Название предмета

    /// Оператор сравнения
    /// \param lhs Левый параметр
    /// \param rhs Правый параметр
    /// \return Результат сравнения
    friend inline bool operator==(const Item& lhs, const Item& rhs)
    {
        return lhs._typeItem == rhs._typeItem;
    }
    /// Оператор сравнения
    /// \param lhs Левый параметр
    /// \param rhs Правый параметр
    /// \return Результат сравнения
    friend inline bool operator!=(const Item& lhs, const Item& rhs)
    {
        return !(lhs == rhs);
    }
};
Q_DECLARE_METATYPE(Item)

#endif // ITEM_H
