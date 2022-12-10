#include "menuwidget.h"

#include <QLayout>
#include <QPushButton>

MenuWidget::MenuWidget(const QString &startText, const Qt::Orientation orientations,
                       QWidget *parent)
    : QWidget(parent)
{
    const auto btnStart = new QPushButton(startText);
    connect(btnStart, &QPushButton::clicked, this, &MenuWidget::start);

    const auto btnExit = new QPushButton(tr("Выход"));
    connect(btnExit, &QPushButton::clicked, this, &MenuWidget::exit);

    const auto lay = orientations == Qt::Vertical ? static_cast<QLayout *>(new QVBoxLayout(this))
                                                  : static_cast<QLayout *>(new QHBoxLayout(this));
    lay->addWidget(btnStart);
    lay->addWidget(btnExit);
}
