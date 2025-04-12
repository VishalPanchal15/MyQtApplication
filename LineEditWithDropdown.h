#ifndef LINEEDITWITHDROPDOWN_H
#define LINEEDITWITHDROPDOWN_H

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>

class LineEditWithDropdown : public QWidget
{
    Q_OBJECT

public:
    LineEditWithDropdown(QWidget *parent = nullptr);
    ~LineEditWithDropdown();

    QString getPopupText() const;
    QString getPopupSelection() const;
    void updateLineEditWithPopupData();

private slots:
    void showFloatingWidget();
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QLineEdit *lineEdit;
    QToolButton *dropdownButton;
    QDialog *floatingWidget = nullptr;
    QLineEdit *additionalLineEdit = nullptr;
    QComboBox *comboBox = nullptr;
    QList<QLineEdit*> additionalLineEdits;
    QList<QComboBox*> comboBoxes;

    QString collectFloatingData() const;
};

#endif // LINEEDITWITHDROPDOWN_H
