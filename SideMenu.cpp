#include "SideMenu.h"

SideMenu::SideMenu(QWidget *parent)
    : QWidget(parent), expanded(false) {
    setFixedWidth(60);
    setStyleSheet("background-color: #1c1c1c;");

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(10);
    layout->setContentsMargins(5, 5, 5, 5);

    QStringList names = {"Avatar", "Prints", "Colour", "Material", "Shape", "Style"};
    for (const QString &name : names) {
        QToolButton *btn = new QToolButton(this);
        btn->setText(name);
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btn->setIconSize(QSize(24, 24));
        btn->setStyleSheet("color: white;");
        btn->setFixedHeight(40);
        btn->setVisible(false); // start hidden
        buttons.append(btn);
        layout->addWidget(btn);

        connect(btn, &QToolButton::clicked, this, [this, name]() {
            emit menuItemClicked(name);
        });
    }

    installEventFilter(this);
}

bool SideMenu::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Enter) {
        expandMenu();
    } else if (event->type() == QEvent::Leave) {
        collapseMenu();
    }
    return QWidget::eventFilter(obj, event);
}

void SideMenu::expandMenu() {
    if (!expanded) {
        setFixedWidth(160);
        for (QToolButton *btn : buttons)
            btn->setVisible(true);
        expanded = true;
    }
}

void SideMenu::collapseMenu() {
    if (expanded) {
        setFixedWidth(60);
        for (QToolButton *btn : buttons)
            btn->setVisible(false);
        expanded = false;
    }
}
