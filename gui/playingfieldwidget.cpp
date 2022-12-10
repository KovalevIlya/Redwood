#include "playingfieldwidget.h"
#include "inventoryitemdelegate.h"

#include "../inventorymodel.h"
#include "../spawnermodel.h"
#include "../inventory.h"
#include "../item.h"
#include "../roles.h"

#include <QLayout>
#include <QTableWidget>
#include <QListWidget>
#include <QHeaderView>

#include <QItemDelegate>

constexpr int sizeItem = 100;
constexpr int rowCount = 3;
constexpr int columnCount = 3;
constexpr int itemsCount = 1;

constexpr int  borderTopWidth = 10;
constexpr int  borderRightWidth = 13;
constexpr int  borderBottomWidth = 10;
constexpr int  borderLeftWidth = 14;


PlayingFieldWidget::PlayingFieldWidget(QWidget *parent)
    : QWidget(parent)
{
    const auto lay = new QHBoxLayout(this);
    lay->addWidget(makeInventory());
    lay->addSpacing(50);
    lay->addWidget(makeSpawner());
}

void PlayingFieldWidget::reset()
{
    _inventoryModel->reset();
}

QWidget *PlayingFieldWidget::makeInventory()
{
    const auto inventory = new QTableView();
    _inventoryModel = new InventoryModel(new Inventory(rowCount, columnCount), this);
    inventory->setModel(_inventoryModel);

    const int width = columnCount * sizeItem + borderRightWidth + borderLeftWidth;
    const int height = rowCount * sizeItem + borderTopWidth + borderBottomWidth;

    inventory->setFixedSize(width, height);

    inventory->setIconSize(QSize(sizeItem, sizeItem));
    inventory->setCornerButtonEnabled(false);
    inventory->verticalHeader()->hide();
    inventory->horizontalHeader()->hide();

    inventory->setDragEnabled(true);
    inventory->setAcceptDrops(true);
    inventory->setDefaultDropAction(Qt::MoveAction);

    static const auto style = QString("background: url(:/resourses/resourses/inventory.png);"
                                      "selection-background-color: rgba(0, 0, 255, 100%);"
                                      "gridline-color: rgba(0, 0, 0, 0%);"
                                      "border-top-width: %1px;"
                                      "border-right-width: %2px;"
                                      "border-bottom-width: %3px;"
                                      "border-left-width: %4px;"
                                      "border-image: url(:/resourses/resourses/border.png) stretch;")
            .arg(borderTopWidth).arg(borderRightWidth).arg(borderBottomWidth).arg(borderLeftWidth);
    inventory->setStyleSheet(style);


    inventory->setSelectionMode(QAbstractItemView::SingleSelection);

    inventory->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    inventory->verticalHeader()->setMinimumSectionSize(sizeItem);
    inventory->verticalHeader()->setMaximumSectionSize(sizeItem);
    inventory->verticalHeader()->setDefaultSectionSize(sizeItem);
    inventory->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    inventory->horizontalHeader()->setMinimumSectionSize(sizeItem);
    inventory->horizontalHeader()->setMaximumSectionSize(sizeItem);
    inventory->horizontalHeader()->setDefaultSectionSize(sizeItem);

    inventory->setItemDelegate(new InventoryItemDelegate());

    return inventory;
}

QWidget *PlayingFieldWidget::makeSpawner()
{
    const auto items = new QListView();
    const auto model = new SpawnerModel(2);
    items->setModel(model);
    items->setViewMode(QListView::IconMode);
    items->setIconSize(QSize(sizeItem, sizeItem));
    items->setSpacing(10);
    items->setAcceptDrops(false);
    items->setWrapping(false);

    model->setData(model->index(0), QVariant::fromValue(Item(Item::TypeItem::Apple,
                                                             ":/resourses/resourses/apple.png")),
                   Roles::InventoryRoles::ItemRole);
    model->setData(model->index(1), QVariant::fromValue(Item(Item::TypeItem::Cheese,
                                                             ":/resourses/resourses/cheese.png")),
                   Roles::InventoryRoles::ItemRole);

    return items;
}
