#ifndef CALCULATORDIG_H
#define CALCULATORDIG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class CalculatorDig : public QDialog
{
    Q_OBJECT
public:
    CalculatorDig(QWidget *parent = nullptr);
private slots:
    void onButtonClicked();
private:
    QLineEdit *display;
    QString currentExpression;

    void evaluateExpression();
};

#endif // CALCULATORDIG_H
