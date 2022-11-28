#ifndef MENU_H
#define MENU_H

#include <QWidget>

/// Виджет меню
class Menu : public QWidget
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param startText Текст для кнопки начала игры
    /// \param orientations Ориентация меню
    /// \param parent Родительский класс
    explicit Menu(const QString &startText, const Qt::Orientation orientations = Qt::Vertical,
                  QWidget *parent = nullptr);

    /// Сигнал начала игры
    Q_SIGNAL void start();
    /// Сигнал выхода
    Q_SIGNAL void exit();
};

#endif // MENU_H
