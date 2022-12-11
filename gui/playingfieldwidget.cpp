#include "playingfieldwidget.h"
#include "inventoriview.h"

#include "../inventorymodel.h"
#include "../spawnermodel.h"
#include "../inventory.h"
#include "../item.h"
#include "../global.h"
#include "../database.h"

#include <QLayout>
#include <QTableWidget>
#include <QListWidget>
#include <QHeaderView>
#include <QItemDelegate>

constexpr int rowCount = 3;
constexpr int columnCount = 3;

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
    const auto itemList = Database::instance().itemList();

    const auto items = new QListView();
    const auto model = new SpawnerModel(itemList.count());
    items->setModel(model);
    items->setViewMode(QListView::IconMode);
    items->setIconSize(QSize(Specification::sizeItem, Specification::sizeItem));
    items->setSpacing(10);
    items->setAcceptDrops(false);
    items->setWrapping(false);

    int idndex = 0;
    for (const auto &item : itemList) {
        model->setData(model->index(idndex++), QVariant::fromValue(item),
                       Roles::InventoryRoles::ItemRole);
    }

    return items;
}
