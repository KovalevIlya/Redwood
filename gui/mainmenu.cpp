#include "mainmenu.h"
#include "menu.h"

#include <QVBoxLayout>
#include <QPushButton>

MainMenu::MainMenu() : QMainWindow()
{
    setWindowTitle(tr("Главное меню"));
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    setFixedSize(200, 100);

    const auto menu = new Menu(tr("Новая игра"));

    connect(menu, &Menu::start, this, [](){});

    connect(menu, &Menu::exit, this, &MainMenu::close);

    setCentralWidget(menu);
}
