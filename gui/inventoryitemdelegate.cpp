#include "inventoryitemdelegate.h"

#include <QApplication>
#include <QPainter>
#include <QDebug>

InventoryItemDelegate::InventoryItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

//QWidget *ItemDelegate::createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
//{
//    return nullptr;
//}l

void InventoryItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const
{
    bool ok;
    const int countItems = index.model()->data(index, Qt::DisplayRole).toInt(&ok);

    if (!ok || countItems < 1)
        return;

    const QRect rect = option.rect;

    const QIcon icon = index.model()->data(index, Qt::DecorationRole).value<QIcon>();
    const QPixmap pixmap = icon.pixmap(QSize(rect.width(), rect.height()));

    const QString text = index.model()->data(index, Qt::DisplayRole).toString();
    const int textWidth = painter->fontMetrics().horizontalAdvance(text);
    const int textHeight = painter->fontMetrics().height();
    const QPoint textBottomRight(rect.bottomRight().x() - 5, rect.bottomRight().y() - 5);
    const QPoint textTopLeft(textBottomRight.x() - textWidth, textBottomRight.y() - textHeight);
    const QRect textRect(textTopLeft, textBottomRight);

    painter->save();

    painter->drawPixmap(rect.topLeft(), pixmap);
    painter->drawText(textRect, text);

    painter->restore();
}

bool InventoryItemDelegate::editorEvent(QEvent *, QAbstractItemModel *, const QStyleOptionViewItem &, const QModelIndex &)
{
    return false;
}
