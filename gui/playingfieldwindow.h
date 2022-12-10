#ifndef PLAYINGFIELDWINDOW_H
#define PLAYINGFIELDWINDOW_H

#include <QMainWindow>

/// Окно игрового поля
class PlayingFieldWindow : public QMainWindow
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param parent Родительский виджет
    explicit PlayingFieldWindow(QWidget *parent = nullptr);
};

#endif // PLAYINGFIELDWINDOW_H
