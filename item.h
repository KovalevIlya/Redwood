#ifndef ITEM_H
#define ITEM_H

#include <QObject>

/// Предмет
class Item
{
    Q_GADGET
public:
    /// Типы предметов
    enum class TypeItem {
        None = -1, ///< Пустота
        Apple = 0, ///< Яблоко
        Cheese ///< Сыр
    };
    Q_ENUM(TypeItem);

    /// Конструктор по-умолчанию
    /// \note Инициализирует объект Пустотой без иконки
    Item();
    /// Конструктор
    /// \param typeItem Тип предмета
    /// \param iconPath Путь к иконке предмета
    explicit Item(const TypeItem typeItem, const QString &iconPath);
    /// Конструктор
    /// \param typeItem Тип предмета
    /// \param iconPath Путь к иконке предмета
    explicit Item(const TypeItem &&typeItem, const QString &&iconPath);
    /// Конструктор копирования
    /// \param other Копируемый предмет
    Item(const Item &other);
    /// Конструктор перемещения
    /// \param other Перемещаемый предмет
    Item(Item &&other);

    /// Установить тип предмета
    /// \param typeItem Тип предмета
    void setType(const TypeItem typeItem);
    /// Установить тип предмета
    /// \param typeItem Тип предмета
    void setType(const TypeItem &&typeItem);
    /// Получить тип предмета
    /// \return Тип предмета
    TypeItem type() const;
    /// Получить название предмета
    /// \return Название предмета
    QString typeName() const;

    /// Установить путь до иконки
    /// \param iconPath Путь до иконки
    void setIconPath(const QString &iconPath);
    /// Установить путь до иконки
    /// \param iconPath Путь до иконки
    void setIconPath(const QString &&iconPath);
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
    TypeItem _typeItem; ///< Тип предмета
    QString _iconPath; ///< Путь до иконки

    static const QHash<TypeItem, QString> _typeNames; ///< Хэш таблица названий предметов

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
