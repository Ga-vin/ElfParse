#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QTextCodec>
#include "maindialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));

    /*
    */
    MainDialog *pwindow = new MainDialog;
    pwindow->show();

    return (app.exec());
}
