#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //QApplication::setStyle(QStyleFactory::create("Windows"));
    MainWindow w;
    //qDebug() << QApplication::style()->objectName();
    w.show();
 /*   qDebug() << QApplication::style()->objectName();
    QStringList availableStyles = QStyleFactory::keys();
    qDebug() << "Available styles:" << availableStyles;*/
    return a.exec();

}
