#include <QApplication>
#include "calculatordig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorDig w;
    w.show();
    return a.exec();
}
