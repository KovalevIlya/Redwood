#include "mainmenu.h"
#include "menuwidget.h"
#include "playingfieldwindow.h"
#include "../database.h"

#include <QVBoxLayout>
#include <QPushButton>

MainMenu::MainMenu() : QMainWindow()
{
    setWindowTitle(tr("Главное меню"));
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    setFixedSize(200, 100);

    const auto menu = new MenuWidget(tr("Новая игра"));

    connect(menu, &MenuWidget::start, this, [this](){
        Database::instance().resetItems();

        const auto playingField = new PlayingFieldWindow();
        connect(playingField, &PlayingFieldWindow::destroyed, this, &MainMenu::deleteLater);

        playingField->show();

        close();
    });

    connect(menu, &MenuWidget::exit, this, &MainMenu::close);

    setCentralWidget(menu);
}
