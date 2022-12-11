#include "inventoriview.h"
#include "inventoryitemdelegate.h"
#include "../inventory.h"
#include "../global.h"

#include <QMouseEvent>
#include <QHeaderView>
#include <QSound>

constexpr int borderTopWidth = 10;
constexpr int borderRightWidth = 13;
constexpr int borderBottomWidth = 10;
constexpr int borderLeftWidth = 14;

InventoriView::InventoriView(QWidget *parent) : QTableView(parent)
{
    const int width = 3 * Specification::sizeItem + borderRightWidth + borderLeftWidth;
    const int height = 3 * Specification::sizeItem + borderTopWidth + borderBottomWidth;

    setFixedSize(width, height);

    setIconSize(QSize(Specification::sizeItem, Specification::sizeItem));
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
    verticalHeader()->setMinimumSectionSize(Specification::sizeItem);
    verticalHeader()->setMaximumSectionSize(Specification::sizeItem);
    verticalHeader()->setDefaultSectionSize(Specification::sizeItem);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    horizontalHeader()->setMinimumSectionSize(Specification::sizeItem);
    horizontalHeader()->setMaximumSectionSize(Specification::sizeItem);
    horizontalHeader()->setDefaultSectionSize(Specification::sizeItem);

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
