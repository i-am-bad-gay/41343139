#include "calculatordig.h"
#include <QGridLayout>
#include <QJSEngine>
#include <QJSValue>
#include <QChar>
#include <QDebug>

CalculatorDig::CalculatorDig(QWidget *parent)
    : QDialog(parent), display(new QLineEdit(this))
{
    setWindowTitle(QStringLiteral("Calculator"));
    resize(300, 400);

    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(50);
    display->setText("0");

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(display, 0, 0, 1, 4);

    QPushButton *btnBack = new QPushButton(QStringLiteral("←"));
    QPushButton *btnDiv  = new QPushButton(QStringLiteral("/"));
    QPushButton *btnMul  = new QPushButton(QStringLiteral("*"));
    QPushButton *btnSub  = new QPushButton(QStringLiteral("-"));

    QPushButton *btn7 = new QPushButton("7");
    QPushButton *btn8 = new QPushButton("8");
    QPushButton *btn9 = new QPushButton("9");
    QPushButton *btnPlus = new QPushButton("+");

    QPushButton *btn4 = new QPushButton("4");
    QPushButton *btn5 = new QPushButton("5");
    QPushButton *btn6 = new QPushButton("6");

    QPushButton *btn1 = new QPushButton("1");
    QPushButton *btn2 = new QPushButton("2");
    QPushButton *btn3 = new QPushButton("3");

    QPushButton *btn0 = new QPushButton("0");
    QPushButton *btnDot = new QPushButton(".");
    QPushButton *btnEq = new QPushButton("=");

    QList<QPushButton*> allBtns = {btnBack, btnDiv, btnMul, btnSub,
        btn7, btn8, btn9, btnPlus,
        btn4, btn5, btn6,
        btn1, btn2, btn3,
        btn0, btnDot, btnEq};

    for(auto a: allBtns){
        a->setMinimumSize(60, 45);
    }
    layout->addWidget(btnBack, 1, 0);
    layout->addWidget(btnDiv,  1, 1);
    layout->addWidget(btnMul,  1, 2);
    layout->addWidget(btnSub,  1, 3);

    layout->addWidget(btn7, 2, 0);
    layout->addWidget(btn8, 2, 1);
    layout->addWidget(btn9, 2, 2);
    layout->addWidget(btnPlus, 2, 3, 2, 1);

    layout->addWidget(btn4, 3, 0);
    layout->addWidget(btn5, 3, 1);
    layout->addWidget(btn6, 3, 2);

    layout->addWidget(btn1, 4, 0);
    layout->addWidget(btn2, 4, 1);
    layout->addWidget(btn3, 4, 2);

    layout->addWidget(btn0, 5, 0, 1, 2);
    layout->addWidget(btnDot, 5, 2);
    layout->addWidget(btnEq, 4, 3, 2, 1);

    for(auto b: allBtns){
        connect(b, &QPushButton::clicked, this, &CalculatorDig::onButtonClicked);
    }
    setLayout(layout);
}

void CalculatorDig::onButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(!btn) return;
    QString tex = btn->text();
    if(tex == "←"){
        if(!currentExpression.isEmpty()){
            currentExpression.chop(1);
            if(currentExpression.isEmpty()) display->setText("0");
            else display->setText(currentExpression);
        }
        return;
    }
    if(tex == "="){
        evaluateExpression();
        return;
    }
    if(display->text() == "0" && tex != "." && !QString("+-*/").contains(tex)){
        currentExpression = tex;
    } else {
        currentExpression += tex;
    }
    display->setText(currentExpression);
}

void CalculatorDig::evaluateExpression()
{
    if(currentExpression.isEmpty()) return;
    while(!currentExpression.isEmpty() && QString("+-*/").contains(currentExpression.right(1))){
        currentExpression.chop(1);
    }
    if(currentExpression.isEmpty()){
        display->setText("0");
        return;
    }
    QJSEngine engine;
    QString expr = currentExpression;
    expr.remove(' ');
    QJSValue result = engine.evaluate(expr);
    if(result.isError() || !result.isNumber()){
        display->setText("error");
        currentExpression.clear();
    } else {
        double val = result.toNumber();
        QString out;
        if(qFuzzyCompare(val, qRound(val)))
            out = QString::number(qRound(val));
        else
            out = QString::number(val, 'g', 12);
        display->setText(out);
        currentExpression = out;
    }
}
