#ifndef INVENTORYMODEL_H
#define INVENTORYMODEL_H

#include <QAbstractItemModel>

class Inventory;

/// Модель инвентаря
class InventoryModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param inventory Инвентарь
    /// \param parent Родительский объект
    explicit InventoryModel(Inventory *inventory, QObject *parent = nullptr);

    /// Получение флагов доступных действий для элемента
    /// \param index Индекс
    /// \return Флаги доступных действий для элемента
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    /// Получение флагов доступный действий претаскивания
    /// \return Флаги доступный действий претаскивания
    Qt::DropActions supportedDropActions() const override;
    /// Получение списка доступных MIME типов
    /// \return Список доступных MIME типов
    QStringList mimeTypes() const override;
    /// Получение закодированных в MIME данных
    /// \param indexes Индексы для кодировки
    /// \return Закодированные в MIME данные
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    /// Опускание элемента закодированного в MIME
    /// \param data Данные закодированные в MIME
    /// \param action Действие перетаскивания
    /// \param row Строка
    /// \param column ССтолбец
    /// \param parent Элемент в который происходит перетаскивание
    /// \return Результат операции
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                      const QModelIndex &parent) override;
    /// Получить индекс элемента
    /// \param row Строка
    /// \param column Столбец
    /// \param parent Родительский индекс
    /// \return Индекс элемента
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    /// Получить родительский индекс элемента
    /// \param child Дочерний индекс элемента
    /// \return Родительский индекс элемента
    QModelIndex parent(const QModelIndex &child) const override;
    /// Получить количество строк
    /// \param parent Индекс, для которого требуется получить количество строк
    /// \return Количество строк
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /// Получить количество столбцов
    /// \param parent Индекс, для которого требуется получить количество столбцов
    /// \return Количество столбцов
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    /// Получить данные
    /// \param index Индекс
    /// \param role Роль
    /// \return Данные
    QVariant data(const QModelIndex &index, int role) const override;
    /// Установить данные
    /// \param index Индекс
    /// \param value Данные
    /// \param role Роль
    /// \return Успех операции
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /// Сбросить модель
    Q_SLOT void reset();

private:
    Inventory *_inventory; ///< Инвентарь
};

#endif // INVENTORYMODEL_H
