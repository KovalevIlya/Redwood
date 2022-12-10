#ifndef SPAWNERMODEL_H
#define SPAWNERMODEL_H

#include "item.h"

#include <QAbstractListModel>

/// Модель источника
class SpawnerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param rowCount Количество строк
    /// \param parent Родительский объект
    explicit SpawnerModel(const uint rowCount, QObject *parent = nullptr);

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
    /// Получить количество столбцов
    /// \param parent Индекс, для которого требуется получить количество столбцов
    /// \return Количество столбцов
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
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

private:
    const uint _rowCount; ///< Количество строк
    QVector<Item> _items; ///< Предметы
};

#endif // SPAWNERMODEL_H
