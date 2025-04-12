#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include <QEvent>
#include <QStringList>

class SideMenu : public QWidget {
    Q_OBJECT
public:
    explicit SideMenu(QWidget *parent = nullptr);

signals:
    void menuItemClicked(const QString &name);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    bool expanded;
    QVBoxLayout *layout;
    QList<QToolButton*> buttons;

    void expandMenu();
    void collapseMenu();
};

#endif // SIDEMENU_H
