#ifndef INVENTORIVIEW_H
#define INVENTORIVIEW_H

#include <QTableView>

/// Отображение инвентаря
class InventoriView : public QTableView
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param parent Родительский виджет
    explicit InventoriView(QWidget *parent = nullptr);

protected:
    /// Событие отпускания клавиши мыши
    /// \param event Событие
    void mouseReleaseEvent (QMouseEvent *event) override;
};

#endif // INVENTORIVIEW_H
