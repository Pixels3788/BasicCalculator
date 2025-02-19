#ifndef CALCULATORBACKEND_H
#define CALCULATORBACKEND_H

#include <QObject>
#include <Qstring>
#include <vector>


class CalculatorBackend {
public:
    CalculatorBackend(); // constructor to initialize variables

    double calculate(double num1, char op, double num2);
    QString getHistory() const;
    void saveResult(double num1, char op, double num2, double result);
    bool validateNumber(const QString& input, double& output);
    bool validateOperator(QChar op);

private:
    std::vector<QString> history;
};

#endif // CALCULATORBACKEND_H
