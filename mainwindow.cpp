#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculatorbackend.h"
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connects the number buttons
    for (int i = 0; i <= 9; ++i) {
        QString buttonName = "button" + QString::number(i);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if (button) {
            connect(button, &QPushButton::clicked, this, &MainWindow::onNumberClicked);
        }
    }

    // connects the operator buttons
    QString operators = "Plus Minus Multiply Divide Power R";
    QStringList operatorNames = operators.split(" ");
    for (int i = 0; i < operatorNames.size(); ++i) {
        QString op = operatorNames.at(i);
        QString buttonName = "button" + op;
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if (button) {
            connect(button, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
        }

    }

    // connects the equals, clear, history, and clears history buttons
    connect(ui->buttonEquals, &QPushButton::clicked, this, &MainWindow::onEqualsClicked);
    connect(ui->buttonClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->buttonHistory, &QPushButton::clicked, this, &MainWindow::onHistoryClicked);
    connect(ui->buttonClearHistory, &QPushButton::clicked, this, &MainWindow::deleteHistory);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// displays the text on the number button clicked
void MainWindow::onNumberClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    currentInput += button->text();
    ui->display->setText(currentInput);
}

// handles the operator buttons for the calculator
void MainWindow::onOperatorClicked() {
    if (currentInput.isEmpty()) return;

    firstOperand = currentInput.toDouble();
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) currentOperator = button->text().at(0);

    if (currentOperator == 'R') {
        double result = sqrt(firstOperand);
        ui->display->setText(QString::number(result, 'f', 0));
        currentInput.clear();
    } else {
        currentInput.clear();
    }

}

// performs the calculation when equals is clicked and catches invalid inputs and displays an error message for them. Displays the results of the calculation to the display
void MainWindow::onEqualsClicked() {
    if (currentInput.isEmpty()) return;

    double secondOperand = currentInput.toDouble();
    double result = backend.calculate(firstOperand, currentOperator.toLatin1(), secondOperand);


    if (qIsNaN(result)) {
        QMessageBox::warning(this, "Error", "Invalid operation!");
        return;
    }


    ui->display->setText(QString::number(result, 'f', 0));

    firstOperand = result;
    currentInput.clear();

}



// clears the display and inputs when the clear button is clicked
void MainWindow::onClearClicked() {
    currentInput.clear();
    firstOperand = 0;
    currentOperator = '\0';
    ui->display->clear();
}
// displays the users history when the history button is clicked
void MainWindow::onHistoryClicked() {
    QMessageBox::information(this, "History", backend.getHistory());
}
// opens the file the users history is stored in and deletes the contents of it as well as closes it.
void MainWindow::deleteHistory() {
    QFile file("history.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.close();
    }
}













