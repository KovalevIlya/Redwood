#include "inventoriview.h"
#include "inventoryitemdelegate.h"
#include "../inventory.h"
#include "../roles.h"

#include <QMouseEvent>
#include <QHeaderView>
#include <QSound>

constexpr int sizeItem = 100;
constexpr int borderTopWidth = 10;
constexpr int borderRightWidth = 13;
constexpr int borderBottomWidth = 10;
constexpr int borderLeftWidth = 14;

InventoriView::InventoriView(QWidget *parent) : QTableView(parent)
{
    const int width = 3 * sizeItem + borderRightWidth + borderLeftWidth;
    const int height = 3 * sizeItem + borderTopWidth + borderBottomWidth;

    setFixedSize(width, height);

    setIconSize(QSize(sizeItem, sizeItem));
    setCornerButtonEnabled(false);
    verticalHeader()->hide();
    horizontalHeader()->hide();

    setDragEnabled(true);
    setAcceptDrops(true);
    setDefaultDropAction(Qt::MoveAction);

    static const auto style = QString("background: url(:/resourses/resourses/inventory.png);"
                                      "selection-background-color: rgba(0, 0, 255, 100%);"
                                      "gridline-color: rgba(0, 0, 0, 0%);"
                                      "border-top-width: %1px;"
                                      "border-right-width: %2px;"
                                      "border-bottom-width: %3px;"
                                      "border-left-width: %4px;"
                                      "border-image: url(:/resourses/resourses/border.png) stretch;")
            .arg(borderTopWidth).arg(borderRightWidth).arg(borderBottomWidth).arg(borderLeftWidth);
    setStyleSheet(style);

    setSelectionMode(QAbstractItemView::SingleSelection);

    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setMinimumSectionSize(sizeItem);
    verticalHeader()->setMaximumSectionSize(sizeItem);
    verticalHeader()->setDefaultSectionSize(sizeItem);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    horizontalHeader()->setMinimumSectionSize(sizeItem);
    horizontalHeader()->setMaximumSectionSize(sizeItem);
    horizontalHeader()->setDefaultSectionSize(sizeItem);

    setItemDelegate(new InventoryItemDelegate);
}

void InventoriView::mouseReleaseEvent (QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        const auto index = currentIndex();
        auto items = model()->data(index, Roles::InventoryRoles::ItemsRole).value<Items>();

        if (items.count > 0) {
            QSound::play(":/resourses/resourses/eat.wav");
            items.count = -1;
            model()->setData(index, QVariant::fromValue(items), Roles::InventoryRoles::AddItemsRole);
        }
    }

    QTableView::mouseReleaseEvent (event);
}