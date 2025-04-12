#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LineEditWithDropdown.h"
#include "SideMenu.h"

#include <QMenu>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tableWidget(nullptr)
    , workingAreaLabel(nullptr)
{
    ui->setupUi(this);
    setupActionMenu();
    createLineEditWithDropdown();
    createSideMenu();
    setSearchLayoutWidgetsVisible(false);
    this->resize(this->width(), 800);
    this->setMinimumHeight(600);

    connect(ui->btnSearch, &QPushButton::clicked, this, &MainWindow::populateTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupActionMenu()
{
    QMenu *menu = new QMenu(this);
    QAction *action1 = menu->addAction("Export");
    QAction *action2 = menu->addAction("Settings");

    connect(action1, &QAction::triggered, this, &MainWindow::onMenuActionClicked);
    connect(action2, &QAction::triggered, this, &MainWindow::onMenuActionClicked);

    ui->actionMenuButton->setMenu(menu);
}

void MainWindow::createLineEditWithDropdown()
{
    LineEditWithDropdown *dropdown = new LineEditWithDropdown(this);
    dropdown->setMaximumWidth(200);

    ui->createButton->setFixedSize(30, 30);
    ui->createButton->setToolTip("Create");
    ui->createButton->setVisible(false); // hidden by default
    ui->createButton->setStyleSheet("QPushButton { background-color: #444; color: white; font-weight: bold; border-radius: 5px; }");


    QHBoxLayout *searchLayout = qobject_cast<QHBoxLayout*>(ui->searchLayout);
    if (!searchLayout) return;

    int index = -1;
    for (int i = 0; i < searchLayout->count(); ++i)
    {
        QWidget *widget = searchLayout->itemAt(i)->widget();
        if (widget == ui->labelSearch) {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        searchLayout->insertWidget(index + 1, dropdown);
    }

    connect(ui->createButton, &QPushButton::clicked, this, []() {
        qDebug() << "'+' button clicked!";
        // Your logic here (e.g., show a dialog, add a row, etc.)
    });
}

void MainWindow::createSideMenu()
{
    ui->sideMenuFrame->setFixedWidth(80);
    ui->sideMenuFrame->setStyleSheet("QFrame { background-color: #2b2b2b; }");

    ui->sidebarLayout->setAlignment(Qt::AlignTop);
    ui->sidebarLayout->setSpacing(15);
    ui->sidebarLayout->setContentsMargins(5, 10, 5, 10);

    auto addSidebarButton = [&](const QString &iconPath, const QString &labelText) {
        QWidget *container = new QWidget();
        QVBoxLayout *vbox = new QVBoxLayout(container);
        vbox->setContentsMargins(0, 0, 0, 0);
        vbox->setAlignment(Qt::AlignHCenter);

        QPushButton *iconBtn = new QPushButton(this);
        iconBtn->setIcon(QIcon(iconPath));
        iconBtn->setIconSize(QSize(32, 32));
        iconBtn->setFlat(true);
        iconBtn->setStyleSheet("QPushButton { border: none; }");

        QLabel *label = new QLabel(labelText);
        label->setStyleSheet("QLabel { color: white; font-size: 10px; }");
        label->setAlignment(Qt::AlignCenter);

        vbox->addWidget(iconBtn);
        vbox->addWidget(label);

        ui->sidebarLayout->addWidget(container);

        connect(iconBtn, &QPushButton::clicked, this, [this, labelText]() {
            handleMenuClick(labelText);
        });
    };

    QString iconPath = "/Users/vishal.panchal/Devlopment/MyQtApplication/images/03 - Jiung.png";
    addSidebarButton(iconPath, "Home");
    addSidebarButton(iconPath, "Avatar");
    addSidebarButton(iconPath, "Fabric");
    addSidebarButton(iconPath, "Trim");
    addSidebarButton(iconPath, "Stage");

    ui->labelLogo->setStyleSheet("font-weight: bold; font-size: 18px; color: cyan;");

    clearTableFrame();

    workingAreaLabel = new QLabel();
    QPixmap pix(iconPath);
    workingAreaLabel->setPixmap(pix.scaled(600, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    workingAreaLabel->setAlignment(Qt::AlignCenter);
    workingAreaLabel->setScaledContents(true);
    workingAreaLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->tableFrame->layout());
    if (!layout) {
        layout = new QVBoxLayout();
        ui->tableFrame->setLayout(layout);
    }
    layout->addWidget(workingAreaLabel);
}

void MainWindow::createTableWidget()
{
    clearTableFrame();

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Status"});

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->tableFrame->layout());
    if (!layout) {
        layout = new QVBoxLayout();
        ui->tableFrame->setLayout(layout);
    }
    layout->addWidget(tableWidget);
}

void MainWindow::populateTable()
{
    if (ui->createButton) ui->createButton->setVisible(false);
    clearTableFrame();

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Status"});
    tableWidget->setRowCount(3);
    tableWidget->setItem(0, 0, new QTableWidgetItem("1"));
    tableWidget->setItem(0, 1, new QTableWidgetItem("Alice"));
    tableWidget->setItem(0, 2, new QTableWidgetItem("Active"));
    tableWidget->setItem(1, 0, new QTableWidgetItem("2"));
    tableWidget->setItem(1, 1, new QTableWidgetItem("Bob"));
    tableWidget->setItem(1, 2, new QTableWidgetItem("Inactive"));
    tableWidget->setItem(2, 0, new QTableWidgetItem("3"));
    tableWidget->setItem(2, 1, new QTableWidgetItem("Charlie"));
    tableWidget->setItem(2, 2, new QTableWidgetItem("Active"));


    // Create layout and add widgets
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->tableFrame->layout());
    if (!layout) {
        layout = new QVBoxLayout();
        ui->tableFrame->setLayout(layout);
    }
    layout->addWidget(tableWidget);

    if (downloadButton) {
        delete downloadButton;
        downloadButton = nullptr;
    }
    
    downloadButton = new QPushButton("Download", this);
    downloadButton->setFixedSize(100, 30);
    downloadButton->setStyleSheet("background-color: #007ACC; color: white; border-radius: 5px;");
    
    connect(downloadButton, &QPushButton::clicked, this, []() {
        qDebug() << "Download button clicked!";
    });
    
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(downloadButton);

    layout->addLayout(btnLayout);

    //ui->tableFrame->setLayout(layout);

}


void MainWindow::onMenuActionClicked()
{
    QAction *senderAction = qobject_cast<QAction*>(sender());
    if (senderAction) {
        qDebug() << "Menu Action Clicked:" << senderAction->text();
    }
}

void MainWindow::handleMenuClick(const QString &name)
{
    setSearchLayoutWidgetsVisible(true);
    if (ui->createButton) ui->createButton->setVisible(true);

    clearTableFrame();  // Clear previous contents

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);

    if (name == "Avatar") {
        tableWidget->setHorizontalHeaderLabels({"Avatar ID", "Name", "Details"});
        tableWidget->setRowCount(2);
        tableWidget->setItem(0, 0, new QTableWidgetItem("AV001"));
        tableWidget->setItem(0, 1, new QTableWidgetItem("Jin"));
        tableWidget->setItem(0, 2, new QTableWidgetItem("Main Vocal"));
        // Add more Avatar data...
    }
    else if (name == "Fabric") {
        tableWidget->setHorizontalHeaderLabels({"Fabric Code", "Type", "Color"});
        tableWidget->setRowCount(2);
        tableWidget->setItem(0, 0, new QTableWidgetItem("FAB101"));
        tableWidget->setItem(0, 1, new QTableWidgetItem("Cotton"));
        tableWidget->setItem(0, 2, new QTableWidgetItem("White"));
        // Add more Fabric data...
    }
    // Add more categories as needed

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->tableFrame->layout());
    if (!layout) {
        layout = new QVBoxLayout();
        ui->tableFrame->setLayout(layout);
    }

    layout->addWidget(tableWidget);
}

// void MainWindow::handleMenuClick(const QString &name)
// {
//     clearTableFrame();  // Clear previous content safely

//     workingAreaLabel = new QLabel(this);
//     workingAreaLabel->setText(QString("You clicked on '%1' module").arg(name));
//     workingAreaLabel->setAlignment(Qt::AlignCenter);
//     workingAreaLabel->setStyleSheet("font-size: 24px; color: gray;");

//     QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->tableFrame->layout());
//     if (!layout) {
//         layout = new QVBoxLayout();
//         ui->tableFrame->setLayout(layout);
//     }

//     layout->addWidget(workingAreaLabel);
// }


void MainWindow::setBackgroundImageToFrame(QFrame *frame, const QString &imagePath)
{
    QString styleSheet = QString(
        "QFrame { background-image: url(%1); background-position: center; background-repeat: no-repeat; }"
    ).arg(imagePath);
    frame->setStyleSheet(styleSheet);
}

void MainWindow::clearTableFrame()
{
    QLayout *layout = ui->tableFrame->layout();
    if (layout) {
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
    }
    // Make sure to reset the pointer!
    workingAreaLabel = nullptr;
    tableWidget = nullptr;
    if (downloadButton) {
        delete downloadButton;
        downloadButton = nullptr;
    }
    
}

void MainWindow::setSearchLayoutWidgetsVisible(bool visible)
{
    QHBoxLayout *searchLayout = qobject_cast<QHBoxLayout*>(ui->searchLayout);
    if (!searchLayout) return;

    for (int i = 0; i < searchLayout->count(); ++i) {
        QLayoutItem *item = searchLayout->itemAt(i);
        QWidget *widget = item->widget();

        if (widget) {
            widget->setVisible(visible);  // hides or shows the widget
        }
        // No need to handle spacers—they're layout items without widgets
        // if (!widget && item->spacerItem()) {
        //     // It's a spacer
        // }
    }
}
