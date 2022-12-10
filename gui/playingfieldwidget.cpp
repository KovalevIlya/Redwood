#include "playingfieldwidget.h"
#include "inventoriview.h"

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
constexpr int itemsCount = 2;

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
    const auto inventory = new InventoriView;
    _inventoryModel = new InventoryModel(new Inventory(rowCount, columnCount), this);
    inventory->setModel(_inventoryModel);

    return inventory;
}

QWidget *PlayingFieldWidget::makeSpawner()
{
    const auto items = new QListView();
    const auto model = new SpawnerModel(itemsCount);
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
