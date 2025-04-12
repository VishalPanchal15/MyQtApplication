#include "LineEditWithDropdown.h"

LineEditWithDropdown::LineEditWithDropdown(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Create Line Edit
    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("Search...");
    lineEdit->setFixedHeight(30);
    //lineEdit->setMaximumWidth(300);
    
    lineEdit->setStyleSheet(R"(
        QLineEdit {
            border: 1px solid #ccc;
            border-right: none;
            border-top-left-radius: 5px;
            border-bottom-left-radius: 5px;
            padding: 5px;
            background-color: rgb(39,39,39);
        }
    )");

    // Create Dropdown Button
    dropdownButton = new QToolButton(this);
    dropdownButton->setText("▼");
    dropdownButton->setFixedHeight(30);
    dropdownButton->setFixedWidth(30); // Optional: fix width for icon-only style
    dropdownButton->setStyleSheet(R"(
        QToolButton {
            border: 1px solid #ccc;
            border-left: none;
            border-top-right-radius: 5px;
            border-bottom-right-radius: 5px;
            background-color: rgb(39,39,39);
        }
        QToolButton::menu-indicator {
            image: none;
        }
    )");

    mainLayout->addWidget(lineEdit);
    mainLayout->addWidget(dropdownButton);
    connect(dropdownButton, &QToolButton::clicked, this, &LineEditWithDropdown::showFloatingWidget);
}

LineEditWithDropdown::~LineEditWithDropdown()
{
    if (floatingWidget) {
        floatingWidget->deleteLater();
    }
}

void LineEditWithDropdown::showFloatingWidget()
{

    if (!floatingWidget)
    {
        floatingWidget = new QDialog(this);
        floatingWidget->setFixedSize(250, 300);
        QVBoxLayout *floatingLayout = new QVBoxLayout(floatingWidget);
        additionalLineEdits.clear();
        comboBoxes.clear();

        // Example: Let's assume we want 2 lines and 1 dropdown
        for (int i = 0; i < 2; ++i) {
            QLabel *label = new QLabel(QString("Input %1:").arg(i + 1), floatingWidget);
            QLineEdit *line = new QLineEdit(floatingWidget);
            additionalLineEdits.append(line);

            floatingLayout->addWidget(label);
            floatingLayout->addWidget(line);
        }

        QLabel *comboLabel = new QLabel("Select Option:", floatingWidget);
        QComboBox *combo = new QComboBox(floatingWidget);
        combo->addItems({"Option A", "Option B", "Option C"});
        comboBoxes.append(combo);

        floatingLayout->addWidget(comboLabel);
        floatingLayout->addWidget(combo);

        floatingWidget->setLayout(floatingLayout);

        int popupWidth = 250;
        floatingWidget->resize(popupWidth, floatingWidget->sizeHint().height());

        QPoint globalPos = mapToGlobal(lineEdit->geometry().topLeft());
        floatingWidget->move(globalPos.x() - popupWidth + lineEdit->width(), globalPos.y() + lineEdit->height());

        floatingWidget->show();

        QApplication::instance()->installEventFilter(this);
    }
    else
    {
        floatingWidget->close();
        floatingWidget = nullptr;
        QApplication::instance()->removeEventFilter(this);
    }

}

bool LineEditWithDropdown::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (floatingWidget && !floatingWidget->geometry().contains(static_cast<QMouseEvent *>(event)->globalPos()))
        {
            floatingWidget->close();
            floatingWidget = nullptr;
            QApplication::instance()->removeEventFilter(this);
        }
    }
    return QWidget::eventFilter(obj, event);
}

QString LineEditWithDropdown::getPopupText() const
{
    return additionalLineEdit ? additionalLineEdit->text() : "";
}

QString LineEditWithDropdown::getPopupSelection() const
{
    return comboBox ? comboBox->currentText() : "";
}

// void LineEditWithDropdown::updateLineEditWithPopupData()
// {
//     QString combined = getPopupText() + " | " + getPopupSelection();
//     lineEdit->setText(combined);
// }

QString LineEditWithDropdown::collectFloatingData() const
{
    QStringList parts;
    for (auto *line : additionalLineEdits) {
        parts << line->text();
    }
    for (auto *combo : comboBoxes) {
        parts << combo->currentText();
    }
    return parts.join(" | ");
}

void LineEditWithDropdown::updateLineEditWithPopupData()
{
    lineEdit->setText(collectFloatingData());
}
