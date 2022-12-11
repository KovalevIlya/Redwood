#include "database.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QFile>

Database::~Database()
{
    QSqlDatabase().close();
}

Database &Database::instance()
{
    static Database instance;
    return instance;
}

Item Database::item(int type) const
{
    QSqlQuery query;
    query.prepare("SELECT * "
                  "FROM item_table "
                  "WHERE \"type\" = :type;");

    query.bindValue(":type", type);
    query.exec();

    if (!query.next())
        return Item();

    return Item(type, query.value(1).toString(), query.value(2).toString());
}

QList<Item> Database::itemList() const
{
    QList<Item> itemsList;

    QSqlQuery query("SELECT * "
                    "FROM item_table "
                    "WHERE \"type\" >= 0;");

    while (query.next()) {
        itemsList.append(Item(query.value(0).toInt(), query.value(1).toString(),
                              query.value(2).toString()));
    }
    return itemsList;
}

void Database::setItems(const int index, const Items &items)
{
    QSqlQuery query;
    query.prepare("INSERT INTO inventory_table (\"index\", item, count) "
                  "VALUES (:index, :item, :count) "
                  "ON CONFLICT(\"index\") DO UPDATE SET "
                  "item = :item, "
                  "count = :count;");

    query.bindValue(":index", index);
    query.bindValue(":item", items.item.type());
    query.bindValue(":count", items.count);
    query.exec();
}

Items Database::items(const int index) const
{
    QSqlQuery query;
    query.prepare("SELECT * "
                  "FROM inventory_table "
                  "WHERE \"index\" = :index;");

    query.bindValue(":index", index);
    query.exec();

    if (!query.next())
        return Items();

    return Items(item(query.value(1).toInt()), query.value(2).toInt());
}

void Database::resetItems()
{
    QSqlQuery("DELETE FROM inventory_table;");
}

QList<Items> Database::itemsList() const
{
    QList<Items> itemsList;

    QSqlQuery query("SELECT * "
                    "FROM inventory_table;");

    int index = -1;
    while (query.next()) {
        while (++index != query.value(0).toInt()) {
            itemsList.append(Items());
        }
        itemsList.append(Items(item(query.value(1).toInt()), query.value(2).toInt()));
    }
    return itemsList;
}

Database::Database()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./database.db");

    if (QFile::exists("./database.db")) {
        db.open();
        return;
    }

    if (db.open()) {
        QSqlQuery("CREATE TABLE item_table ("
                  "\"type\" INTEGER PRIMARY KEY, "
                  "path_icon TEXT, "
                  "ru_name TEXT);");

        QSqlQuery("CREATE TABLE inventory_table ("
                  "\"index\" INTEGER PRIMARY KEY, "
                  "item INTEGER DEFAULT (0), "
                  "count INTEGER DEFAULT (0), "
                  "CONSTRAINT inventory_table_FK FOREIGN KEY (item) "
                  "REFERENCES item_table(\"type\") "
                  "ON DELETE CASCADE ON UPDATE CASCADE);");

        QSqlQuery query;
        query.prepare("INSERT INTO item_table (\"type\", path_icon, ru_name) "
                      "VALUES (:type, :path_icon, :ru_name);");

        query.bindValue(":type", -1);
        query.bindValue(":path_icon", "");
        query.bindValue(":ru_name", "");
        query.exec();

        query.bindValue(":type", 0);
        query.bindValue(":path_icon", ":/resourses/resourses/apple.png");
        query.bindValue(":ru_name", "Яблоко");
        query.exec();

//        query.bindValue(":type", 1);
//        query.bindValue(":path_icon", ":/resourses/resourses/cheese.png");
//        query.bindValue(":ru_name", "Сыр");
//        query.exec();
    }
}
