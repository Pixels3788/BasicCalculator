#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculatorbackend.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNumberClicked();
    void onOperatorClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onHistoryClicked();
    void deleteHistory();

private:
    Ui::MainWindow *ui;
    CalculatorBackend backend;
    QString currentInput;
    double firstOperand;
    QChar currentOperator;
};
#endif // MAINWINDOW_H
