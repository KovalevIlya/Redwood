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
    const auto layRight = new QVBoxLayout();
    layRight->addStretch();
    layRight->addWidget(makeSpawner());

    const auto lay = new QHBoxLayout(this);
    lay->addWidget(makeInventory());
    lay->addSpacing(50);
    lay->addLayout(layRight);
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

    const auto spawner = new QListView();

    const auto model = new SpawnerModel(itemList.count());
    spawner->setModel(model);

    spawner->setViewMode(QListView::IconMode);
    spawner->setIconSize(QSize(Specification::sizeItem, Specification::sizeItem));
    spawner->setSpacing(0);
    spawner->setAcceptDrops(false);
    spawner->setWrapping(false);

    spawner->setFixedHeight(Specification::sizeItem + 24);
    spawner->setFixedWidth(itemList.count() * Specification::sizeItem + 16);

    static const auto style = "background-color: rgba(0, 0, 0, 0%);"
                              "border-style: none;"
                              "font: bold 14px;";
    spawner->setStyleSheet(style);

    int idndex = 0;
    for (const auto &item : itemList) {
        model->setData(model->index(idndex++), QVariant::fromValue(item),
                       Roles::InventoryRoles::ItemRole);
    }

    return spawner;
}
