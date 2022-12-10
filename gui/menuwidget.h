#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

/// Виджет меню
class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param startText Текст для кнопки начала игры
    /// \param orientations Ориентация меню
    /// \param parent Родительский класс
    explicit MenuWidget(const QString &startText, const Qt::Orientation orientations = Qt::Vertical,
                        QWidget *parent = nullptr);

    /// Сигнал начала игры
    Q_SIGNAL void start();
    /// Сигнал выхода
    Q_SIGNAL void exit();
};

#endif // MENUWIDGET_H
