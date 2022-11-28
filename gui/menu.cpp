#include "menu.h"

#include <QLayout>
#include <QPushButton>

Menu::Menu(const QString &startText, const Qt::Orientation orientations, QWidget *parent)
    : QWidget(parent)
{
    const auto btnStart = new QPushButton(startText);
    connect(btnStart, &QPushButton::clicked, this, &Menu::start);

    const auto btnExit = new QPushButton(tr("Выход"));
    connect(btnExit, &QPushButton::clicked, this, &Menu::exit);

    const auto lay = orientations == Qt::Vertical ? static_cast<QLayout *>(new QVBoxLayout(this))
                                                  : static_cast<QLayout *>(new QHBoxLayout(this));
    lay->addWidget(btnStart);
    lay->addWidget(btnExit);
}
