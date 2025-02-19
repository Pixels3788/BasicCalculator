#include "calculatorbackend.h"
#include <cmath>
#include <fstream>
#include <sstream>

CalculatorBackend::CalculatorBackend() {}

double CalculatorBackend::calculate(double num1, char op, double num2) {
    double result = 0;
    switch(op) {
    case '+': result = num1 + num2; break;
    case '-': result = num1 - num2; break;
    case '*': result = num1 * num2; break;
    case '/':
        if (num2 == 0) return NAN;
        result = num1 / num2;
        break;
    case '^': result = pow(num1, num2); break;
    case 'R': result = sqrt(num1); break;
    default: return NAN; // for invalid operators
    }
    saveResult(num1, op, num2, result);
    return result;
}


void CalculatorBackend::saveResult(double num1, char op, double num2, double result) {
    QString entry = QString("%1 %2 %3 = %4").arg(num1).arg(op).arg(num2).arg(result);
    history.push_back(entry);

    std::ofstream file("history.txt", std::ios::app);
    if (file.is_open()) {
        file << entry.toStdString() << std::endl;
        file.close();
    }
}


QString CalculatorBackend::getHistory() const {
    std::ifstream file("history.txt");
    if (!file.is_open()) return "Error: Unable to open history.";

    std::stringstream buffer;
    buffer << file.rdbuf();
    return QString::fromStdString(buffer.str());
}

bool CalculatorBackend::validateNumber(const QString& input, double& output) {
    bool ok;

    output = input.toDouble(&ok);
    return ok;
}

bool CalculatorBackend::validateOperator(QChar op) {
    return op == '+' || op == '-' || '*' || op == '/' || op == '^';
}



