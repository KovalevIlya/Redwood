#ifndef INVENTORYITEMDELEGATE_H
#define INVENTORYITEMDELEGATE_H

#include <QStyledItemDelegate>

/// Делегат инвентаря
class InventoryItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param parent Родительский объект
    explicit InventoryItemDelegate(QObject *parent = nullptr);
    /// Отрисока делегата
    /// \param painter Объект отрисовки
    /// \param option Параметры силя
    /// \param index Индекс
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
protected:
    /// Событие редактирования
    /// \return Успех обработки события
    bool editorEvent(QEvent *, QAbstractItemModel *, const QStyleOptionViewItem &,
                     const QModelIndex &) override;
};

#endif // INVENTORYITEMDELEGATE_H
