#include "playingfieldwindow.h"
#include "playingfieldwidget.h"
#include "menuwidget.h"
#include "../database.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>

PlayingFieldWindow::PlayingFieldWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlag(Qt::Window, true);

    const auto playingFielsWidget = new PlayingFieldWidget;

    const auto btnMenu = new QPushButton(tr("Главное меню"));

    const auto menu = new MenuWidget(tr("Новая игра"), Qt::Horizontal);
    connect(menu, &MenuWidget::start, this, [this, playingFielsWidget, menu]() {
        centralWidget()->setEnabled(true);
        Database::instance().resetItems();
        playingFielsWidget->reset();
        menu->hide();
    });
    connect(menu, &MenuWidget::exit, this, &PlayingFieldWindow::close);
    menu->hide();

    connect(btnMenu, &QPushButton::clicked, this, [this, menu]() {
        menu->show();
        centralWidget()->setEnabled(false);
    });

    const auto mainWidget = new QWidget;

    const auto lay = new QVBoxLayout(mainWidget);
    lay->addWidget(btnMenu);
    lay->addStretch();
    lay->addWidget(playingFielsWidget);

    setMenuWidget(menu);
    setCentralWidget(mainWidget);

    static const auto style = "PlayingFieldWindow { "
                              "    background-image: url(:/resourses/resourses/Background.jpg);"
                              "    background-position: bottom right;"
                              "}";
    setStyleSheet(style);
}
