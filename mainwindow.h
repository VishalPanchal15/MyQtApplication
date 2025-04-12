#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QToolButton>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMenuActionClicked();
    void populateTable();
    void handleMenuClick(const QString &name);

private:
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    QLabel *workingAreaLabel;
    QPushButton* downloadButton = nullptr;
    QPushButton *createButton = nullptr;

    void setupActionMenu();
    void createTableWidget();
    void createLineEditWithDropdown();
    void createSideMenu();
    void setBackgroundImageToFrame(QFrame *frame, const QString &imagePath);   
    void clearTableFrame();
    void setSearchLayoutWidgetsVisible(bool visible);


signals:
    void menuItemClicked(const QString &name);
};

#endif // MAINWINDOW_H
